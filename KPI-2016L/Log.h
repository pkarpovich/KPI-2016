#pragma once
using namespace std;
#define DW(param, ...) Log::DoubleWrite(log, param, __VA_ARGS__, "");

namespace Log
{
	struct LOG
	{
		wchar_t logfile[50];
		ofstream * stream;
	};

	static const LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, wchar_t* c, ...);
	//void WriteTimplates(LOG log, char* c);
	void WriteLog(LOG log);
	//void WriteParm(LOG log, Parm::PARM parm);
	//void WriteIn(LOG log, In::IN in);
	//void WriteErrors(LOG log, Error::ERRORS error);
	//void WriteError(LOG log, Error::ERROR_MESSAGE error);
	void DoubleWrite(LOG log, bool rc, char* c, ...);
	void Close(LOG log);
};