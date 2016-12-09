@echo off

if exist %1.obj del %1.obj
if exist %1.exe del %1.exe

pause
c:\masm32\bin\ml /c /coff %1.asm
if errorlevel 1 goto errasm


c:\masm32\bin\link /subsystem:console /out:%1.exe /libpath:c:\masm32 /libpath:c:\irvine user32.lib irvine32.lib kernel32.lib user32.lib /machine:x86 %1.obj
if errorlevel 1 goto errlink

start %1.exe
goto TheEnd

:errlink
echo _
echo Link error
goto TheEnd

:errasm
echo _
echo Assembly Error
goto TheEnd

:TheEnd

pause