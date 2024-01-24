---
title: "在docker中安装redis"
date: 2024-01-04
tags:
  - redis
  - docker
  - kubernetes
categories:
  - 实践
  - 部署
  - docker
description: "记录部署在docker中部署redis的过程，并使用k8s进行容器编排管理"
draft: false
keywords:
  - Docker
  - Kubernetes
  - Redis
---



博客地址：sirius1y.top



#### 常规步骤：安装vim openssh，生成密钥

```bash
sudo apt-get update
sudo apt-get install vim openssh-server
cd .ssh
ssh-keygen -t rsa -C "sirius1y@outlook.com"
cat id_rsa.pub > authorized_keys
ssh localhost
exit
rm known_hosts
```



#### 安装docker

##### 设置 Docker 的`apt`存储库

官网教程：https://docs.docker.com/desktop/install/ubuntu/

```bash
# Add Docker's official GPG key:
sudo apt-get update
# 安装证书、下载工具、证书验证工具
sudo apt-get install ca-certificates curl gnupg
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
# 证书对所有人都可读
sudo chmod a+r /etc/apt/keyrings/docker.gpg

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

![image-20240104183136017](/home/yoho/.config/Typora/typora-user-images/image-20240104183136017.png)

##### 安装 Docker 软件包

```bash
 sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

##### 通过运行镜像来验证Docker Engine安装是否成功

```bash
sudo docker run hello-world
```

