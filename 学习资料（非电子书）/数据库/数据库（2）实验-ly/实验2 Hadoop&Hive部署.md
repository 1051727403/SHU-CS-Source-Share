---
title: "hadoop部署"
date: 2023-12-14
tags:
  - hadoop
  - hive
  - hdfs
  - 分布式
  - 实验
  - 数据库原理
categories:
  - 实践
description: "这篇文章记录了在三台云服务器上部署hadoop的过程"
draft: false

---

博客地址：sirius1y.top

### 生成密钥并实现自我登录

```bash
sudo apt-get install vim
sudo apt-get install openssh-server
cd .ssh
ssh-keygen -t rsa -C "sirius1y@outlook.com"
cat id_rsa.pub > authorized_keys
```

![图片1](https://s2.loli.net/2023/12/14/SeFMJrOcvl8wy4V.png)

### 安装java

```
sudo apt-get install openjdk-8-jre openjdk-8-jdk
```

 

#### 检查java是否安装完成

```
java -version
```

 

### 下载hadoop

网站：https://archive.apache.org/dist/hadoop/common/hadoop-2.7.0/

```bash
wget https://archive.apache.org/dist/hadoop/common/hadoop-2.7.0/hadoop-2.7.0.tar.gz

# 解压
sudo tar -zxf hadoop-2.7.0.tar.gz -C /usr/local
```

修改所有权：

```bash
cd /usr/local
sudo mv hadoop-2.7.0/ hadoop
sudo chown -R ubuntu ./hadoop
```

![图片2](https://s2.loli.net/2023/12/14/8kF1PyrnROc9ZMg.png)



#### 设置JAVA_HOME环境变量

```bash
sudo vim ~/.bashrc

# 把下面内容添加到末尾
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
```

![图片3](https://s2.loli.net/2023/12/14/ewuXvmhE85iWlHR.png)

删除~/.ssh/kown_hosts

创建镜像之后新建示例

发现能够存在hadoop

![图片4](https://s2.loli.net/2023/12/14/59vYaNkGD7JAWlb.png)

-----------------创建两台镜像

#### 取机器的昵称

`sudo vim /etc/hostname`添加自己的名字

![图片5](https://s2.loli.net/2023/12/14/SyXokEAMwWRjZ8i.png)

`sudo vim /etc/hosts`，这里都是使用的**内网IP地址**

![图片6](https://s2.loli.net/2023/12/14/av9TStrykmKPRVx.png)

重启之后，每台机器的名字都变了

![图片7](https://s2.loli.net/2023/12/14/7CIDMe8AirYfckL.png)



并且可以通过直接`ssh master`,`ssh slave01`的方式直接访问；

 

#### 修改master和slaves配置文件

```bash
cd /usr/local/hadoop/etc/hadoop/
```

修改这些配置文件

配置文件详情：

https://www.aidac-shu.com/courses/的reference部分

![图片8](https://s2.loli.net/2023/12/14/W4g5zPfqAsdHZEB.png)

```xml
# slaves
slave01
slave02
```

```xml
# core-site.xml
<configuration>
<property>
<name>hadoop.tmp.dir</name>
<value>/usr/local/hadoop/tmp</value>
<description>Abase for other temporary directories.</description>
</property>
<property>
<name>fs.defaultFS</name>
<value>hdfs://master:9000</value>
</property>
</configuration>
```

```xml
# hdfs-site.xml
<configuration>
<property>
<name>dfs.replication</name>
<value>3</value>
</property>
</configuration>
```

```xml
# mapred-site.xml
<configuration>
<property>
<name>mapreduce.framework.name</name>
<value>yarn</value>
</property>
</configuration>
```

```xml
# yarn-site.xml
<configuration>
<!--  Site specific YARN configuration properties  -->
<property>
<name>yarn.nodemanager.aux-services</name>
<value>mapreduce_shuffle</value>
</property>
<property>
<name>yarn.resourcemanager.hostname</name>
<value>master</value>
</property>
</configuration>
```

![图片8](https://s2.loli.net/2023/12/14/mda3cD5YObRyzX4.png)



用`jps`检查java进程执行情况

![图片10](https://s2.loli.net/2023/12/14/34hyKYJlxvZgcr1.png)



### 启动hadoop

```bash
/usr/local/hadoop/bin/hdfs namenode -format
```

在这之后会得到一大串的输出，最后会出现两个0,表示成功执行：

![图片11](https://s2.loli.net/2023/12/14/q5n6Jt3alNS4DE8.png)



```bash
/usr/local/hadoop/sbin/start-all.sh
```

![图片12](https://s2.loli.net/2023/12/14/Tt38nRZzDPgHmC1.png)



刚开始启用这条命令的时候会出现JAVA_HOME没有设置的情况，但是我已经在`~/.bashrc`中设置了(尝试过在/etc/bash.bashrc也不行)

原因很有可能是环境变量并没有作用到`/usr/local/hadoop`中。

然后我在`/usr/local/hadoop/etc/hadoop/hadoop-env.sh`中设置了`export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64`之后（在master和两台slave上都设置）了，在启用命令`sbin/start-all.sh`就能成功执行。



![图片13](https://s2.loli.net/2023/12/14/Dl2zAMHpaVTNYrI.png)

![图片14](https://s2.loli.net/2023/12/14/ix2T4ENXC3DUzFO.png)

![图片15](https://s2.loli.net/2023/12/14/vigGIfO1pwAqurc.png)

![图片16](https://s2.loli.net/2023/12/14/rkMmTQ9N6OSJZqc.png)



### HDFS使用

#### 添加HADOOP环境变量

可以把HADOOP的位置/usr/local/hadoop/添加到环境变量中，就可以直接访问hadoop和hdfs了

```bash
export HADOOP_HOME=/usr/local/hadoop
export PATH=$PATH:$HADOOP_HOME/bin
```

![图片17](https://s2.loli.net/2023/12/14/SlzMeRJGtrKQ84m.png)



#### 文件操作

在slave01上把文件放入到/中: hdfs dfs -put etc/hadoop/*.xml /

使用命令`hdfs dfs -ls /`会列出文件系统/下的所有文件

![图片18](https://s2.loli.net/2023/12/14/bdHCAXDs5vZpQny.png)



在这里演示，在文件系统中先创建一个目录/user/input/，再把文件try.sh放入其中，再进行查看

![图片19](https://s2.loli.net/2023/12/14/UC4QNkH5M6uvqgV.png)



需要注意的是，需要在目录创建成功之后再进行put操作，否则只会创建目录，但是不会把文件放入其中的操作。(好奇怪)

 另外，在任何一个结点上创建的文件都会同步到其他几台机器上。

![图片20](https://s2.loli.net/2023/12/14/DdaGAFvLsT81RNW.png)

![图片21](https://s2.loli.net/2023/12/14/u15mt6iG9jW3YCA.png)



## 配置HIVE

### 下载hive

在master上的主目录上，运行

```bash
wget https://dlcdn.apache.org/hive/hive-1.2.2/apache-hive-1.2.2-bin.tar.gz
```



#### 解压到主目录下

```bash
ubuntu@master:~$ tar -zxvf apache-hive-1.2.2-bin.tar.gz -C ~
```



#### 更改名字+更改所有权

```bash
# 改名 mv
ubuntu@master:~$ ls
apache-hive-1.2.2-bin  apache-hive-1.2.2-bin.tar.gz  hadoop-2.7.0.tar.gz
ubuntu@master:~$ mv apache-hive-1.2.2-bin hive
ubuntu@master:~$ ls
apache-hive-1.2.2-bin.tar.gz  hadoop-2.7.0.tar.gz  hive

# 更改所有权 chown
ubuntu@master:~$ sudo chown -R ubuntu ./hive
```

#### 把hive添加到环境变量中

```bash
# ~/.bashrc

export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export HADOOP_HOME=/usr/local/hadoop
export PATH=$PATH:$HADOOP_HOME/bin
export HIVE_HOME=/home/ubuntu/hive/
export PATH=$PATH:$HIVE_HOME/bin
```

完成之后更新 `source ~/.bashrc`



### 运行hive

![image-20231221193739573](https://s2.loli.net/2023/12/21/hO4TgCJRsAkpaZ8.png)

```hive
# HiveSQL
# 创建数据库
CREATE DATABASE one;

# 查看数据库
SHOW DATABASES;

# 切换数据库
USE database_name;

# 查看该数据库下面的所有表
SHOW TABLES;

# 新建表
CREATE TABLE employees(
	id INT,
    name STRING,
    department STRING
);

# 插入数据
INSERT INTO TABLE employees (id, name, department) VALUES (1, 'Alice', 'IT');
INSERT INTO TABLE employees (id, name, department) VALUES (2, 'Bob', 'HR');
INSERT INTO TABLE employees (id, name, department) VALUES (3, 'Charlie', 'Finance');


# 查询操作
SELECT * FROM employees;
SELECT * FROM employees WHERE department='IT';
```

插入过程中的一些截图，他这个插入还比较麻烦：

分为了三个部分进行执行。

![image-20231221203144988](https://s2.loli.net/2023/12/21/qVaWYTcKb47xrSv.png)

![image-20231221203202258](https://s2.loli.net/2023/12/21/tSlPHsop1Qmg8BA.png)

查询展示：

![image-20231221203034689](https://s2.loli.net/2023/12/21/utHKCweYW8czgFn.png)

![image-20231221202956806](https://s2.loli.net/2023/12/21/QmtkgaJU2D7YoF3.png)