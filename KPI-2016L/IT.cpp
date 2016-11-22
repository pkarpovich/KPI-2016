#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
		{
			throw GET_ERROR(202, 5);
		}
		IdTable *New = new IdTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		return *New;
	}
	void Add(IdTable & idtable, Entry entry)
	{
		idtable.table[idtable.size++] = entry;
	}
	Entry GetEntry(IdTable &idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable & idTable, bool isDecFunction, char word[ID_MAXSIZE], char nameFunction[ID_MAXSIZE])
	{
		char *prefId = new char[255];
		prefId[0] = '\0';
		strcpy(prefId, nameFunction);
		strcat(prefId, word);
		if (!isDecFunction)
		{
			for (int i = 0; i < idTable.size; i++)
			{
				if (idTable.table[i].idtype == IT::T_FUNC)
				{
					if (strcmp(word, idTable.table[i].prefId) == 0)
					{
						return i;
					}
				}
				else
				{
					if (strcmp(prefId, idTable.table[i].prefId) == 0)
					{
						return i;
					}
				}
			}
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable & ittable)
	{
		delete &ittable;
	}

	void ShowIT(IdTable & iT, LT::LexTable l, Parm::PARM param, Log::LOG log)
	{
		if (param.IT == true)
		{
			cout << "Таблица идентификаторов: " << endl;
			cout << endl;
			bool isLiteral = 0;
			cout << " IT  |   LT   | УКАЗ. |      ИМЯ     |  ТИП ИДЕНТИФИКАТОРА  |     ЗНАЧЕНИЕ" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < iT.size; i++)
			{
				cout << setfill(' ') << setfill('0') << setw(2) << i << setw(4) << setfill(' ') << "|";
				cout << setw(5) << iT.table[i].idfirstLE << setw(4) << "|";
				if (iT.table[i].pointer == true) cout << setw(4) << "*" << setw(4) << "|";
				else cout << setw(4) << " " << setw(4) << "|";
				cout << setw(11);
				cout << iT.table[i].prefId << setw(4) << "|";
				cout << setw(8);
				switch (iT.table[i].iddatatype)
				{
				case IT::DT_INT: cout << "int"; break;
				case IT::DT_STR: cout << "str"; break;
				case IT::DT_BOOL: cout << "bool"; break;
				default: cout << " "; break;
				}
				cout << setw(12);
				switch (iT.table[i].idtype)
				{
				case IT::T_VAR: cout << "переменная"; break;
				case IT::T_FUNC: cout << "функция"; break;
				case IT::T_FUNC_P: cout << "параметр"; break;
				case IT::T_CIRCLE_P: cout << "параметр в цикле"; break;
				case IT::T_CONDITION_P: cout << "параметр в условии"; break;
				case IT::T_LITERAL: cout << "литерал"; isLiteral = true; break;
				default: cout << " "; break;
				}
				cout << setw(3);
				cout << "|";
				if (isLiteral || iT.table[i].value.vstr.len > 0)
				{
					if (iT.table[i].iddatatype == IT::DT_INT) cout << setw(3) << iT.table[i].value.vint;
					else if (iT.table[i].iddatatype == IT::DT_BOOL) cout << setw(3) << iT.table[i].value.vbool;
					else cout << setw(3) << iT.table[i].value.vstr.str << "[" << iT.table[i].value.vstr.len << "]";
				}
				cout << endl;
				isLiteral = 0;
			}
		}
		(*log.stream) << "Таблица идентификаторов: " << endl;
		(*log.stream) << endl;
		bool isLiteral = 0;
		(*log.stream) << " IT  |   LT   | УКАЗ. |      ИМЯ     |  ТИП ИДЕНТИФИКАТОРА  |     ЗНАЧЕНИЕ" << endl;
		(*log.stream) << "-------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < iT.size; i++)
		{
			(*log.stream) << setfill(' ') << setfill('0') << setw(2) << i << setw(4) << setfill(' ') << "|";
			(*log.stream) << setw(5) << iT.table[i].idfirstLE << setw(4) << "|";
			if (iT.table[i].pointer == true) (*log.stream) << setw(4) << "*" << setw(4) << "|";
			else (*log.stream) << setw(4) << " " << setw(4) << "|";
			(*log.stream) << setw(11);
			(*log.stream) << iT.table[i].prefId << setw(4) << "|";
			(*log.stream) << setw(8);
			switch (iT.table[i].iddatatype)
			{
			case IT::DT_INT: (*log.stream) << "int"; break;
			case IT::DT_STR: (*log.stream) << "str"; break;
			case IT::DT_BOOL: (*log.stream) << "bool"; break;
			default: (*log.stream) << " "; break;
			}
			(*log.stream) << setw(12);
			switch (iT.table[i].idtype)
			{
			case IT::T_VAR: (*log.stream) << "переменная"; break;
			case IT::T_FUNC: (*log.stream) << "функция"; break;
			case IT::T_FUNC_P: (*log.stream) << "параметр"; break;
			case IT::T_LITERAL: (*log.stream) << "литерал"; isLiteral = true; break;
			default: (*log.stream) << " "; break;
			}
			(*log.stream) << setw(3);
			(*log.stream) << "|";
			if (isLiteral || iT.table[i].value.vstr.len > 0)
			{
				if (iT.table[i].iddatatype == IT::DT_INT) (*log.stream) << setw(3) << iT.table[i].value.vint;
				else if(iT.table[i].iddatatype == IT::DT_BOOL) (*log.stream) << setw(3) << iT.table[i].value.vbool;
				else (*log.stream) << setw(3) << iT.table[i].value.vstr.str << "[" << iT.table[i].value.vstr.len << "]";
			}
			(*log.stream) << endl;
			isLiteral = 0;
		}
	}
	Entry::Entry()
	{
		strcpy(this->id, "null");
		strcpy(this->prefId, "null");
		this->idfirstLE = 0xffffffff;
		this->idtype = IT::T_NO;
		this->pointer = false;
		strcpy(this->value.vbool, "false");
		strcpy(this->value.vint, "0");
		strcpy(this->value.vstr.str, "\0");
		this->value.vstr.len = 0;
	}
}