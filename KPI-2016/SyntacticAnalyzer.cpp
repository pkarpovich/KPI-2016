#include "stdafx.h"

bool SA::syntacticAnalyzer(LA::LexAnaliz &Lex, std::stack<MFST::MfstState>& state, Log::LOG log, Parm::PARM param)
{
	MFST_TRACE_START;
	if(param.SA)	CON_MFST_TRACE_START
	MFST::Mfst mfst(Lex.l, GRB::getGreibach());
	if (mfst.start(log, param))
	{
		mfst.printrules(log, param, state);
		return true;
	}
	return false;
}
