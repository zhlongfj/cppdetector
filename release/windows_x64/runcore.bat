set cur=%~dp0
%~dp0cppdetector\cppdetector.exe multithread %1 %cur%config\exceptionconfig.json %cur%config\detectorRuleNames.json %cur%detectorResult
set reterror=%errorlevel%
echo %reterror%
exit /b %reterror%