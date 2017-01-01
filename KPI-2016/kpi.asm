.586
.model flat, stdcall
includelib kernel32.lib
ExitProcess PROTO,
x:DWORD
WaitMsg PROTO
Crlf PROTO
 WriteInt PROTO
Str_copy PROTO :DWORD, :DWORD
SetConsoleTitleA PROTO :DWORD
WriteString PROTO

.data
bufmath sdword ?
begini dword 0 

.const

cname db 'KPI-2016 Compiler',0
L01 dword 0 
L02 dword 5 
L03 dword 0 

.code
main PROC

invoke SetConsoleTitleA, offset cname
push L01
pop begini
@circle1:
mov eax, L02
cmp eax, begini
jle @if1
mov EAX, begini
invoke WriteInt
invoke Crlf
push begini
pop eax
inc eax
push eax
pop begini
jmp @circle1
@if1:
invoke Crlf
call waitMsg
call ExitProcess
main ENDP
END main