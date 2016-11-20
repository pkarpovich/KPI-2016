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

powres dword 0 
powcount dword 1 
begina dword 2 
beginb dword 5 
beginres dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 0 
L02 dword 1 
L03 dword 1 
L04 dword 2 
L05 dword 5 
L06 dword 0 

.code
pow PROC uses ebx ebp esi edi, powa:dword, powb:dword
@circle:
mov eax, powcount
cmp eax, powb
ja @if

push powa
push powcount
pop eax
pop ebx
imul eax, ebx
push eax
pop powres
push powcount
push L03
pop eax
pop ebx
add eax, ebx
push eax
pop powcount
jmp @circle
@if:
mov eax, powres
ret 8
pow ENDP

main PROC

invoke SetConsoleTitleA, offset cname
invoke pow, begina, beginb
push eax
pop beginres
mov EAX, beginres
invoke WriteInt
invoke WaitMsg
invoke ExitProcess, 0
main ENDP
end main