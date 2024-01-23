---
title: "GNS3+RIP/OSRF"
date: 2023-10-30
tags:
  - GNS3
  - 动态路由
  - RIP
  - OSRF
  - router

---

博客地址：sirius1y.top

# RIP

## 网络拓扑图



![image-20231030000821307](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698595735.png)

## 路由器配置

![image-20231030000807480](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698595729.png)

下面是路由器R1、R2和R3的配置示例:

**R1 配置:**

```shell
configure terminal
interface FastEthernet0/0
ip address 10.1.1.1 255.255.255.0
no shutdown
exit

interface FastEthernet0/1
ip address 172.16.10.1 255.255.255.0
no shutdown
exit

router rip
version 2
network 10.1.1.0
network 172.16.0.0
end
wr
```

**R2 配置:**

```
configure terminal
interface FastEthernet0/0
ip address 10.1.1.2 255.255.255.0
no shutdown
exit

router rip
version 2
network 10.1.1.0
end
wr
```

**R3 配置:**

```
configure terminal
interface FastEthernet0/0
ip address 172.16.10.2 255.255.255.0
no shutdown
exit

router rip
version 2
network 172.16.0.0
end
wr
```

## 配置结果

### show ip interface brief

```
R2#show ip interface brief
Interface                  IP-Address      OK? Method Status                Protocol
FastEthernet0/0            10.1.1.2        YES manual up                    up   

R1#show ip interface brief
Interface                  IP-Address      OK? Method Status                Protocol
FastEthernet0/0            10.1.1.1        YES manual up                    up      
FastEthernet0/1            172.16.10.1     YES manual up                    up     

R3#show ip interface brief
Interface                  IP-Address      OK? Method Status                Protocol
FastEthernet0/0            172.16.10.2     YES manual up                    up      
```



### show ip route

![image-20231030001852105](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698596663.png)

![image-20231030001921939](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698596361.png)

![image-20231030001945874](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698596385.png)

### show ip protocols

![image-20231030001739722](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698596259.png)



## 结果检验

![image-20231030001326702](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698596006.png)

![image-20231030001401757](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698596041.png)



## 问题记录

问题1：刚开始绘制拓扑图的时候随意发挥，每个网卡都配的不一样的子网，然后互相ping不通，虽然设置了rip协议，但是一开始就没有相互连上的网段，所以也无法进行交换。

![image-20231030003810394](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698597490.png)



# OSRF

## 网络拓扑图和路由配置

![image-20231030004059539](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698597659.png)

## 配置

**R1 配置:**

```shell
configure terminal
interface FastEthernet0/0
ip address 172.16.10.1 255.255.0.0
no shutdown
exit

interface FastEthernet0/1
ip address 10.1.1.1 255.255.255.0
no shutdown
exit

router ospf 100
network 10.1.1.0 0.0.0.255 area 0
network 172.16.0.0 0.0.255.255 area 0
end
wr


```

**R2 配置:**

```
configure terminal
interface FastEthernet0/0
ip address 10.1.1.2 255.255.255.0
no shutdown
exit

router ospf 100
network 10.1.1.0 0.0.0.255 area 0
end
wr

```

**R3 配置:**

```
configure terminal
interface FastEthernet0/0
ip address 172.16.10.2 255.255.0.0
no shutdown
exit

router ospf 100
network 172.16.0.0 0.0.255.255 area 0
end
wr

```



## 配置截图

### show ip route

![image-20231030005839882](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698598812.png)

### show ip protocols

![image-20231030005924477](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698598764.png)

## 联通性测试

![image-20231030005729042](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698598800.png)

![image-20231030005741503](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698598789.png)
