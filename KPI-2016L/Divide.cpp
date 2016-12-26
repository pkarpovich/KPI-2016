#include "stdafx.h"

namespace Div
{
	Divide::Divide()
	{
		this->count_word = 0;
		this->lines = 1;
	}

	void AddDivideWord(Divide &div, int count, char symbol)
	{
		char buf[2];
		buf[0] = symbol;
		buf[1] = '\0';
		strcpy_s(&div.word[div.count_word][count], 255, buf);
	}

	Divide DivideWord(In::IN in, Log::LOG log)
	{
		Divide div;
		Error::ErrorTable eT(ERROR_MAX_ENTRY);
		int Word_position = 0, position = 0;
		bool isNeg = 0;
		for (int i = 0; i <= in.size; i++)
		{
			switch (in.code[in.text[i]])
			{
			case in.T:	// если у нас разрешенная буква
			{
				if (isNeg&&in.text[i - 1] == '-')
				{
					AddDivideWord(div, Word_position++, in.text[i - 1]);	isNeg = 0;
				}
				AddDivideWord(div, Word_position++, in.text[i]);	// добавляем ее в массив
				position++;	// что бы при ошибке выводило возицию
				break;
			}
			case in.S:	// если у нас сепоратор
			{
				if (in.text[i] == '-' && (in.text[i - 1] == '(' || in.text[i - 1] == ':' || in.text[i - 1] == '='))
				{	// проверка на отрицательное число
					if (in.text[i - 1] != '=') div.count_word++;
					Word_position = 0; isNeg = true;	break;
				}
				if ((in.text[i] == '=' && in.text[i - 1] == '=') || (in.text[i] == '=' && in.text[i - 1] == '!') ||
					(in.text[i] == '=' && in.text[i - 1] == '<') || (in.text[i] == '=' && in.text[i - 1] == '>'))
				{
					AddDivideWord(div, 1, in.text[i]); div.count_word++; Word_position = 0;	break;
				}
				if ((in.text[i] == '+' && in.text[i - 1] == '+') ||
					(in.text[i] == '-' && in.text[i - 1] == '-'))
				{
					AddDivideWord(div, 1, in.text[i]); Word_position = 0;	break;
				}
				div.count_word++;	// переходим к след слову
				position++;
				AddDivideWord(div, 0, in.text[i]);	// добавляем сепоратор 
				if (in.code[in.text[i + 1]] == in.T || in.code[in.text[i + 1]] == in.Q)
				{
					Word_position = 0;
					div.count_word++;
				}
				break;
			}
			case in.K:
			{
				if (in.code[in.text[i + 1]] == in.K)
				{
					while (in.code[in.text[++i]] != in.N)
					{
					};
					i--;
				}
				else
				{
					while (in.code[in.text[++i]] != in.K)
					{

						if (in.code[in.text[i]] == in.N)
						{
							if (in.lines - 1 < ++div.lines) throw GET_ERROR(114);
							div.count_word++;
							AddDivideWord(div, 0, DEVIDE_LINE);
						}
					};
				}
				break;
			}
			case in.Q:
			{
				AddDivideWord(div, Word_position++, '\'');						// заменяются все ковычки на '...'
				while (in.code[in.text[++i]] != in.Q)
				{
					AddDivideWord(div, Word_position++, in.text[i]);
				}
				AddDivideWord(div, Word_position++, '\'');
				if (in.code[in.text[i + 1]] == in.T) { div.count_word++; Word_position = 0; }
				break;
			}
			case in.P:
			{
				if (in.code[in.text[i + 1]] != in.P && in.code[in.text[i + 1]] != in.S && in.text[i + 1] != IN_CODE_ENDL)
				{
					div.count_word++;
					Word_position = 0;
				}
				position++;
				break;
			}
			case in.N:
			{
				div.count_word++;
				AddDivideWord(div, 0, DEVIDE_LINE);		// добавляем сепоратор "|" в качестве разделителя слов
				if (in.code[in.text[i + 1]] == in.T)
				{
					Word_position = 0;
					div.count_word++;
				}
				div.lines++;
				position = 0;
				isNeg = 0;
				break;
			}
			default: GET_ERROR(113, div.lines, position);
			}
		}
		if (eT.errors.size() > 0)	throw GET_ERROR(113);
		//for (int i = 0; i <= dev.count_word; i++)	cout << dev.word[i] << endl;

		return div;
	}
}