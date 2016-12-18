#include "stdafx.h"
#include "Templates.h"
#define nt nible.table[i]
#define OUT(tmpl, ...) GEN(buf, tmpl, __VA_ARGS__); Log::WriteLine(out, buf, "");
namespace Gen
{
	void Generator(Parm::PARM param, NT::Nible nible)
	{
		Log::LOG out = Log::INITLOG;
		wchar_t buff[50];
		wcscpy(buff, param.out);
		wcscat(buff, L".asm");
		out = Log::getlog(buff);
	
		char *buf = new char[1024];
		GEN(buf, ASM_GLOBAL);
		(*out.stream) << buf;

		char *lib = new char[1024]; strcpy(lib, "ExitProcess PROTO,\nx:DWORD\nWaitMsg PROTO\nCrlf PROTO\n WriteInt PROTO\nStr_copy PROTO :DWORD, :DWORD\nSetConsoleTitleA PROTO :DWORD\nWriteString PROTO\n");
		/*for (auto it : nible.component)
		{
			switch (it)
			{
			case NT::SPRINT: GEN0(buf, ASM_INCLUDE_SPRINT); strcat(lib, buf); break;
			case NT::IPRINT: GEN0(buf, ASM_INCLUDE_IPRINT); strcat(lib, buf); break;
			}
		}*/
		(*out.stream) << lib;

		char *iden = new char[1024]; strcpy(iden, "\n.data\nbufmath sdword ?\n");
		char *lexIden = new char[1024]; strcpy(lexIden, "\n.const\n\ncname db 'KPI-2016 Compiler RC1',0\n");
		stack<int> stack;
		for (int i = 0; i < nible.size; i++)
		{
			if (nt.TN == NT::INIT)
			{
				if(nt.TD == IT::DT_STR)	GEN(buf, ASM_STR, nt.p2, nt.p3);
				else if(nt.TD == IT::DT_INT) GEN(buf, ASM_INT, nt.p2, nt.p3);
				strcat(iden, buf);
				stack.push(i);
			}
			else if (nt.TN == NT::LEX_INIT)
			{
				if (nt.TD == IT::DT_STR)	GEN(buf, ASM_STR, nt.p2, nt.p3);
				else if (nt.TD == IT::DT_INT) GEN(buf, ASM_INT, nt.p2, nt.p3);
				strcat(lexIden, buf);
				stack.push(i);
			}
		}
		while (!stack.empty())
		{
			Delete(nible, nible.table[stack.top()]);
			stack.pop();
		}
		(*out.stream) << iden;
		(*out.stream) << lexIden;

		(*out.stream) << "\n.code\n";

		char *main = new char[1024]; main[0] = '\0';

		for (int i = 0; i < nible.size; i++)
		{
			switch (nt.TN)
			{
			case NT::KPI_LIB: Log::WriteLine(out, ASM_KPI_LIB, ""); break;
			case NT::BEGIN:				OUT(ASM_BEGIN); break;
			case NT::PUSH:				OUT(ASM_INIT, nt.p2); break;
			case NT::POP:				OUT(ASM_INITE, nt.p2); break;
			case NT::PLUS:				OUT(ASM_PLUS); break;
			case NT::MINUS:				OUT(ASM_MINUS); break;
			case NT::MUL:				OUT(ASM_MUL); break;
			case NT::DIV:				OUT(ASM_DIV); break;
			case NT::IF:				OUT( ASM_IF, nt.p3, nt.p2);	break;
			case NT::MORE:				OUT( ASM_MORE, nt.p2); break;
			case NT::LESS:				OUT( ASM_LESS, nt.p2); break;
			case NT::END_IF:			OUT( ASM_ENDIF, nt.p2, nt.p2); break;
			case NT::END_ELSE:			OUT( ASM_ENDELSE, nt.p2);break;
			case NT::CIRCLE:			OUT(ASM_CIRCLE,nt.p4, nt.p3, nt.p2); break;
			case NT::END_CIRCLE:		OUT( ASM_CIRCLEEND, nt.p2, nt.p2); break;
			case NT::FUNC:				OUT( ASM_FUNC, nt.p2); break;
			case NT::PARAM_INIT:		OUT( ASM_FUNC_PARAM, nt.p2); break;
			case NT::PARAM_SECOND_INIT: OUT( ASM_FUNC_SECOND_PARAM, nt.p2); break;
			case NT::START_FUNC:		OUT( ASM_FUNC_START); break;
			case NT::RETURN:			OUT( ASM_FUNC_RETURN, nt.p2); break;
			case NT::END_FUNC:			OUT( ASM_FUNC_END, nt.p2); break;
			case NT::END_MAIN_FUNC:		OUT(ASM_MAIN_FUNC_END); break;
			case NT::FUNC_INVOKE:		OUT( ASM_INVOKE_FUNC, nt.p2); break;
			case NT::FANC_PARAM:		OUT(ASM_INVOKE_PARAM, nt.p2); break;
			case NT::PUSH_INVOKE:		OUT(ASM_PUSH_INVOKE); break;
			case NT::STR_PUSH:			OUT( ASM_STR_INIT, nt.p2, nt.p3); break;
			case NT::PRINT:
				if (nt.TD == IT::DT_STR) GEN(main, ASM_SPRINT, nt.p2);	else if (nt.TD == IT::DT_INT)	GEN(main, ASM_IPRINT, nt.p2);
				if (strcmp(nt.p3, "endl") == 0) { GEN(buf, ASM_ENDL); strcat(main, buf); }	Log::WriteLine(out, main, "");	break;
			}
		}
		Log::Close(out);
	}
}
