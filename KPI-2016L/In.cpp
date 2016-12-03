#include "stdafx.h"
#undef IN

using namespace std;
namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in;

		int position = 1,
			count_error = 0;

		in.size = 0;
		in.lines = 1;
		in.ignor = 0;
		in.text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream inFile;
		inFile.open(infile);
		bool inComment = 0;


		if (!inFile)
		{
			throw GET_ERROR(110);
		}
		else
		{
			unsigned char tempChar;
			while ((tempChar = inFile.get()) && !inFile.eof())
			{
				switch (in.code[tempChar])
				{
					case in.N: {
						in.text[in.size] = IN_CODE_ENDL;
						in.lines++;
						position = 1;
						break;
					}
					case in.F: {
						ADD_ERROR(111, in.lines, position, "", Error::INN);
						count_error++;
						break;
					}
					case in.T: case in.P: case in.Q: case in.S: case in.K: {
						
						in.text[in.size] = tempChar;
						break;
					}
					case in.I: {
						in.ignor++;
						break;
					}
					default: {
						in.text[in.size] = '!';
						break;
					}
				}
				position++;
				in.size++;
			}

			in.text[in.size] = '\0';
			in.size--;
			if (count_error > 0) {
				throw ERROR_THROW_IN
			}
			inFile.close();
		}
		in = DeleteExtraSpace(in);
		return in;
	}
	void DeleteSymbol(IN & in, int position_del)
	{
		for (int i = position_del; i < in.size; i++)
		{
			in.text[i] = in.text[i + 1];
		}
		in.size--;
	}
	IN DeleteExtraSpace(IN in)
	{
		int ql_space = 0;
		for (int i = 0; i < in.size; i++)
		{
			switch (in.code[in.text[i]])
			{
				case in.P:
				{
					if (++ql_space > 1)			// если кол-во пробелов > 1
					{
						DeleteSymbol(in, i);	// удаляем
						i--;
					}
					break;
				}
				case in.S:	// если у нас сепоратор
				{
					if (in.code[in.text[i - 1]] == in.P)	// проверяем, есть ли пробел до него и после
					{
						DeleteSymbol(in, i - 1);	// если есть, удаляем
						i--;
					}
					if (in.code[in.text[i + 1]] == in.P)
					{
						DeleteSymbol(in, i + 1);
						i--;
					}
					break;
				}
				case in.N:
				{
					if (in.code[in.text[i + 1]] == in.P)	// если новая строка начинается с пробела, удаляем его
					{
						DeleteSymbol(in, i + 1);
					}
					break;
				}
				case in.T:
				{
					ql_space = 0;	// зануляем колличство пробеллов
					break;
				}
				case in.Q:
				{
					while (in.code[in.text[++i]] != in.Q)	// пропускаем все пробелы в "...."
					{
						if (in.code[in.text[i]] == in.N) throw GET_ERROR(115, 1);
					}
					break;
				}
			}
		}
		return in;
	}
	void AddDevideWord(Devide & dev, int count, char symbol)
	{
		char buf[2];
		buf[0] = symbol;
		buf[1] = '\0';
		strcpy(&dev.word[dev.count_word][count], buf);
	}
	Devide DivideWord(IN in)
	{
		In::Devide dev;
		int Word_position = 0, position = 0;
		for (int i = 0; i <= in.size; i++)
		{
			switch (in.code[in.text[i]])
			{
				case in.T:	// если у нас разрешенная буква
				{
					AddDevideWord(dev, Word_position++, in.text[i]);	// добавляем ее в массив
					position++;	// что бы при ошибке выводило возицию
					break;
				}
				case in.S:	// если у нас сепоратор
				{
					dev.count_word++;	// переходим к след слову
					position++;
					AddDevideWord(dev, 0, in.text[i]);	// добавляем сепоратор 
					if (in.code[in.text[i + 1]] == in.T || in.code[in.text[i + 1]] == in.Q)
					{
						Word_position = 0;
						dev.count_word++;
					}					
					break;
				}
				case in.K:
				{
					if (in.code[in.text[i + 1]] == in.K)
					{
						while (in.code[in.text[++i]] != in.N) 
						{};
						i--;
					}
					else
					{
						while (in.code[in.text[++i]] != in.K)
						{
							if (in.code[in.text[i]] == in.N)
							{
								dev.lines++;
								dev.count_word++;
								AddDevideWord(dev, 0, DEVIDE_LINE);
							}
							if (in.lines < dev.lines) throw GET_ERROR(114, 1);
						};
					}
					break;
				}
				case in.Q:
				{
					AddDevideWord(dev, Word_position++, '\'');						// заменяются все ковычки на '...'
					while (in.code[in.text[++i]] != in.Q)
					{
						AddDevideWord(dev, Word_position++, in.text[i]);
					}
					AddDevideWord(dev, Word_position++, '\'');
					if (in.code[in.text[i + 1]] == in.T) { dev.count_word++; Word_position = 0; }
					break;
				}
				case in.P:
				{
					if (in.code[in.text[i + 1]] != in.P && in.code[in.text[i + 1]] != in.S)
					{
						dev.count_word++;
						Word_position = 0;
					}
					position++;
					break;
				}
				case in.N:
				{
					dev.count_word++;
					AddDevideWord(dev, 0, DEVIDE_LINE);		// добавляем сепоратор "|" в качестве разделителя слов
					if (in.code[in.text[i + 1]] == in.T)
					{
						Word_position = 0;
						dev.count_word++;
					}
					dev.lines++;
					position = 0;
					break;
				}
				default:
				{
					ADD_ERROR(113, dev.lines, position, "", Error::INN);
					dev.count_error++;
				}
			}
		}
		if (dev.count_error > 0)
		{
			throw ERROR_THROW_IN
		}
		/*cout << "Разделение слов" << endl;
		for (int i = 0; i <= dev.count_word; i++)
		{
			cout << dev.word[i] << endl;
		}*/
		return dev;
	}
};