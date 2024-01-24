---
title: "GNS3+static router"
date: 2023-10-30
tags:
  - GNS3
  - 静态路由
---



博客地址：sirius1y.top



## 预备知识

### 静态路由和动态路由是什么？

**静态路由**

静态路由是一种手动配置路由信息的方式，其中网络管理员手动指定每个目的地网络的下一跳路由器或出口。这些手动配置的路由信息通常在网络中不经常更改，因此称为"静态"路由。静态路由通常用于小型网络或需要特定路由路径的特殊情况，例如，将流量定向到特定服务器或分支机构。

静态路由的主要优点是简单和易于管理，因为管理员有完全的控制权。然而，它不适用于大型、复杂的网络，因为手动配置路由信息可能变得非常繁琐，并且难以应对网络拓扑的变化。

**动态路由**

动态路由是一种更灵活的路由方式，其中路由器能够自动学习网络拓扑和动态地调整路由表。动态路由协议允许路由器之间交换路由信息，以确定最佳路径到达目的地网络。一些常见的动态路由协议包括RIP（Routing Information Protocol）、OSPF（Open Shortest Path First）和BGP（Border Gateway Protocol）等。

动态路由的主要优势在于其自动性和适应性。它适用于大型复杂的网络，因为它能够适应网络拓扑的变化，而无需手动更新路由信息。然而，动态路由也可能引入一些安全和性能方面的考虑，因此需要适当的配置和监控。

### GNS3 console 模式介绍

**用户 EXEC 模式**
该模式下，提示符为“ Router>”，需要了解该模式下可以实用的命令，输入
“ ?”。
**特权 EXEC 模式**
查看 Cisco 路由器的系统参数，必需进入特权 EXEC 模式，输入命令：

```bash
Router1> enable
Password:
Router1#
```

**全局配置模式**
若需要修改系统范围内的配置参数，必需进入全局配置模式。输入命令：

```bash
Router1# configure terminal
Router1(config)#
```

**接口配置模式**
若要修改网络接口，需要进入接口配置模式。输入命令：

```bash
Router1(Config)#interface Ethernet 0/0
Router1(config-if)#
```

**返回**

- Exit 命令：层层返回，即退回到上一个命令层次。

- End 命令：从任何模式直接退回到特权 EXEC 模式。

- Disable 命令：从特权 EXEC 模式返回到用户 EXEC 模式。即

  ```bash
  Router1＃ disable
  Router1>
  ```

- Logout 命令：从用户 EXEC 模式终止控制台会话，输入 logout。



### GNS3命令简介

```bash
# 配置路由
## 注意！是目标的网络地址，不是IP地址！
R2(config)# ip route <目标网络地址> <子网掩码> <下一跳地址>

# 配置IP地址
R2(config)# ip address <设置的地址> <子网掩码> 
```

`no shutdown`：这是`interface`子配置模式下的命令，用于激活（启用）接口，使其可以传输数据。当接口处于"shutdown"状态时，通过输入`no shutdown`命令，可以将接口从禁用状态切换到启用状态。这通常用于启用已禁用的接口。

`ip routing` 是一个配置命令，用于在Cisco路由器上启用路由功能。在Cisco路由器上，这个命令通常用于打开路由功能，以使路由器能够根据路由表来决定如何将数据包从一个网络传输到另一个网络。



### 环境配置

GNS3环境配置可以参考这篇博文：https://www.cisco.com/c/zh_cn/support/docs/dial-access/floating-static-route/118263-technote-nexthop-00.html

IOU，IOS下载地址：https://ccie.lol/blog/2016/07/03/cisco-ios-image-download/

如果使用VirualBox等虚拟环境，遇到问题rc=-19...解决方法：https://stackoverflow.com/questions/38437264/i-cant-execute-command-modprobe-vboxdrv

GNS3 VM网卡设置：网卡一选择Host-Only，网卡二选择NAT



## 静态路由实验

### 网络拓扑图

![image-20231026113947314](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698291587.png)

先绘制好拓扑图：

