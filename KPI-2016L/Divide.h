#pragma once

namespace Div
{
	struct Divide
	{
		char word[DEV_MAX_WORD][DEV_WORD_SIZE];			// массив слов
		int count_word;				// колличество слов
		int	lines;					// строка
		Divide();
	};

	Divide DivideWord(In::IN, Log::LOG);		// разделение in.txt на слова
	void AddDivideWord(Divide &, int, char);	// добавление буквы в массив
}