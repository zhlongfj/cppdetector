echo off
setlocal enabledelayedexpansion

set codepath=%1
set codepath=%codepath:\=/%
set YYYYmmdd=%date:~0,4%%date:~5,2%%date:~8,2%
set hhmiss=%time:~0,2%%time:~3,2%%time:~6,2%
set "hhmiss=%hhmiss: =0%"
set withTime=%YYYYmmdd%_%hhmiss%

set cur=%~dp0
set filePath=%cur%filenames%withTime%.json
echo the json file path of checking file paths: %filepath%

set driveDir=%codepath:~0,2%
%driveDir%
cd %codepath%
echo  %driveDir%

for /F %%i in ('git rev-parse --short head') do ( set headcommitid=%%i)
echo headcommitid=%headcommitid%

for /F %%i in ('git rev-parse --short head~1') do ( set previouscommitid=%%i)
echo previouscommitid=%previouscommitid%

echo begin writing json file...
echo [ >> %filePath%
set file=0
set prefile=0
set n=0
for /F %%i in ('git diff --name-only %previouscommitid% %headcommitid%') do (
 set /a n+=1
 if !n! GTR 1 (
	set prefile=!file!
	echo "%codepath%/!prefile!", >> %filePath%
 )
 set file=%%i
 echo %codepath%/!prefile!
)
echo %codepath%/%file%
echo "%codepath%/%file%" >> %filePath%
echo ] >> %filePath%

echo end writing json file...

call %cur%cppdetector\cppdetector.exe multithread %filePath% %cur%\config\exceptionconfig.json %cur%\config\detectorRuleNames.json %cur%detectorResult
set reterror=%errorlevel%
if %errorlevel% neq 0 (
	echo find issue...
)
if exist %filePath% (
	del %filePath% /q
)
goto endOfFile

@echo off
set n=
(for /f "delims=" %%a in ('dir /a-d/b 文件夹名称') do (
    if defined n echo ,
    set n=1
    set /p "s=%%a"<nul
)) > 保存文件名
goto endOfFile

set ddd="dd"
::git log -2 --pretty=format:"%%h" >> %ddd%
::git log -2 --name-only > %ddd%
::git log -1 --name-only >> %ddd%
::echo %ddd% 
::git diff --name-only 774468a3 fb38df81
::git log -2
::git rev-parse --short head -2

git log -1 --name-only

for /F %%i in ('git diff --name-only %previouscommitid% %headcommitid%') do (
 set file=%%i
 echo %%i)
::git log -2 --name-only
::pause
::for /F %%i in ('git log -2 --name-only') do ( set file=%%i)
::echo file=%file%
::pause      
for /f "delims=" %%i in ('git diff --name-only %previouscommitid% %headcommitid%') do        
  echo %%i

pause  
for /F "Delims=" %%A In ('git diff --name-only %previouscommitid% %headcommitid%') Do Set "result=%%A"
echo %result%
pause
for /F %%i in ('git diff --name-only %previouscommitid% %headcommitid%') do ( set file=%%i echo file=%file%)
echo file=%file%

:endOfFile
exit /b %reterror%