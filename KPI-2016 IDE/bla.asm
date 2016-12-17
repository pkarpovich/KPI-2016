.586
.model flat, stdcall
includelib kernel32.lib
ExitProcess PROTO,
x:DWORD
WaitMsg PROTO
Crlf PROTO
 WriteInt PROTO
SetConsoleTitleA PROTO :DWORD
WriteString PROTO

.data
bufmath sdword ?
begina dword 0 

.const

cname db 'KPI-2016 Compiler RC1',0
L01 dword 99 
L02 db 'Hello icewave',0 
L03 dword 0 

.code
main PROC

invoke SetConsoleTitleA, offset cname

push 99
pop begina
mov EDX, offset L02
invoke WriteString
invoke Crlf
mov EAX, L03
ret
main ENDP
END main