#include "stdafx.h"
#include "Templates.h"
#define nt nible.table[i]
#define WRITE(tmpl, ...) GEN(buf, tmpl, __VA_ARGS__); Log::WriteLine(out, buf, "");
namespace Gen
{
	void Generator(Parm::PARM param, NT::Nible nible)
	{
		Log::LOG out = Log::INITLOG;
		wchar_t paramOut[50];
		wcscpy_s(paramOut, 50, param.out);
		wcscat_s(paramOut, 50, L".asm");
		out = Log::getlog(paramOut);
	
		char *buf = new char[1024];
		GEN(buf, ASM_GLOBAL);
		Log::WriteLine(out, buf, "");

		char *lib = new char[1024]; strcpy_s(lib, 1024, "ExitProcess PROTO,\nx:DWORD\nWaitMsg PROTO\nCrlf PROTO\n WriteInt PROTO\nStr_copy PROTO :DWORD, :DWORD\nSetConsoleTitleA PROTO :DWORD\nWriteString PROTO\n");
		Log::WriteLine(out, lib, "");

		char *iden = new char[1024]; strcpy_s(iden, 1024, "\n.data\nbufmath sdword ?\n");
		char *lexIden = new char[1024]; strcpy_s(lexIden, 1024, "\n.const\n\ncname db 'KPI-2016 Compiler',0\n");

		for (int i = 0; i < nible.size; i++)
		{
			if (nt.TN == NT::INIT)
			{
				if(nt.TD == IT::DT_STR)	GEN(buf, ASM_STR, nt.p2, nt.p3);
				else if(nt.TD == IT::DT_INT) GEN(buf, ASM_INT, nt.p2, nt.p3);
				strcat_s(iden, 1024, buf);
			}
			else if (nt.TN == NT::LEX_INIT)
			{
				if (nt.TD == IT::DT_STR)	GEN(buf, ASM_STR, nt.p2, nt.p3);
				else if (nt.TD == IT::DT_INT) GEN(buf, ASM_INT, nt.p2, nt.p3);
				strcat_s(lexIden, 1024, buf);
			}
		}
		Log::WriteLine(out, iden, "");
		Log::WriteLine(out, lexIden, "");

		Log::WriteLine(out, "\n.code\n", "");

		char *main = new char[1024]; main[0] = '\0';

		for (int i = 0; i < nible.size; i++)
		{
			switch (nt.TN)
			{
			case NT::KPI_LIB:			Log::WriteLine(out, ASM_KPI_LIB, ""); break;
			case NT::BEGIN:				WRITE(ASM_BEGIN); break;
			case NT::PUSH:				WRITE(ASM_INIT, nt.p2); break;
			case NT::POP:				WRITE(ASM_INITE, nt.p2); break;
			case NT::PLUS:				WRITE(ASM_PLUS); break;
			case NT::MINUS:				WRITE(ASM_MINUS); break;
			case NT::MUL:				WRITE(ASM_MUL); break;
			case NT::DIV:				WRITE(ASM_DIV); break;
			case NT::INC:				WRITE(ASM_INC); break;
			case NT::DEC:				WRITE(ASM_DEC); break;
			case NT::IF:				WRITE( ASM_IF, nt.p3, nt.p2);	break;
			case NT::MORE:				WRITE( ASM_MORE, nt.p2); break;
			case NT::MORE_OR_EQUALLY:	WRITE( ASM_MORE_OR_EQUALLY, nt.p2); break;
			case NT::LESS:				WRITE( ASM_LESS, nt.p2); break;
			case NT::LESS_OR_EQUALLY:	WRITE( ASM_LESS_OR_EQUALLY, nt.p2); break;
			case NT::EQUALITY:			WRITE( ASM_EQUALITY, nt.p2); break;
			case NT::NO_EQUALITY:		WRITE( ASM_NO_EQUALITY, nt.p2); break;
			case NT::END_IF:			WRITE( ASM_ENDIF, nt.p2, nt.p2); break;
			case NT::END_ELSE:			WRITE( ASM_ENDELSE, nt.p2);break;
			case NT::CIRCLE:			WRITE(ASM_CIRCLE,nt.p4, nt.p3, nt.p2); break;
			case NT::END_CIRCLE:		WRITE( ASM_CIRCLEEND, nt.p2, nt.p2); break;
			case NT::FUNC:				WRITE( ASM_FUNC, nt.p2); break;
			case NT::PARAM_INIT:		WRITE( ASM_FUNC_PARAM, nt.p2); break;
			case NT::PARAM_SECOND_INIT: WRITE( ASM_FUNC_SECOND_PARAM, nt.p2); break;
			case NT::START_FUNC:		WRITE( ASM_FUNC_START); break;
			case NT::RETURN:			WRITE( ASM_FUNC_RETURN, nt.p2); break;
			case NT::END_FUNC:			WRITE( ASM_FUNC_END, nt.p2); break;
			case NT::END_MAIN_FUNC:		WRITE(ASM_MAIN_FUNC_END); break;
			case NT::FUNC_INVOKE:		WRITE( ASM_INVOKE_FUNC, nt.p2); break;
			case NT::FANC_PARAM:		WRITE(ASM_INVOKE_PARAM, nt.p2); break;
			case NT::PUSH_INVOKE:		WRITE(ASM_PUSH_INVOKE); break;
			case NT::STR_PUSH:			WRITE( ASM_STR_INIT, nt.p2, nt.p3); break;
			case NT::PRINT:
				if (nt.TD == IT::DT_STR) GEN(main, ASM_SPRINT, nt.p2);	else if (nt.TD == IT::DT_INT)	GEN(main, ASM_IPRINT, nt.p2);
				if (strcmp(nt.p3, "endl") == 0) { GEN(buf, ASM_ENDL); strcat_s(main, 1024, buf); }	Log::WriteLine(out, main, "");	break;
			}
		}
		Log::Close(out);
	}

	void StartAssemblerCompil(Parm::PARM parm)
	{
		char *param = new char[255];
		char *buf = new char[50];
		size_t i;
		strcpy_s(param, 255, "..\\KPI-2016\\make.bat ");
		wcstombs_s(&i, buf, 50, parm.out, sizeof(parm.out));
		strcat_s(param, 255, buf);
		WinExec(param, 1);
	}
}
