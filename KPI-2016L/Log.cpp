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
			throw GET_ERROR(112,3);
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

	void WriteError(LOG log, Error::ERRORS error)
	{
		switch (error.type)
		{
		case	Error::PARAM: {
			cout << "---- Ошибка в параметрах ----" << endl;
			break;
		}
		case Error::INN: {
			cout << "---- Ошибка при проверке входного файла  ----" << endl;
			break;
		}
		case Error::LOG: {
			cout << "---- Ошибка в log файле ----" << endl;
			break;
		}
		case Error::LT: {
			cout << "---- Ошибка в таблице лексем ----" << endl;
			break;
		}
		case Error::IT: {
			cout << "---- Ошибка в таблице индентификаторов ----" << endl;
			break;
		}
		case Error::LA: {
			cout << "---- Ошибка при лексическом анализе ----" << endl;
			break;
		}
		}
		if (error.type == Error::INN)
		{
			cout << "Ошибка № " << error.id << ": " << error.message << endl;
			for (int i = 0; i < error.count; i++)
				cout << "Строка " << error.errors_in[i].line << ", позиция " << error.errors_in[i].pos << endl;
		}
		else
		{
			cout << "Ошибка № " << error.id << ": " << error.message << endl;
		}
/*
		switch (error.type)
		{
		case	Error::PARAM: {
			(*log.stream) << "---- Ошибка в параметрах ----" << endl;
			break;
		}
		case Error::INN: {
			(*log.stream) << "---- Ошибка при проверке входного файла  ----" << endl;
			break;
		}
		case Error::LOG: {
			(*log.stream) << "---- Ошибка в log файле ----" << endl;
			break;
		}
		case Error::LT: {
			(*log.stream) << "---- Ошибка в таблице лексем ----" << endl;
			break;
		}
		case Error::IT: {
			(*log.stream) << "---- Ошибка в таблице индентификаторов ----" << endl;
			break;
		}
		case Error::LA: {
			(*log.stream) << "---- Ошибка при лексическом анализе ----" << endl;
			break;
		}
		}
		if (error.type == Error::INN)
		{
			(*log.stream) << "Ошибка № " << error.id << ": " << error.message << endl;
			for (int i = 0; i < error.count; i++)
				(*log.stream) << "Строка " << error.errors_in[i].line << ", позиция " << error.errors_in[i].pos << endl;
		}
		else
		{
			(*log.stream) << "Ошибка № " << error.id << ": " << error.message << endl;
		}*/
	}

	void WriteWarning(LOG log, Error::ERRORS error)
	{
		switch (error.type)
		{
		case	Error::PARAM: {
			cout << "---- Предупреждение в параметрах ----" << endl;
			break;
		}
		case Error::INN: {
			cout << "---- Предупреждение при проверке входного файла  ----" << endl;
			break;
		}
		case Error::LOG: {
			cout << "---- Предупреждение в log файле ----" << endl;
			break;
		}
		case Error::LT: {
			cout << "---- Предупреждение в таблице лексем ----" << endl;
			break;
		}
		case Error::IT: {
			cout << "---- Предупреждение в таблице индентификаторов ----" << endl;
			break;
		}
		case Error::LA: {
			cout << "---- Предупреждение в лексическом анализе ----" << endl << endl;;
			break;
		}
		}
		if (error.type = Error::INN)
		{
			for (int i = 0; i < error.warning; i++)
			{
				cout << "Предупреждение № " << error.errors_la[i].id << ": " << error.errors_la[i].message << endl;
				cout << "Строка " << error.errors_la[i].line << ", идентификатор: " << error.errors_la[i].word << endl << endl;
			}
		}
		cout << endl;

		switch (error.type)
		{
		case	Error::PARAM: {
			(*log.stream) << "---- Предупреждение в параметрах ----" << endl;
			break;
		}
		case Error::INN: {
			(*log.stream) << "---- Предупреждение при проверке входного файла  ----" << endl;
			break;
		}
		case Error::LOG: {
			(*log.stream) << "---- Предупреждение в log файле ----" << endl;
			break;
		}
		case Error::LT: {
			(*log.stream) << "---- Предупреждение в таблице лексем ----" << endl;
			break;
		}
		case Error::IT: {
			(*log.stream) << "---- Предупреждение в таблице индентификаторов ----" << endl;
			break;
		}
		case Error::LA: {
			(*log.stream) << "---- Предупреждение в лексическом анализе ----" << endl << endl;;
			break;
		}
		}
		if (error.type = Error::INN)
		{
			for (int i = 0; i < error.warning; i++)
			{
				(*log.stream) << "Предупреждение № " << error.errors_la[i].id << ": " << error.errors_la[i].message << endl;
				(*log.stream) << "Строка " << error.errors_la[i].line << ", идентификатор: " << error.errors_la[i].word << endl << endl;
			}
		}
		(*log.stream) << endl;
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}
}