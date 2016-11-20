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
		if (!log.stream->is_open())
			throw GET_ERROR(112);
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

	void WriteLine(LOG log, wchar_t * c, ...)
	{
		char buf[50];
		wchar_t **p = &c;
		while (*p != L"")
		{
			wcstombs(buf, *p, sizeof(buf));
			(*log.stream) << buf;
			p += sizeof(**p) / 2;
		}
	}

	void WriteTimplates(LOG log, char * c)
	{
		(*log.stream) << c;
	}

	void WriteLog(LOG log)
	{
		char buf[255];

		time_t ravtime;
		struct tm* timeinfo;

		time(&ravtime);
		timeinfo = localtime(&ravtime); 

		strftime(buf, PARM_MAX_SIZE, "Дата: %d.%m.%y %H:%M:%S", timeinfo);
		(*log.stream) << "\n---- Протокол ---- \n" << buf << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char parmIN[PARM_MAX_SIZE], parmOUT[PARM_MAX_SIZE], parmLOG[PARM_MAX_SIZE];

		wcstombs(parmIN, parm.in, sizeof(parmIN));
		wcstombs(parmOUT, parm.out, sizeof(parmOUT));
		wcstombs(parmLOG, parm.log, sizeof(parmLOG));

		(*log.stream) << "---- Параметры ----"
			<< "\n-in: " << parmIN
			<< "\n-out: " << parmOUT
			<< "\n-log: " << parmLOG << endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		(*log.stream) << "---- Исходные данные ----"
			<< "\nКолличество символов:" << in.size
			<< "\nПроигнорировано: " << in.ignor
			<< "\nКолличество строк: " << in.lines << endl;
	}

	void WriteErrors(LOG log, Error::ERRORS error)
	{
		switch (error.type)
		{
			case Error::LA:
				{
					cout << "Ошибка " << error.id << ": " << error.message << endl;
					(*log.stream) << "Ошибка " << error.id << ": " << error.message << endl;
					for (int i = 0; i < error.count; i++)
					{
						(*log.stream) << "Строка: " << error.errors[i].line << " идентификатор: " << error.errors[i].word << endl;
						cout << "Строка: " << error.errors[i].line << " идентификатор: " << error.errors[i].word << endl;
					}
					break;
				}
			case Error::INN:
				{
					cout << "Ошибка " << error.id << ": " << error.message << endl;
					(*log.stream) << "Ошибка " << error.id << ": " << error.message << endl;
					for (int i = 0; i < error.count; i++)
					{
						(*log.stream) << "Строка: " << error.errors[i].line << " позиция: " << error.errors[i].pos << endl;
						cout << "Строка: " << error.errors[i].line << " позиция: " << error.errors[i].pos << endl;
					}
					break;
				}
		}
	}

	void WriteError(LOG log, Error::ERROR_MESSAGE error)
	{
		cout << "Ошибка " << error.id << ": " << error.message << endl;
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}
}