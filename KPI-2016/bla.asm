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
mulmmull dword 0 
sumres dword 0 
begintest dword 0 
L03 dword 12 
L05 dword 41 
L08 dword 32 
beginlib dword 0 
begini dword 0 

.const

cname db 'KPI-2016 Compiler ALPHA 3',0
L01 dword 2 
L02 dword 2 
L04 dword 12 
L06 dword 31 
L07 dword 10 
L09 dword 12 
L10 dword 20 
L11 dword 100 
L12 dword 0 
L13 dword 0 
L14 dword 25 
L15 dword 5 
L16 dword 4 
L17 dword 0 
L18 dword 10 
L19 dword 1 
L20 dword 20 
L21 dword 2 
L22 dword 0 

.code
xpow PROC USES ebx edx xpowx : SDWORD, xpowy : SDWORD
mov bufmath, 0
fild xpowy
fild xpowx
fyl2x
fld st(0)
frndint
fxch st(1)
fsub st(0), st(1)
f2xm1
fld1
faddp st(1), st
fscale
fistp bufmath
mov eax, bufmath
ret
xpow ENDP

sqrt PROC USES ebx edx sqrtx : SDWORD
mov bufmath, 0
finit
fild sqrtx
fsqrt
fist bufmath
mov EAX, bufmath
ret
sqrt ENDP
mulm PROC uses ebx ebp esi edi mulma:dword, mulmb:dword
push mulma
push mulmb
pop eax
pop ebx
imul eax, ebx
push eax
pop mulmmull
mov EAX, mulmmull
ret
mulm ENDP

sum PROC uses ebx ebp esi edi suma:dword, sumb:dword
push suma
push sumb
pop eax
pop ebx
add eax, ebx
push eax
invoke mulm, L01, L02
push eax
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

push L03
push L04
pop ebx
pop eax
cdq
div ebx
push eax
push L05
push L06
pop eax
pop ebx
imul eax, ebx
push eax
push L07
pop ebx
pop eax
sub eax, ebx
push eax
push L08
push L09
pop ebx
pop eax
sub eax, ebx
push eax
push L10
pop eax
pop ebx
imul eax, ebx
push eax
pop eax
pop ebx
imul eax, ebx
push eax
push L11
pop ebx
pop eax
cdq
div ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
invoke sum, L12, L13
push eax
pop eax
pop ebx
add eax, ebx
push eax
invoke xpow, L14, L15
push eax
pop eax
pop ebx
add eax, ebx
push eax
pop begintest
invoke sqrt, L16
push eax
pop beginlib
mov EAX, beginlib
invoke WriteInt
invoke Crlf
mov EAX, begintest
invoke WriteInt
invoke Crlf
push 0
pop begini
@circle:
mov eax, L18
cmp eax, begini
jb @if
mov EAX, begini
invoke WriteInt
invoke Crlf
push begini
push L19
pop eax
pop ebx
add eax, ebx
push eax
pop begini
jmp @circle
@if:
push 20
pop begintest
push 2
pop begini
mov EAX, L22
ret
main ENDP
END main