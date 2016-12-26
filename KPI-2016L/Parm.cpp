#include "stdafx.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR *argv[], Log::LOG &log)
	{
		PARM param;
		Error::ErrorTable eT(ERROR_MAX_ENTRY);
		wchar_t buf[300];								// временная переменнная
		int param_size_in = wcslen(PARM_IN),			// размер зарезервированного параметра in
			param_size_out = wcslen(PARM_OUT),			// размер зарезервированного параметра out
			param_size_log = wcslen(PARM_LOG);			// размер зарезервированного параметра log

		if (argc == 1)	throw GET_ERROR(100)
		else			// если есть параметры
		{
			for (int i = 0; i < argc; i++)
			{
				wcscpy_s(buf, argv[i]);
				if (wcslen(buf) > PARM_MAX_SIZE)	throw GET_ERROR(104)
				else
				{
					if (wcsstr(buf, PARM_IN) != NULL)
					{
						wcscpy_s(param.in, argv[i] + param_size_in);					// добавляем параметр in
						wcscpy_s(param.out, argv[i] + param_size_in);					// добавляем параметр out (равный in)
						wcsncat_s(param.out, PARM_OUT_DEFAULT_EXT, wcslen(argv[i]));	// добавляем расширение .out
						wcscpy_s(param.log, argv[i] + param_size_in);					// добавляем параметр log  (равный in)
						wcsncat_s(param.log, PARM_LOG_DEFAULT_EXT, wcslen(argv[i]));	// добавляем расширение .log
					}
					else if (wcsstr(buf, PARM_OUT) != NULL)		wcscpy_s(param.out, argv[i] + param_size_out);
					else if (wcsstr(buf, PARM_LOG) != NULL)		wcscpy_s(param.log, argv[i] + param_size_out);
					else if (wcsstr(buf, PARM_LT) != NULL)		param.LT = true;
					else if (wcsstr(buf, PARM_IT) != NULL)		param.IT = true;
					else if (wcsstr(buf, PARM_SA) != NULL)		param.SA = true;
					else if (wcsstr(buf, PARM_NT) != NULL)		param.NT = true;
					else if (wcsstr(buf, PARM_RULE) != NULL)	param.R = true;
				}
			}
			log = Log::getlog(param.log);
			Log::WriteLog(log);
			WriteParm(log, param);
			return param;
		}
	}

	void WriteParm(Log::LOG log, PARM parm)
	{
		char *parmIN = (char *)malloc(BUFFER_SIZE);
		char *parmOUT = (char *)malloc(BUFFER_SIZE);
		char *parmLOG = (char *)malloc(BUFFER_SIZE);
		size_t   i;
		wcstombs_s(&i, parmIN, (size_t)BUFFER_SIZE, parm.in, (size_t)BUFFER_SIZE);
		wcstombs_s(&i, parmOUT, (size_t)BUFFER_SIZE, parm.out, (size_t)BUFFER_SIZE);
		wcstombs_s(&i, parmLOG, (size_t)BUFFER_SIZE, parm.log, (size_t)BUFFER_SIZE);
		DW(false, "---- Параметры ----\n", "\n-in: ", parmIN, "\n-out: ", parmOUT, "\n-log: ", parmLOG, "\n",
			"-LT: ", parm.LT ? "true" : "false", "\n",
			"-IT: ", parm.IT ? "true" : "false", "\n",
			"-SA: ", parm.SA ? "true" : "false", "\n",
			"-NT: ", parm.NT ? "true" : "false", "\n",
			"-DT: ", parm.LT ? "true" : "false", "\n");
	}
}