![image-20240104183604976](https://s2.loli.net/2024/01/04/iZ7XgPloVHshcrR.png)



#### 安装Kubernetes

##### 换源

```bash
apt-get update && apt-get install -y apt-transport-https
curl https://mirrors.aliyun.com/kubernetes/apt/doc/apt-key.gpg | sudo apt-key add - 
sudo vim /etc/apt/sources.list.d/kubernetes.list
###
deb https://mirrors.aliyun.com/kubernetes/apt/ kubernetes-xenial main
###
sudo apt-get update

# 验证
apt-cache madison kubectl
apt-cache madison kubeadm
```

![image-20240104185758066](https://s2.loli.net/2024/01/04/Gt6RxKPWAf3v1ld.png)

![image-20240104185808655](https://s2.loli.net/2024/01/04/Gh2HoSg3jWDbViB.png)

![image-20240104185834186](https://s2.loli.net/2024/01/04/dwGTnsAIPrhDMFL.png)

##### 开始安装

```bash
sudo apt-get install kubelet=1.18.0-00 kubeadm=1.18.0-00 kubectl=1.18.0-00
```

##### 验证安装成功

```bash
kubeadm version
```

![image-20240104190129329](https://s2.loli.net/2024/01/04/wFenpLzG28A6oqN.png)

 

---------------------

#### 在腾讯云上将当前主机创建为镜像



#### 从镜像中恢复后，检查docker, kubeadm为1.18的版本

```bash
sudo docker run hello-world
kubeadm version
```

![image-20240111181803831](https://s2.loli.net/2024/01/11/p4wdLvbXV5Y2szh.png)

------------------------------



#### 更改hostname，hosts

添加内网地址

```bash
sudo vim /etc/hostname
```

```bash
sudo vim /etc/hosts
```

重启之后，可以实现免密ssh登录



#### 关闭swap分区虚拟内存

```bash
sudo swapoff -a
```



### kubenetes初始化

#### 使用kubeadm初始化master node

参考指南：https://kubernetes.io/zh-cn/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/

这里的内网地址和外网地址都可以，但是后面的`--service-cidr,--pod-network`是需要的，不然会出现flannel一直处于crash状态一直在重启，并且dnscore也会一直处于creating的状态。

```bash
sudo kubeadm init --apiserver-advertise-address=172.19.16.5 --image-repository=registry.aliyuncs.com/google_containers --service-cidr=10.96.0.0/12  --pod-network-cidr=10.244.0.0/16
```

![image-20240104193322308](https://s2.loli.net/2024/01/04/FGvNpD5Kcq19Had.png)![image-20240111183223556](https://s2.loli.net/2024/01/11/uhUx4Diyr8YJsjP.png)

```bash
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config
```



#### kubernete slave加入

```bash
sudo kubeadm join 172.19.16.6:6443 --token 836yhd.5plsxh5r8j13xcjz \
    --discovery-token-ca-cert-hash sha256:8dbfb4048b7e636a20184b8e24a55a27319597001d526468ee58531d2d0521c8 
```

![image-20240111183412977](https://s2.loli.net/2024/01/11/NIS2ZGw7kh8XjqF.png)



### 进行部署

```bash
# master
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
kubectl get pods --all-namespaces
kubectl get nodes

```

![image-20240111184243268](https://s2.loli.net/2024/01/11/y7F3AuazijS4hxg.png)



#### redis deployment

```bash
mkdir redis_example
cd redis_example/
vim redis-leader-deployment.yaml
```

```yaml
# redis-leader-deployment.yaml
# SOURCE: https://cloud.google.com/kubernetes-engine/docs/tutorials/guestbook
apiVersion: apps/v1
kind: Deployment
metadata:
  name: redis-leader
  labels:
    app: redis
    role: leader
    tier: backend
spec:
  replicas: 1
  selector:
    matchLabels:
      app: redis
  template:
    metadata:
      labels:
        app: redis
        role: leader
        tier: backend
    spec:
      containers:
      - name: leader
        image: "docker.io/redis:6.0.5"
        resources:
          requests:
            cpu: 100m
            memory: 100Mi
        ports:
        - containerPort: 6379
```

```bash
kubectl apply -f redis-leader-deployment.yaml
```

![image-20240111185229816](https://s2.loli.net/2024/01/11/cuqYIz4AZB6klgU.png)



#### redis service

```bash
vim redis-leader-service.yaml
```

```yaml
# redis-leader-service.yaml
# SOURCE: https://cloud.google.com/kubernetes-engine/docs/tutorials/guestbook
apiVersion: v1
kind: Service
metadata:
  name: redis-leader
  labels:
    app: redis
    role: leader
    tier: backend
spec:
  ports:
  - port: 6379
    targetPort: 6379
  selector:
    app: redis
    role: leader
    tier: backend
```

```bash
kubectl apply -f redis-leader-service.yaml
```

![image-20240111185444638](https://s2.loli.net/2024/01/11/WYtK2T4qUrFJwR9.png)



#### redis deployment

```bash
vim redis-follower-deployment.yaml
```

```yaml
# SOURCE: https://cloud.google.com/kubernetes-engine/docs/tutorials/guestbook
apiVersion: apps/v1
kind: Deployment
metadata:
  name: redis-follower
  labels:
    app: redis
    role: follower
    tier: backend
spec:
  replicas: 2
  selector:
    matchLabels:
      app: redis
  template:
    metadata:
      labels:
        app: redis
        role: follower
        tier: backend
    spec:
      containers:
      - name: follower
        image: us-docker.pkg.dev/google-samples/containers/gke/gb-redis-follower:v2
        resources:
          requests:
            cpu: 100m
            memory: 100Mi
        ports:
        - containerPort: 6379
```

```bash
kubectl apply -f redis-follower-deployment.yaml 
```

![image-20240111185655077](https://s2.loli.net/2024/01/11/S9CPEuUMxBdFeW3.png)



#### redis service

```bash
vim redis-follower-service.yaml
```

```yaml
# SOURCE: https://cloud.google.com/kubernetes-engine/docs/tutorials/guestbook
apiVersion: v1
kind: Service
metadata:
  name: redis-follower
  labels:
    app: redis
    role: follower
    tier: backend
spec:
  ports:
    # the port that this service should serve on
  - port: 6379
  selector:
    app: redis
    role: follower
    tier: backend
```

```bash
kubectl apply -f redis-follower-service.yaml
```

![image-20240111185849832](https://s2.loli.net/2024/01/11/JTLwneP7SFCcWGg.png)



#### 前端deployment

```bash
vim frontend-deployment.yaml
```

```yaml
# SOURCE: https://cloud.google.com/kubernetes-engine/docs/tutorials/guestbook
apiVersion: apps/v1
kind: Deployment
metadata:
  name: frontend
spec:
  replicas: 3
  selector:
    matchLabels:
        app: guestbook
        tier: frontend
  template:
    metadata:
      labels:
        app: guestbook
        tier: frontend
    spec:
      containers:
      - name: php-redis
        image: us-docker.pkg.dev/google-samples/containers/gke/gb-frontend:v5
        env:
        - name: GET_HOSTS_FROM
          value: "dns"
        resources:
          requests:
            cpu: 100m
            memory: 100Mi
        ports:
        - containerPort: 80

```

```bash
kubectl apply -f frontend-deployment.yaml
```

![image-20240111190010397](https://s2.loli.net/2024/01/11/2WLNyi1DY8kCnu5.png)



#### 前端service

```bash
vim frontend-service.yaml
```

```yaml
# SOURCE: https://cloud.google.com/kubernetes-engine/docs/tutorials/guestbook
apiVersion: v1
kind: Service
metadata:
  name: frontend
  labels:
    app: guestbook
    tier: frontend
spec:
  # if your cluster supports it, uncomment the following to automatically create
  # an external load-balanced IP for the frontend service.
  # type: LoadBalancer
  type: NodePort
  ports:
    # the port that this service should serve on
  - port: 80
  selector:
    app: guestbook
    tier: frontend
```

```bash
kubectl apply -f frontend-service.yaml
```

![image-20240111190231786](https://s2.loli.net/2024/01/11/AYyxV4zmvaURq8H.png)



### 访问前端

在云服务器的安全组里面放开frontend的端口，在浏览器中访问可以看到页面

![image-20240111191415134](https://s2.loli.net/2024/01/11/vAWpC3jBU1mZO6f.png)

![image-20240111191356009](https://s2.loli.net/2024/01/11/HbNMf8LUjTtBAI2.png)

### 删除其中的一个pod

在尝试删除一个front pod之后，可以看到kubernetes系统自动为我们新建了一个frontend的pod

```bash
kubectl delete pod frontend-769fbdbdcc-jdvfb
```

![image-20240111191523416](https://s2.loli.net/2024/01/11/DWmPS5BTpAjFz9e.png)



### pod扩容

```bash
kubectl scale deployment frontend --replicas=5
```

![image-20240111191623642](https://s2.loli.net/2024/01/11/gFXH7fv9duVz1Mt.png)
