#pragma once
#define GEN(buf, tmpl, ...)		sprintf_s(buf, 1024, tmpl, __VA_ARGS__)

#define ASM_GLOBAL ".586\n.model flat, stdcall\nincludelib kernel32.lib\n"

#define ASM_INCLUDE_SPRINT "WriteString PROTO\n"
#define ASM_INCLUDE_IPRINT "WriteDec PROTO\n"

#define ASM_STR "%s db %s,0 \n"
#define ASM_INT "%s dword %s \n"

#define ASM_SPRINT "mov EDX, offset %s\ninvoke WriteString\n"
#define ASM_IPRINT "push %s\ncall WriteInt\n"
#define ASM_ENDL "call Crlf\n"

#define ASM_MAIN ".code\n "
#define ASM_BEGIN "main PROC\n\ninvoke SetConsoleTitleA, offset cname\n"

#define ASM_INIT "push %s\n"
#define ASM_INITE "pop %s\n"
#define ASM_STR_INIT "invoke Str_copy, offset %s, offset %s\n"

#define ASM_INC "pop eax\ninc eax\npush eax\n"
#define ASM_DEC "pop eax\ndec eax\npush eax\n"
#define ASM_PLUS "pop eax\npop ebx\nadd eax, ebx\npush eax\n"
#define ASM_MINUS "pop ebx\npop eax\nsub eax, ebx\npush eax\n"
#define ASM_MUL "pop eax\npop ebx\nimul eax, ebx\npush eax\n"
#define ASM_DIV "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n"

#define ASM_IF "mov eax, %s\ncmp eax, %s\n"
#define ASM_LESS "jle @if%s\n"
#define ASM_LESS_OR_EQUALLY "jl @if%s\n"
#define ASM_MORE "jge @if%s\n"
#define ASM_MORE_OR_EQUALLY "jg @if%s\n"
#define ASM_EQUALITY "jne @if%s\n"
#define ASM_NO_EQUALITY "je @if%s\n"
#define ASM_ENDIF "jmp @endElse%s\n@if%s:\n"
#define ASM_ENDELSE "@endElse%s:\n"

#define ASM_CIRCLE "@circle%s:\nmov eax, %s\ncmp eax, %s\n"
#define ASM_CIRCLEEND "jmp @circle%s\n@if%s:\n"

#define ASM_FUNC "%s PROC uses ebx ebp esi edi"
#define ASM_FUNC_PARAM " %s:dword"
#define ASM_FUNC_SECOND_PARAM ", %s:dword"
#define ASM_FUNC_START "\n"
#define ASM_FUNC_RETURN "mov EAX, %s\nret\n"
#define ASM_FUNC_END "%s ENDP\n\n"
#define ASM_MAIN_FUNC_END "invoke Crlf\ncall waitMsg\ncall ExitProcess\nmain ENDP\nEND main"

#define ASM_INVOKE_FUNC "call %s\npush eax\n"
#define ASM_INVOKE_PARAM "push %s\n"
#define ASM_PUSH_INVOKE "\npush eax\n"

#define ASM_END "invoke WaitMsg\ninvoke ExitProcess, 0\nretinvoke WaitMsg\ninvoke ExitProcess, 0\n"




//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define ASM_KPI_LIB "kpixpow PROC USES ebx edx xpowx : SDWORD, xpowy : SDWORD\n\
mov bufmath, 0\n\
fild xpowy\n\
fild xpowx\n\
fyl2x\n\
fld st(0)\n\
frndint\n\
fxch st(1)\n\
fsub st(0), st(1)\n\
f2xm1\n\
fld1\n\
faddp st(1), st\n\
fscale\n\
fistp bufmath\n\
mov eax, bufmath\n\
ret\n\
kpixpow ENDP\n\
\n\
kpisqrt PROC USES ebx edx sqrtx : SDWORD\n\
mov bufmath, 0\n\
finit\n\
fild sqrtx\n\
fsqrt\n\
fist bufmath\n\
mov EAX, bufmath\n\
ret\n\
kpisqrt ENDP\n"