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
		Log::WriteLine(log, "Тест:", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN_FILE in_file;
		in_file.in = In::getin(parm.in);
		in_file.dev = In::DivideWord(in_file.in);
		Log::WriteIn(log, in_file.in);
		LA::LexAnaliz Lex = LA::LexicalAnaliz(in_file.dev, log, parm);
		std::stack<MFST::MfstState> storestate;
		if (SA::syntacticAnalyzer(Lex, storestate, log, parm))
		{
			//LT::ShowLT(Lex.l, parm, log);
			NT::Nible nible = NT::genNible(Lex, log);
			Gen::Generator(parm, nible);
			WinExec("C:\\Users\\taller\\OneDrive\\Документы\\Visual Studio 2015\\Projects\\KPI-2016\\KPI-2016\\make.bat", 1);
		}
		Log::Close(log);
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