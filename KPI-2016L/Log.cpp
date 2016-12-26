#include "stdafx.h"

using namespace std;

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		wcscpy_s(log.logfile, logfile);
		log.stream->open(logfile, ios::out);
		return log;
	}

	void WriteLine(LOG log, char * c, ...)
	{
		char **p = &c;
		while (*p != "")
		{
			(*log.stream) << *p;
			p += sizeof(**p);
		}
	}

	void DoubleWrite(LOG log, bool rc, char * c, ...)
	{
		char **p = &c;
		while (*p != "")
		{
			(*log.stream) << *p;
			if(rc)	std::cout << *p;
			p += sizeof(**p);
		}
	}

	void WriteLog(LOG log)
	{
		char buf[255];
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		strftime(buf, PARM_MAX_SIZE, "Дата: %d.%m.%y %H:%M:%S", &newtime);
		DW(false, "---- Протокол ---- \n", buf, "\n");
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}
}