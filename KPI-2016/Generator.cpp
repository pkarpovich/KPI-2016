#include "stdafx.h"
#include "Templates.h"
#define nt nible.table[i]
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
		GEN0(buf, ASM_GLOBAL);
		(*out.stream) << buf;

		char *lib = new char[1024]; strcpy(lib, "ExitProcess PROTO,\nx:DWORD\nWaitMsg PROTO\nCrlf PROTO\n WriteInt PROTO\nSetConsoleTitleA PROTO :DWORD\nWriteString PROTO\n");
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
		char *lexIden = new char[1024]; strcpy(lexIden, "\n.const\n\ncname db 'KPI-2016 Compiler ALPHA 3',0\n");
		stack<int> stack;
		for (int i = 0; i < nible.size; i++)
		{
			if (nt.TN == NT::INIT)
			{
				if(nt.TD == IT::DT_STR)	GEN2(buf, ASM_STR, nt.p2, nt.p3);
				else if(nt.TD == IT::DT_INT) GEN2(buf, ASM_INT, nt.p2, nt.p3);
				strcat(iden, buf);
				stack.push(i);
			}
			else if (nt.TN == NT::LEX_INIT)
			{
				if (nt.TD == IT::DT_STR)	GEN2(buf, ASM_STR, nt.p2, nt.p3);
				else if (nt.TD == IT::DT_INT) GEN2(buf, ASM_INT, nt.p2, nt.p3);
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
			case NT::KPILIB: Log::WriteTimplates(out, ASM_KPI_LIB); break;
			case NT::BEGIN:	GEN0(buf, ASM_BEGIN);Log::WriteTimplates(out, buf);	break;
			case NT::INT_D: GEN1(buf, ASM_INIT, nt.p2);	Log::WriteTimplates(out, buf);	break;
			case NT::INT_E:	GEN1(buf, ASM_INITE, nt.p2); Log::WriteTimplates(out, buf);	break;
			case NT::PLUS:	GEN0(buf, ASM_PLUS); Log::WriteTimplates(out, buf);	break;
			case NT::MINUS:	GEN0(buf, ASM_MINUS); Log::WriteTimplates(out, buf); break;
			case NT::MUL:	GEN0(buf, ASM_MUL);	Log::WriteTimplates(out, buf);	break;
			case NT::DIV:	GEN0(buf, ASM_DIV);	Log::WriteTimplates(out, buf);	break;
			case NT::IF:	GEN2(buf, ASM_IF, nt.p3, nt.p2); Log::WriteTimplates(out, buf);	break;
			case NT::MORE:	GEN0(buf, ASM_MORE); Log::WriteTimplates(out, buf);	break;
			case NT::LESS:	GEN0(buf, ASM_LESS); Log::WriteTimplates(out, buf);	break;
			case NT::ENDIF:	GEN0(buf, ASM_ENDIF); Log::WriteTimplates(out, buf); break;
			case NT::ENDELSE: GEN0(buf, ASM_ENDELSE); Log::WriteTimplates(out, buf); break;
			case NT::CIRCLE: GEN2(buf, ASM_CIRCLE, nt.p3, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::ENDCIRCLE:	GEN0(buf, ASM_CIRCLEEND); Log::WriteTimplates(out, buf); break;
			case NT::FUNC:	GEN1(buf, ASM_FUNC, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::PARAM_INIT: GEN1(buf, ASM_FUNC_PARAM, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::PARAM_SECOND_INIT: GEN1(buf, ASM_FUNC_SECOND_PARAM, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::STARTFUNC:	GEN0(buf, ASM_FUNC_START); Log::WriteTimplates(out, buf); break;
			case NT::RETURN:	GEN1(buf, ASM_FUNC_RETURN, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::ENDFUNC:	GEN1(buf, ASM_FUNC_END, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::ENDMAINFUNC: GEN0(buf, ASM_MAIN_FUNC_END); Log::WriteTimplates(out, buf); break;
			case NT::FUNCINVOKE:GEN1(buf, ASM_INVOKE_FUNC, nt.p2); Log::WriteTimplates(out, buf); break;
			case NT::FANCPARAM:	GEN1(buf, ASM_INVOKE_PARAM, nt.p2);	Log::WriteTimplates(out, buf);break;
			case NT::PUSHINVOKE:GEN0(buf, ASM_PUSH_INVOKE);	Log::WriteTimplates(out, buf); break;
			case NT::PRINT:
				if (nt.TD == IT::DT_STR) GEN1(main, ASM_SPRINT, nt.p2);	else if (nt.TD == IT::DT_INT)	GEN1(main, ASM_IPRINT, nt.p2);
				if (strcmp(nt.p3, "endl") == 0) { GEN0(buf, ASM_ENDL); strcat(main, buf); }	Log::WriteTimplates(out, main);	break;
			}
		}
		Print(nible);
		Log::Close(out);
	}
}
