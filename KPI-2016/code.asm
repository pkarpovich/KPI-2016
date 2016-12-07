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

beginres dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 0 
L02 dword 20 
L03 dword 90 
L04 dword 70 
L05 dword 0 

.code
main PROC

invoke SetConsoleTitleA, offset cname

push 0
pop beginres
push 20
pop beginres
push L02
push L03
pop eax
pop ebx
add eax, ebx
push eax
pop beginres
mov eax, L04
cmp eax, beginres
ja @if
mov EAX, beginres
invoke WriteInt
invoke Crlf
jmp @endElse
@if:
@endElse:
mov EAX, L05
ret
main ENDP
END main