#include "stdafx.h"

namespace Gen
{
	void Generator(Parm::PARM param, LA::LexAnaliz lex, std::stack<MFST::MfstState> storestate)
	{
		Log::LOG out = Log::INITLOG;
		GRB::Greibach grb;
		out = Log::getlog(param.out);
		(*out.stream) << ASM_LIB;
		for (int i = 0; i < lex.iT.size; i++)
		{
			if (lex.iT.table[i].idtype == IT::L && lex.iT.table[i].iddatatype == IT::STR)
			{
				(*out.stream) << ASM_STR(lex.iT.table[i].id, lex.iT.table[i].value.vstr.str) << endl;
			}
		}
		char* buf = new char;
		grb = GRB::getGreibach();
		MFST::MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			if (lex.l.table[state.lenta_position].lexema == LEX_BEGIN_FUNCTION)
			{
				(*out.stream) << ASM_BEGIN;
			}
			if (lex.l.table[state.lenta_position].lexema == LEX_LITERAL && lex.iT.table[lex.l.table[state.lenta_position].idxTI].iddatatype == IT::STR)
			{
				(*out.stream) << ASM_SOUT(lex.iT.table[lex.l.table[state.lenta_position].idxTI].id);
			}
			if (lex.l.table[state.lenta_position].lexema == LEX_RETURN)
			{
				(*out.stream) << ASM_RETURN;
			}
		}
		(*out.stream) << ASM_END;
		//cout << state.nrule << endl;
		//GRB::Rule rule;
		//char* buf = new char;
		//rule = grb.getRule(state.nrule);
		//cout << rule.getCRule(buf, state.nrulechain) << endl;
		//cout << rule.chains << endl;
		//for (int i = 0; i < state.lenta_position; i++)
		//{
		//	
		//	
		//}
		
		/*for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			cout << "Номер правила: " << state.lenta_position << endl;
			rule = grebach.getRule(state.nrule);
			if (param.R) CON_MFST_TRACE7
				MFST_TRACE7
		}*/

	}
}
