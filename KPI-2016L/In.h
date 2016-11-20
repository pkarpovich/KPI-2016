#pragma once
#undef IN
#define IN_MAX_LEN_TEXT		1024*1024
#define DEV_MAX_WORD		1000		// кол-во слов, в ммассиве слов
#define DEV_WORD_SIZE		255			// длина слова в массиве
#define DEVIDE_LINE			'|'			// разделитель строк
#define IN_CODE_ENDL '\n'
#define IN_CODE_TABLE {\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::P, IN::N, IN::T, IN::T, IN::I, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::P, IN::T, IN::Q, IN::T, IN::T, IN::T, IN::T, IN::Q, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::T, IN::S,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::S, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::K, IN::S, IN::T, IN::T,\
	IN::Q, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::T, IN::S, IN::T, IN::T,\
																													\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T\
}
namespace In
{
	struct IN
	{
		enum {T = 1, F = 2, I = 3, N = 4, P = 5, Q = 6, S = 7, K = 8};	// T - разрешенный, F - запрещенный, I -игнорируемый, N - конец строки
																// P - пробел, Q - ковычки, S - сепаратор, K - комментарий
		int size,
			lines,
			ignor;
		unsigned char* text;
		int code[256] = IN_CODE_TABLE;
	};
	struct Devide
	{
		char word[DEV_MAX_WORD][DEV_WORD_SIZE];			// массив слов
		int count_word = 0,				// колличество слов
			count_error = 0,			// колличество ошибок (нераспознанное слово)
			lines = 1;					// строка
	};
	struct IN_FILE
	{
		IN in;
		Devide dev;
	};
	IN getin(wchar_t infile[]);
	void DeleteSymbol(IN &in, int position_del);				// удаление буквы в строке
	IN DeleteExtraSpace(IN in);									// удаление лишних пробелов
	void AddDevideWord(Devide &dev, int count, char symbol);	// добавление буквы в массив
	Devide DivideWord(IN in);									// разделение in.txt на слова
}