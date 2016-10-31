#pragma once

namespace SA
{
	void syntacticAnalyzer(LA::LexAnaliz &Lex, std::stack<MFST::MfstState>& state, Log::LOG log, Parm::PARM param);
}