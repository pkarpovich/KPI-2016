#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::DoubleWrite(log,false, "Тест:", "без ошибок \n", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN_FILE in_file;
		in_file.in = In::getin(parm.in);
		in_file.dev = In::DivideWord(in_file.in, parm, log);
		//Log::WriteIn(log, in_file.in);
		LA::LexAnaliz Lex = LA::LexicalAnaliz(in_file.dev, log, parm);
		std::stack<MFST::MfstState> storestate;
		if (SA::syntacticAnalyzer(Lex, storestate, log, parm))
		{
			NT::Nible nible = NT::genNible(Lex, log, parm);
			Gen::Generator(parm, nible);
			char *param = new char[255];
			char *buf = new char[50];
			strcpy(param, "C:\\Users\\taller\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\KPI-2016\\KPI-2016\\make.bat ");
			wcstombs(buf, parm.out, sizeof(parm.out));
			strcat(param, buf);
			WinExec(param, 1);
		}
		Log::Close(log);
		system("pause");
		return 0;
	}
	catch (Error::ERROR_MESSAGE em)
	{
		Log::WriteError(log, em);
		system("pause");
	}
	catch (Error::ERRORS e)
	{
		Log::WriteErrors(log, e);
		system("pause");
	}
};