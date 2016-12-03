@echo off
start c:\masm32\bin\ml /c /coff "code.asm"
start c:\masm32\bin\link /subsystem:console /out:"prog.exe" /libpath:c:\masm32 /libpath:c:\irvine user32.lib irvine32.lib kernel32.lib user32.lib /machine:x86 /safeseh:no code.obj
pause
start prog.exe