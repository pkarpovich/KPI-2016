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

maxres dword 0 
begina dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 0 
L02 dword 0 
L03 dword 1 
L04 dword 2 
L05 dword 5 
L06 dword 0 

.code
max PROC uses ebx ebp esi edi, maxi:dword, maxb:dword
push maxi
push maxb
pop eax
pop ebx
add eax, ebx
push eax
pop maxres
mov eax, maxres
ret 8
max ENDP

main PROC

invoke SetConsoleTitleA, offset cname

invoke max, L04, L05
push eax
push L03
pop eax
pop ebx
add eax, ebx
push eax
pop begina
mov EAX, begina
invoke WriteInt
mov eax, L06
ret 8
main ENDP

invoke WaitMsg
invoke ExitProcess, 0
end main