#include "stdafx.h"
using namespace std;
Error::ErrorTable eT(ERROR_MAX_ENTRY);

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv, log);
		File::File file(parm.in, log);
		LA::LexAnaliz Lex = LA::LexicalAnaliz(file.dev, log, parm);
		if (SA::syntacticAnalyzer(Lex, log, parm))
		{
			NT::Nible nible = NT::genNible(Lex, log, parm);
			Gen::Generator(parm, nible);
			Gen::StartAssemblerCompil(parm);
		}
		Log::Close(log);
		return 0;
	}
	catch (Error::ErrorTable eT)
	{
		Error::PrintErrors(eT,log);
		system("pause");
	}
};