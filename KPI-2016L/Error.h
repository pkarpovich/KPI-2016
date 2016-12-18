#pragma once

#define ET(id,message) Add(temp, id, message);
#define GET_ERROR(id, ...) Error::CompleteError(eT, id, __VA_ARGS__);
#define ERROR_MAXSIZE_MESSAGE 200
#define ERROR_MAX_ENTRY 1000

namespace Error
{
	
	struct Entry
	{
		int id;
		char *message = new char[ERROR_MAXSIZE_MESSAGE];
		int line;
		int pos;
		char *word = new char[255];
	};

	struct ErrorTable
	{
		int maxSize;
		int size;
		std::vector<Entry> errors;
		Entry *table;
		ErrorTable(int);
		ErrorTable() = default;
	};

	void Add(ErrorTable&, int, char*);
	Entry GetError(ErrorTable, int id);
	ErrorTable CompleteError(ErrorTable&, int, const int line = -1, const int pos = -1, const char* word = "");
	void PrintErrors(ErrorTable, Log::LOG log);
}

