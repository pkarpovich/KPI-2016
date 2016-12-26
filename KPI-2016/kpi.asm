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

cname db 'KPI-2016 Compiler',0
L01 db 'in function factorial',0 
L02 dword 1 
L03 dword 25 
L04 dword 1 
L05 db 'KPI-2016 Translator',0 
L06 db 'new label',0 
L07 dword 3 
L08 db 'factorial: ',0 
L09 dword -1 
L10 dword 2 
L11 dword 5 
L12 dword 12 
L13 dword 12 
L14 dword 41 
L15 dword 31 
L16 dword 10 
L17 dword 32 
L18 dword 12 
L19 dword 20 
L20 dword 100 
L21 dword 2 
L22 dword 5 
L23 db 'exp: ',0 
L24 dword 25 
L25 db 'sqrt(25): ',0 
L26 dword 10 
L27 dword 8 
L28 db ' below 8',0 
L29 db ' abow 8',0 
L30 dword 0 

.code
kpixpow PROC USES ebx edx xpowx : SDWORD, xpowy : SDWORD
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
kpixpow ENDP

kpisqrt PROC USES ebx edx sqrtx : SDWORD
mov bufmath, 0
finit
fild sqrtx
fsqrt
fist bufmath
mov EAX, bufmath
ret
kpisqrt ENDP
kpifact PROC uses ebx ebp esi edi factn:dword
mov EDX, offset L01
invoke WriteString
call Crlf
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
pop eax
inc eax
push eax
pop factcount
jmp @circle1
@if1:
mov EAX, factres
ret
kpifact ENDP

main PROC

invoke SetConsoleTitleA, offset cname
invoke Str_copy, offset L05, offset beginlabel
mov EDX, offset beginlabel
invoke WriteString
call Crlf
invoke Str_copy, offset L06, offset beginlabel
mov EDX, offset beginlabel
invoke WriteString
call Crlf
push L07
call kpifact
push eax
pop beginfac
mov EDX, offset L08
invoke WriteString
push beginfac
call WriteInt
call Crlf
push L09
push L10
push L11
call kpixpow
push eax
push L12
push L13
pop ebx
pop eax
cdq
idiv ebx
push eax
push L14
push L15
pop eax
pop ebx
imul eax, ebx
push eax
push L16
pop ebx
pop eax
sub eax, ebx
push eax
push L17
push L18
pop ebx
pop eax
sub eax, ebx
push eax
push L19
pop eax
pop ebx
imul eax, ebx
push eax
pop eax
pop ebx
imul eax, ebx
push eax
push L20
pop ebx
pop eax
cdq
idiv ebx
push eax
pop ebx
pop eax
sub eax, ebx
push eax
pop eax
pop ebx
add eax, ebx
push eax
push L21
push L22
call kpixpow
push eax
pop eax
pop ebx
add eax, ebx
push eax
pop eax
pop ebx
imul eax, ebx
push eax
pop beginexp
mov EDX, offset L23
invoke WriteString
push beginexp
call WriteInt
call Crlf
push L24
call kpisqrt
push eax
pop beginexpTwo
mov EDX, offset L25
invoke WriteString
push beginexpTwo
call WriteInt
call Crlf
@circle2:
mov eax, L26
cmp eax, beginexpTwo
jle @if2
mov eax, L27
cmp eax, beginexpTwo
jge @if3
push beginexpTwo
call WriteInt
mov EDX, offset L28
invoke WriteString
call Crlf
jmp @endElse3
@if3:
push beginexpTwo
call WriteInt
mov EDX, offset L29
invoke WriteString
call Crlf
@endElse3:
push beginexpTwo
pop eax
inc eax
push eax
pop beginexpTwo
jmp @circle2
@if2:
invoke Crlf
call waitMsg
call ExitProcess
main ENDP
END main