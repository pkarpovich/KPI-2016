#pragma once
#define ASM_LIB ".586\n\
.model flat, stdcall\n\
includelib kernel32.lib\n\
ExitProcess PROTO,\n\
x:DWORD\n\
WaitMsg PROTO\n\
WriteString PROTO\n\
Crlf PROTO\n\n\
.data\n"

#define ASM_STR(literalName, literalValue) literalName<<" db "<<literalValue<<", 0"

#define ASM_BEGIN ".code\n main PROC\n"

#define ASM_END "main ENDP\n\
end main"

#define ASM_SOUT(literalValue) "mov EDX, offset "<<literalValue<< "\ninvoke WriteString\ninvoke Crlf\n"

#define ASM_RETURN "invoke WaitMsg\ninvoke ExitProcess, 0\n"


namespace Gen
{
	void Generator(Parm::PARM param, LA::LexAnaliz lex, std::stack<MFST::MfstState> storestate);
}