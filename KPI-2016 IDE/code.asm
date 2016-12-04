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

begina dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 10 
L02 dword 0 

.code
main PROC

invoke SetConsoleTitleA, offset cname

push 10
pop begina
mov EAX, begina
invoke WriteInt
invoke Crlf
mov eax, L02
ret 8
main ENDP

invoke WaitMsg
invoke ExitProcess, 0
end main