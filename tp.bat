@sc stop TP
@sc delete TP
:start
set /P pid="INPUT PID:"
echo %pid% > C:\krnldrvctrl.txt
@sc create TP binPath= "C:\TP.sys" type= kernel
@sc start TP
@sc stop TP
@sc delete TP
goto start