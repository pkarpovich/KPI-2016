#pragma once
#include <tchar.h>

#define PARM_IN					L"-in:"				// ключ для файла исходного кода
#define PARM_OUT				L"-out:"			// ключ для выходного файла
#define PARM_LOG				L"-log:"			// ключ для лог файла
#define PARM_MAX_SIZE			300					// максимальный размер параметра
#define PARM_OUT_DEFAULT_EXT	L".out"				// расширение файла объектного кода
#define PARM_LOG_DEFAULT_EXT	L".log"				// расширение лог файла
#define PARM_LT					L"-LT"				// ключ для вывода таблицы лексем 
#define PARM_IT					L"-IT"				// ключ для вывода таблицы индентификаторов
#define PARM_SA					L"-SA"
#define PARM_NT					L"-NT"
#define PARM_DT					L"-DT"
#define PARM_RULE				L"-R"

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];					// имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];					// имя файла объектного файла
		wchar_t log[PARM_MAX_SIZE];					// имя лог файла
		bool IT = false;							// нужнен ли вывод таблицы индентификаторов
		bool LT = false;							// нужен ли вывод таблицы лексем
		bool SA = false;
		bool DT = false;
		bool NT = false;
		bool R = false;
	};

	PARM getparm(int argc, _TCHAR* argv[]);
}