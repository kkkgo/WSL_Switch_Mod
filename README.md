# WSL_Switch_Mod
自用小工具，为WSL2固定IP和网关

## 原理
1、WSL2每次启动的时候会检查创建一个WSL交换机，随机分配IP网关，虽然只会创建一次，但每次重启后就会自动删掉，每次IP都不一样，这可能会给网络应用调试带来麻烦。   
2、在开机后使用WSL之前运行本程序，会创建一个固定IP网关的WSL交换机，这样启动WSL的时候就会跳过检查创建的步骤。

## 使用方法
0、[下载程序](https://github.com/kkkgo/WSL_Switch_Mod/releases)  
1、重启系统后，先不要打开WSL。运行本程序  
2、如果你得到类似以下输出，说明运行成功：
>========================================
0x0
WSL switch successfully created.
default via 192.168.114.1 dev eth0
192.168.114.0/30 dev eth0 proto kernel scope link src 192.168.114.2

现在你得到了一个指定IP的交换机（如果需要其他网段，可以修改源码自己编译即可）：
>网络地址：192.168.114.0
网关：192.168.114.1
WSL IP：192.168.114.2
    广播地址：192.168.114.3

## 创建计划任务开机启动
假设你的WSL_Switch_Mod.exe在C:\tools  
```
schtasks.exe /create /tn "WSL_Switch_Mod" /ru SYSTEM /sc ONSTART /tr "C:\tools\WSL_Switch_Mod.exe"
```

## 删除计划任务
```
schtasks /delete /tn WSL_Switch_Mod
```
