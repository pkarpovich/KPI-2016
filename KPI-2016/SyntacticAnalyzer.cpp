#include "stdafx.h"

bool SA::syntacticAnalyzer(LA::LexAnaliz Lex, Log::LOG log, Parm::PARM param)
{
	char buf[255];
	TRACE_START; DW(param.SA, buf);
	MFST::Mfst mfst(Lex.l, GRB::getGreibach());
	if (mfst.start(log, param))
	{
		mfst.printrules(log, param);
		return true;
	}
	return false;
}
