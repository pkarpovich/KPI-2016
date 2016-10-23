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
		/*MFST_TRACE_START;
		MFST::Mfst mfst(Lex.l, GRB::getGreibach());
		mfst.start();
		mfst.printrules();
		PN::PolishNotation(Lex, log);
		LT::ShowLT(Lex.l, parm, log);*/
		Log::Close(log);
		return 0;
	}
	catch (Error::ERRORS e)
	{
		Log::WriteError(log, e);
	}
};