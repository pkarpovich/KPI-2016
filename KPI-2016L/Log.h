#pragma once
using namespace std;

#define DW(param, ...) Log::DoubleWrite(log, param, __VA_ARGS__, "");
#define BUFFER_SIZE 100

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
	void WriteLog(LOG log);
	void DoubleWrite(LOG log, bool rc, char* c, ...);
	void Close(LOG log);
};