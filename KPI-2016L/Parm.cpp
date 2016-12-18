#include "stdafx.h"
extern Error::ErrorTable eT;
Parm::PARM Parm::getparm( int argc, _TCHAR *argv[])
{
	Parm::PARM param;
	wchar_t buf[300];								// временная переменнная
	int param_size_in  = wcslen(PARM_IN),			// размер зарезервированного параметра in
		param_size_out = wcslen(PARM_OUT),			// размер зарезервированного параметра out
		param_size_log = wcslen(PARM_LOG);			// размер зарезервированного параметра log

	if (argc == 1)	// если нет параметров
	{
		throw GET_ERROR(100);
	}
	else			// если есть параметры
	{
		for (int i = 0; i < argc; i++)
		{
			wcscpy(buf, argv[i]);
			if (wcslen(buf) > PARM_MAX_SIZE)
			{
				throw GET_ERROR(104);									// если превышен размер входного параметра
			}
			else
			{
				if (wcsstr(buf, PARM_IN) != NULL)
				{
					wcscpy(param.in, argv[i] + param_size_in);					// добавляем параметр in
					wcscpy(param.out, argv[i] + param_size_in);					// добавляем параметр out (равный in)
					wcsncat(param.out, PARM_OUT_DEFAULT_EXT, wcslen(argv[i]));	// добавляем расширение .out
					wcscpy(param.log, argv[i] + param_size_in);					// добавляем параметр log  (равный in)
					wcsncat(param.log, PARM_LOG_DEFAULT_EXT, wcslen(argv[i]));	// добавляем расширение .log
				}
				else if (wcsstr(buf, PARM_OUT) != NULL)
				{
					wcscpy(param.out, argv[i] + param_size_out);				// добавляем параметр out
				}
				else if (wcsstr(buf, PARM_LOG) != NULL)
				{
					wcscpy(param.log, argv[i] + param_size_out);				// добавляем параметр log
				}
				else if (wcsstr(buf, PARM_LT) != NULL)
				{
					param.LT = true;											// ключ для таблицы лексем
				}
				else if (wcsstr(buf, PARM_IT) != NULL)
				{
					param.IT = true;											// ключ для таблицы индентификаторов
				}
				else if (wcsstr(buf, PARM_SA) != NULL)
				{
					param.SA = true;
				}
				else if (wcsstr(buf, PARM_DT) != NULL)
				{
					param.DT = true;
				}
				else if (wcsstr(buf, PARM_NT) != NULL)
				{
					param.NT = true;
				}
				else if (wcsstr(buf, PARM_RULE) != NULL)
				{
					param.R = true;
				}
			}
		}
		return param;
	}
}