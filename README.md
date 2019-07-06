# ZwTerminateProcess

内核驱动，结束进程，一般没有结束不了的，包括各种安全卫士，类似PCHUNTER。

使用：

>打开测试模式：bcdedit /set testsigning on  然后重启。见到右下角有测试模式的水印。

>1，把TP.sys复制到C盘根目录。

>2，运行tp.bat就好了。

>3，输入PID。

注意：

>1，输入-1则会锁定控制文件(C:\krnldrvctrl.txt)，需要用PCHUNTER解锁。

>2，输入-2则会蓝屏，原理看代码（返回空指针）。
