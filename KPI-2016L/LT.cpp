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
		if (param.LT == true)
		{
			cout << "Таблица лексем: " << endl;
			for (int i = 0; i < l.size; i++)	//вывод таблицы лексем
			{
				if (l.table[i].lexema != LEX_FORBIDDEN)
				{
					if (l.table[i].sn != l.table[i - 1].sn) // Чтобы при выводе выводило на новых строках
					{
						cout << std::endl;
						cout << setfill('0') << setw(2) << l.table[i].sn << " "; //setfill('0') << setw(2) - добавить ноль
					}
					cout << l.table[i].lexema;
					/*if (l.table[i].idxTI != TI_NULLIDX)
					{
						if(l.table[i].lexema == LEX_AT)
							cout << "{" << l.table[i].idxTI << "}";
						else cout << "" << l.table[i].idxTI << "]";
					}*/
				}
			}
			cout << endl << endl;
		}
		(*log.stream) << "Таблица лексем: " << endl;
		for (int i = 0; i < l.size; i++)	//вывод таблицы лексем
		{
			if (l.table[i].lexema != LEX_FORBIDDEN)
			{
				if (l.table[i].sn != l.table[i - 1].sn) // Чтобы при выводе выводило на новых строках
				{
					(*log.stream) << std::endl;
					(*log.stream) << setfill('0') << setw(2) << l.table[i].sn << " "; //setfill('0') << setw(2) - добавить ноль
				}
				(*log.stream) << l.table[i].lexema;
				if (l.table[i].idxTI != TI_NULLIDX)
				{
					if (l.table[i].lexema == LEX_AT)
						(*log.stream) << "[" << l.table[i].idxTI << "]";
					else (*log.stream) << "{" << l.table[i].idxTI << "}";
				}
			}
		}
		(*log.stream) << endl << endl;
	}
}