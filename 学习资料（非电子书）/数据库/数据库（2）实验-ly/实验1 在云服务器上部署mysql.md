---
title: "在云服务器上部署mysql"
date: 2023-11-30
tags:
  - mysql
  - 云服务器
  - 实验
  - 数据库原理
categories:
  - 实践
description: "这篇文章记录了在两台主机上部署mysql"
draft: false
 
---



博客地址：sirius1y.top



## 实验要求

1．在云服务器上启动两个实例(server和client)，并实现在两个实例之间进行SSH免密登录。

2．在两个实例上安装MySQL，在server上创建数据库和用户，并在Client上远程连接Server的数据库。



## 实验步骤

### 购买两个2核4GB的实例，操作系统为ubuntu20.04

![图片1](https://s2.loli.net/2023/12/20/epAEDhdmkMJqWf7.png)

### 软件更新和安装

```bash
sudo apt-get update
sudo apt-get install vim
sudo apt-get install ssh
sudo spt-get install mysql-server
```



### SSH免密登录

在clinet端生成密钥，再把公钥添加到本地已认证的密钥中就可以实现本机对自己的免密登录。再把client上面的私钥公钥和已认证的密钥发送到server上，这样就能实现他们的相互免密登录。

```bash
ssh-keygen -t rsa -C yuanhao
cd ~/.ssh
cat id_rsa.pub > authorized_keys
scp id_rsa ubuntu@43.132.187.176:~/.ssh/id_rsa
scp id_rsa.pub ubuntu@43.132.187.176:~/.ssh/id_rsa.pub
scp authorized_keys ubuntu@43.132.187.176:~/.ssh/authorized_keys
```

之后可以使用cat对authorized_keys进行检查。

### client连接远程数据库

在server上安装mysql之后对mysql的配置文件进行修改，把绑定的端口从127.0.0.1改为0.0.0.0,以便于来自client的用户进行访问。

![图片2](https://s2.loli.net/2023/12/20/2NHBsJeAZ1VhfuQ.png)

![图片3](https://s2.loli.net/2023/12/20/oOkhI2RBy1ZfxWM.png)

之后在server的mysql中创建用户并赋予权限。

![图片4](https://s2.loli.net/2023/12/20/foXsiDxk3pGPtMN.png)

![图片5](https://s2.loli.net/2023/12/20/X2DbA6hv8quUMjH.png)

在server上创建一个数据库db1,然后在client上实现对server的mysql登录，这需要在服务器的安全组里放开3306端口。然后检查是否登陆成功，并且能够看到之前创建的db1.

![图片6](https://s2.loli.net/2023/12/20/A4N2XDiS1Yy8jKz.png)