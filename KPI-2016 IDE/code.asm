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

suma dword 0 
sumres dword 0 
begina dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 0 
L02 dword 0 
L03 dword 99 
L04 dword 20 
L05 dword 0 
L06 dword 50 
L07 dword 4 
L08 dword 0 

.code
sum PROC uses ebx ebp esi edi, suma:dword, sumb:dwordpush 0
pop sumres
push 0
pop sumres
push suma
push sumb
pop eax
pop ebx
add eax, ebx
push eax
pop sumres
main PROC

invoke SetConsoleTitleA, offset cname
push 0
pop begina
push 99
pop begina
push L03
push L04
pop eax
pop ebx
add eax, ebx
push eax
pop begina
mov EAX, begina
invoke WriteInt
invoke Crlf
push 0
pop beginres
invoke sum, L06, L07pop beginres
mov EAX, begina
invoke WriteInt
invoke Crlf
invoke Crlf
invoke WaitMsg
invoke ExitProcess, 0
main ENDP
end main