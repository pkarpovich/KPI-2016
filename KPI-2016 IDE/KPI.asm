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

sumres dword 0 
beginb dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 20 
L02 dword 50 
L03 dword 0 

.code
sum PROC uses ebx ebp esi edi suma:dword, sumb:dword
push 0
pop sumres
push suma
push sumb
pop eax
pop ebx
add eax, ebx
push eax
pop sumres
mov EAX, sumres
ret
sum ENDP

main PROC

invoke SetConsoleTitleA, offset cname

invoke sum, L01:dword, L02:dwordpop beginb
mov EAX, beginb
invoke WriteInt
invoke Crlf
mov EAX, L03
ret
main ENDP
END main