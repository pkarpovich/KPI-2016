@echo off
start ml /c /coff "code.asm"
start link /subsystem:console /out:"prog.exe" /libpath:c:\masm32 /libpath:c:\irvine user32.lib irvine32.lib kernel32.lib user32.lib /machine:x86 /safeseh:no code.obj
pause
start prog.exe