放路由器，然后连线，点击全部start，然后依次打开他们的console。

![image-20231026154657115](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698306417.png)

### 设置IP地址

先对router2和4进行配置，设定他们的IP地址就行，操作都是一样的。

```bash
R4#show interface
FastEthernet0/0 is administratively down, line protocol is down 
  Hardware is DEC21140, address is ca02.0779.0000 (bia ca02.0779.0000)
  MTU 1500 bytes, BW 100000 Kbit/sec, DLY 100 usec, 
     reliability 255/255, txload 1/255, rxload 1/255
  Encapsulation ARPA, loopback not set
  Keepalive set (10 sec)
  Half-duplex, 100Mb/s, 100BaseTX/FX
  ARP type: ARPA, ARP Timeout 04:00:00
  Last input never, output 00:13:07, output hang never
  Last clearing of "show interface" counters never
  Input queue: 0/75/0/0 (size/max/drops/flushes); Total output drops: 0
  Queueing strategy: fifo
  Output queue: 0/40 (size/max)
  5 minute input rate 0 bits/sec, 0 packets/sec
  5 minute output rate 0 bits/sec, 0 packets/sec
     0 packets input, 0 bytes
     Received 0 broadcasts (0 IP multicasts)
     0 runts, 0 giants, 0 throttles 
     0 input errors, 0 CRC, 0 frame, 0 overrun, 0 ignored
     0 watchdog
     0 input packets with dribble condition detected
     0 packets output, 0 bytes, 0 underruns
          
R4#configure terminal
Enter configuration commands, one per line.  End with CNTL/Z.
R4(config)#interface FastEthernet0/0
R4(config-if)#ip address 12.5.10.2 255.255.255.0
R4(config-if)#no shut
R4(config-if)#ip routing
R4(config)#
*Oct 26 03:27:34.367: %LINK-3-UPDOWN: Interface FastEthernet0/0, changed state to up
*Oct 26 03:27:35.367: %LINEPROTO-5-UPDOWN: Line protocol on Interface FastEthernet0/0, changed state to up
R4(config)#exit
R4#
*Oct 26 03:27:38.723: %SYS-5-CONFIG_I: Configured from console by console
R4#wr
Warning: Attempting to overwrite an NVRAM configuration previously written
by a different version of the system image.
Overwrite the previous NVRAM configuration?[confirm]
Building configuration...
[OK]
```



按照表中设置好各个路由的IP地址之后，用ping命令进行测试：

R2：能pingR1，ping不通R4

![image-20231026120233150](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698292953.png)

R4：能ping通R1的12.5.10.1，R1的10.1.1.1不在同一子网，无法ping通；不能ping通R2

![image-20231026120422958](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698293063.png)

R1：对R2、R4都能ping通

![image-20231026120657573](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698293217.png)



### 设置静态路由

问题1：应该设置R2和R4的路由表，告诉他们对方是可达的，而不是设置R1的路由表。

问题2：设置静态路由`ip route`出现错误`%Inconsistent address and mask`

![image-20231026135108406](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698299468.png)



![image-20231026135132431](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698299492.png)

问题3：R2和R4的静态路由都设置好了，但就是ping不通

找了很久的原因，最后发现中间R1的Fa0/1没有配好IP地址。

查看命令`show ip interface bried`

![image-20231026153943835](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698305983.png)

配好之后：

![image-20231026154010352](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698306010.png)

然后就能完成R2 ping R4, R4 ping R2了。



最后展示一下R2和R4静态路由的设置

配置方法进入全局配置模式，有(config)标识，然后使用命令`ip route [目标网络地址] [子网掩码] [下一跳IP地址]`，最后记得wr保存配置。

![image-20231026154229269](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698306149.png)

![image-20231026154256526](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231026_1698306176.png)

![image-20231030105418501](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698634764.png)

### 联通性测试

![image-20231030105304357](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698634418.png)

![image-20231030105323164](https://raw.githubusercontent.com/sirius2alpha/Typora-pics/master/2023/10/upgit_20231030_1698634403.png)
