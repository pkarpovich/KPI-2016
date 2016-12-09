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

blares dword 0 
beginres dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 0 
L02 dword 0 
L03 dword 70 
L04 dword 0 

.code
bla PROC uses ebx ebp esi edi blaa:dword, blab:dword
push eax

push 0
pop blares
push 0
pop blares
push blaa
push blab
pop eax
pop ebx
add eax, ebx
push eax
pop blares
mov EAX, blares
ret
bla ENDP

main PROC

invoke SetConsoleTitleA, offset cname

push 0
pop beginres
mov eax, L03
cmp eax, beginres
ja @if
mov EAX, beginres
invoke WriteInt
invoke Crlf
jmp @endElse
@if:
@endElse:
mov EAX, L04
ret
main ENDP
END main