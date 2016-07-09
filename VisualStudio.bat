@ECHO OFF

echo Downloading CMake...
echo:

SET CMAKEZIP=%TEMP%\cmake.zip
IF NOT EXIST "%CMAKEZIP%" powershell -Command (new-object System.Net.WebClient).DownloadFile('https://cmake.org/files/v3.6/cmake-3.6.0-win32-x86.zip', '%CMAKEZIP%')

echo Extracting CMake...
echo:

SET CMAKE=%TEMP%\cmake-3.6.0-win32-x86\bin\cmake.exe
IF NOT EXIST "%CMAKE%" Call :UnZipFile "%TEMP%" "%CMAKEZIP%"

echo Generating VS Project in "build" sub-directory...
echo:

if not exist "build" mkdir build
cd build
"%CMAKE%" -G "Visual Studio 14 2015 Win64" ..

echo Done
echo:
pause
exit

:unzipfile <extractto> <newzipfile>
set vbs="%temp%\_.vbs"
if exist %vbs% del /f /q %vbs%
>>%vbs% echo set objshell = createobject("shell.application")
>>%vbs% echo set filesinzip=objshell.namespace(%2).items
>>%vbs% echo objshell.namespace(%1).copyhere(filesinzip)
cscript //nologo %vbs%
if exist %vbs% del /f /q %vbs%
exit /b
