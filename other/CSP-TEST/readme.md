
## windows 安装 NOI linux


参考文章：《[CSP-J/S 备赛必学之环境准备](https://mp.weixin.qq.com/s/2CJBXOxT5lXoN_jNqDhaKQ)》  
NOI Linux 2.0 的系统镜像文件: https://noiresources.ccf.org.cn/download/ubuntu-noi-v2.0.iso
NOI 官网环境介绍地址：https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml
VMware Workstation Pro 虚拟机下载载地址：https://support.broadcom.com/group/ecx/free-downloads


根据官方公告介绍，2021 年 NOI Linux 2.0 的 G++ 版本是 9.3.0，最高支持 C++20 标准。  
当然，考试编译指令是 `g++ -std=c++14`，所以比赛中只能使用 C++14 标准。  
自己平常写测试工具时，可以使用 C++20 标准来提高开发效率。  



## Noi Linux 开启 SSH 服务

1. 打开终端，输入以下命令安装 OpenSSH 服务器：


```bash
sudo apt-get update
sudo apt-get install openssh-server
```

2. 安装完成后，启动 SSH 服务并设置为开机自启


```bash
sudo systemctl enable ssh
sudo systemctl start ssh
```


3. 查看 SSH 服务状态，确保其正在运行


```bash
sudo systemctl status ssh
```

4. 查看本机 IP 地址，记下以便远程连接使用

```bash
ip addr show
```  

如下，`192.168.59.129` 即为本机 IP 地址。  


```text
tiankonguse@ubuntu:~/noi/2025/HN/CSP-S$ ip addr show 
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000 
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00 
    inet 127.0.0.1/8 scope host lo 
        valid_lft forever preferred_lft forever 
    inet6 ::1/128 scope host 
        valid_lft forever preferred_lft forever 
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000 
    link/ether 00:0c:29:58:95:40 brd ff:ff:ff:ff:ff:ff 
    altname enp2s1 
    inet 192.168.59.129/24 brd 192.168.59.255 scope global dynamic noprefixroute ens33 
        valid_lft 1665sec preferred_lft 1665sec 
    inet6 fe80::4a01:ff92:5f50:baa0/64 scope link noprefixroute 
        valid_lft forever preferred_lft forever
```


## SSH 远程连接 NOI Linux  

下载 git for windows 并安装，安装过程中选择安装 OpenSSH 组件。  
下载地址： https://git-scm.com/install/windows


也可以在 Windows 的 PowerShell 中直接命令行安装 Git:  


```powershell
winget install --id Git.Git -e --source winget
```


然后打开 Git Bash 终端，使用以下命令连接到 NOI Linux 系统。  
其中 `tiankonguse` 替换为你的 NOI Linux 用户名，`192.168.59.129` 替换为你的 NOI Linux IP 地址：。


```bash
ssh tiankonguse@192.168.59.129
```

然后输入密码，即可登录。  


## SSH 免密码登录 NOI Linux  



打开 Git Bash 终端，生成 SSH 密钥对，命令如下，之后一路回车即可：   


```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```


然后把公钥复制到 NOI Linux 系统中，命令如下：  


```bash
ssh-copy-id -i ~/.ssh/id_ed25519.pub tiankonguse@192.168.59.129
```


最后免密登录  

```bash
ssh tiankonguse@192.168.59.129
```



映射别名，快捷登录  


```bash
vim ~/.ssh/config

Host noi
    HostName 192.168.59.129
    User tiankonguse
    IdentityFile ~/.ssh/id_ed25519
```



然后就可以通过以下命令快捷登录 NOI Linux 系统了：  


```bash
ssh noi
```

## SSH 上传下载文件到 NOI Linux  



## 关闭 虚拟机 linux 桌面  


虚拟机开启 linux 桌面会占用较多资源，建议关闭桌面，节省资源用于编译和测试。  


为了安全，这里只介绍临时关闭命令，不要永久关闭。  


```bash
sudo systemctl isolate multi-user.target
```


如果不小心永久关闭了桌面，可以通过以下命令重新开启：  


```bash
sudo systemctl set-default graphical.target
```

