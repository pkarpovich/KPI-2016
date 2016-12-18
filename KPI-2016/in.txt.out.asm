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
factres dword 0 
factcount dword 0 
beginlabel db 0,0 
beginfac dword 0 
beginexp dword 0 
beginexpTwo dword 0 

.const

cname db 'KPI-2016 Compiler RC1',0
L01 db 'in function factorial',0 
L02 dword 1 
L03 dword 2 
L04 dword 1 
L05 dword 1 
L06 db 'KPI-2016 Translator',0 
L07 db 'andrey',0 
L08 dword 3 
L09 db 'factorial: ',0 
L10 dword 7 
L11 dword 12 
L12 dword 12 
L13 dword 41 
L14 dword 31 
L15 dword 10 
L16 dword 32 
L17 dword 12 
L18 dword 20 
L19 dword 100 
L20 dword 2 
L21 dword 5 
L22 db 'exp: ',0 
L23 dword 25 
L24 db 'sqrt(25): ',0 
L25 dword 10 
L26 dword 8 
L27 db ' below 8',0 
L28 db ' abow 8',0 
L29 dword 1 
L30 dword 0 

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
fact PROC uses ebx ebp esi edi factn:dword
mov EDX, offset L01
invoke WriteString
invoke Crlf
push L02
pop factres
push L03
pop factcount
push factn
push L04
pop eax
pop ebx
add eax, ebx
push eax
pop factn
@circle1:
mov eax, factn
cmp eax, factcount
jle @if1
push factres
push factcount
pop eax
pop ebx
imul eax, ebx
push eax
pop factres
push factcount
push L05
pop eax
pop ebx
add eax, ebx
push eax
pop factcount
jmp @circle1
@if1:
mov EAX, factres
ret
fact ENDP

main PROC

invoke SetConsoleTitleA, offset cname
invoke Str_copy, offset L06, offset beginlabel
mov EDX, offset beginlabel
invoke WriteString
invoke Crlf
invoke Str_copy, offset L07, offset beginlabel
mov EDX, offset beginlabel
invoke WriteString
invoke Crlf
invoke fact, L08
push eax
pop beginfac
mov EDX, offset L09
invoke WriteString
mov EAX, beginfac
invoke WriteInt
invoke Crlf
invoke fact, L10
push eax
push L11
push L12
pop ebx
pop eax
cdq
div ebx
push eax
push L13
push L14
pop eax
pop ebx
imul eax, ebx
push eax
push L15
pop ebx
pop eax
sub eax, ebx
push eax
push L16
push L17
pop ebx
pop eax
sub eax, ebx
push eax
push L18
pop eax
pop ebx
imul eax, ebx
push eax
pop eax
pop ebx
imul eax, ebx
push eax
push L19
pop ebx
pop eax
cdq
div ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
pop eax
pop ebx
add eax, ebx
push eax
invoke xpow, L20, L21
push eax
pop eax
pop ebx
add eax, ebx
push eax
pop beginexp
mov EDX, offset L22
invoke WriteString
mov EAX, beginexp
invoke WriteInt
invoke Crlf
invoke sqrt, L23
push eax
pop beginexpTwo
mov EDX, offset L24
invoke WriteString
mov EAX, beginexpTwo
invoke WriteInt
invoke Crlf
@circle2:
mov eax, L25
cmp eax, beginexpTwo
jle @if2
mov eax, L26
cmp eax, beginexpTwo
jge @if3
mov EAX, beginexpTwo
invoke WriteInt
mov EDX, offset L27
invoke WriteString
invoke Crlf
jmp @endElse3
@if3:
mov EAX, beginexpTwo
invoke WriteInt
mov EDX, offset L28
invoke WriteString
invoke Crlf
@endElse3:
push beginexpTwo
push L29
pop eax
pop ebx
add eax, ebx
push eax
pop beginexpTwo
jmp @circle2
@if2:
mov EAX, L30
ret
main ENDP
END main