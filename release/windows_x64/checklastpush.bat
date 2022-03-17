echo off
::set codepath=D:\gitRepo\viplexcore
set codepath=F:\work\git\viplexcore
call checklastpushcore.bat %codepath%
echo %errorlevel%
pause