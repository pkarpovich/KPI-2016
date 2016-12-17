#include "stdafx.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE)
		{
			throw GET_ERROR(200, 4);
		}
		else
		{
			LexTable *New = new LexTable;
			New->maxsize = size;
			New->size = 0;
			New->table = new Entry[size];
			memset(New->table, 0xff, sizeof(Entry)*size);
			return *New;
		}
	}
	void Add(LexTable & lextable, Entry entry)
	{
		if (lextable.size > lextable.maxsize)
		{
			throw GET_ERROR(201,4)
		}
		else
		{
			lextable.table[lextable.size++] = entry;
		}
	}

	void AddTo(LexTable& lextable, Entry entry, int pos)
	{
		for (int i = lextable.size; i > pos; i--)
		{
			lextable.table[i] = lextable.table[i - 1];
		}
		lextable.table[pos+1] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable & lextable, int n)
	{
		return lextable.table[n];
	}
	void Delete(LexTable & lextable)
	{
		delete lextable.table;
	}
	void Swap(LexTable &oldLexTable, int number, Entry newTable)
	{
		oldLexTable.table[number] = newTable;
	}
	void ShowLT(LexTable & l, Parm::PARM param, Log::LOG log)
	{
		char *buf = new char[255];
		DW(param.LT, "\nТаблица лексем: \n")
		for (int i = 0; i < l.size; i++)	//вывод таблицы лексем
		{
			if (l.table[i].lexema != LEX_FORBIDDEN)
			{
				if (l.table[i].sn != l.table[i - 1].sn) // Чтобы при выводе выводило на новых строках
				{
					sprintf_s(buf, 255, "\n%02d ", l.table[i].sn); DW(param.LT, buf);
				}
				sprintf_s(buf, 255, "%c", l.table[i].lexema); DW(param.LT, buf);
				if (l.table[i].idxTI != TI_NULLIDX)
				{
					sprintf_s(buf, 255, "{%d}", l.table[i].idxTI); DW(param.LT, buf);
				}
			}
		}
		DW(param.LT, "\n\n");
		delete[] buf;
	}
}