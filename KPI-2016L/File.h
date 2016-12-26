#pragma once
namespace File
{
	struct File
	{
		In::IN in;
		Div::Divide dev;
		File(wchar_t infile[], Log::LOG log);
	};
}
