#include "stdafx.h"

namespace File
{
	File::File(wchar_t infile[], Log::LOG log)
	{
		this->in = In::getin(infile, log);
		this->dev = Div::DivideWord(this->in, log);
	}
}