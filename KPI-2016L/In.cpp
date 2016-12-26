#include "stdafx.h"
#undef IN

using namespace std;
namespace In
{
	IN getin(wchar_t infile[], Log::LOG log)
	{
		IN in;
		Error::ErrorTable eT(ERROR_MAX_ENTRY);
		int position = 1, count_error = 0;

		in.size = 0;	in.lines = 1;	in.ignor = 0;
		in.text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream inFile;
		inFile.open(infile);


		if (!inFile)	throw GET_ERROR(110)
		else
		{
			unsigned char tempChar;
			while ((tempChar = inFile.get()) && !inFile.eof())
			{
				switch (in.code[tempChar])
				{
					case in.N:	in.text[in.size] = IN_CODE_ENDL; in.lines++;	position = 1; break;
					case in.F:	GET_ERROR(111, in.lines, position);	break;
					case in.T: case in.P: case in.Q: case in.S: case in.K:	in.text[in.size] = tempChar; break;
					case in.I: in.ignor++;	break;
					default: in.text[in.size] = '!'; break;
				}
				position++;
				in.size++;
			}

			in.text[in.size] = '\0';
			in.size--;
			if (eT.errors.size() > 0)	throw GET_ERROR(111)
			inFile.close();
		}
		in = DeleteExtraSpace(in);
		WriteIn(log, in);
		return in;
	}
	void DeleteSymbol(IN & in, int position_del)
	{
		for (int i = position_del; i < in.size; i++) in.text[i] = in.text[i + 1];
		in.size--;
	}
	IN DeleteExtraSpace(IN in)
	{
		Error::ErrorTable eT(ERROR_MAX_ENTRY);
		int ql_space = 0;
		for (int i = 0; i < in.size; i++)
		{
			switch (in.code[in.text[i]])
			{		// если кол-во пробелов > 1 
				case in.P:	if (++ql_space > 1)	{ DeleteSymbol(in, i--); }	break;
				case in.S:	// если у нас сепоратор проверяем, есть ли пробел до него и после, если есть, удаляем
					if (in.code[in.text[i - 1]] == in.P) DeleteSymbol(in, i-- - 1);
					if (in.code[in.text[i + 1]] == in.P) DeleteSymbol(in, i-- + 1);
					break;
				case in.N: // если новая строка начинается с пробела, удаляем его
					if (in.code[in.text[i + 1]] == in.P) DeleteSymbol(in, i + 1); break;
				case in.T:	ql_space = 0;	break;
				case in.Q:
					while (in.code[in.text[++i]] != in.Q)	// пропускаем все пробелы в "...."
						if (in.code[in.text[i]] == in.N) throw GET_ERROR(115);
					break;
			}
		}
		return in;
	}
	void WriteIn(Log::LOG log, In::IN in)
	{
		char *lines = new char[255]; sprintf_s(lines, 255, "%d", in.lines);
		char *size = new char[255]; sprintf_s(size, 255, "%d", in.size);
		char *ignor = new char[255]; sprintf_s(ignor, 255, "%d", in.ignor);
		DW(false, "---- Исходные данные ----",
			"\nКолличество символов:", size,
			"\nПроигнорировано: ", ignor,
			"\nКолличество строк: ", lines, "\n");
		delete[] lines, size, ignor;
	}
};