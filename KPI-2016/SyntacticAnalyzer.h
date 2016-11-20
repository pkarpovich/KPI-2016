#pragma once

namespace SA
{
	MFST::Mfst syntacticAnalyzer(LA::LexAnaliz &Lex, std::stack<MFST::MfstState>& state, Log::LOG log, Parm::PARM param);
}