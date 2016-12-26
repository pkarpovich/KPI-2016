#include "stdafx.h"
namespace IT
{
	IdTable Create(int size)
	{
		Error::ErrorTable eT(ERROR_MAX_ENTRY);
		if (size > TI_MAXSIZE)		throw GET_ERROR(202)
		IdTable *New = new IdTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		return *New;
	}

	Entry::Entry()
	{
		strcpy_s(this->id, ID_MAXSIZE, "null");
		strcpy_s(this->prefId, ID_MAXSIZE, "null");
		strcpy_s(this->value.val, TI_STR_MAXSIZE, "0");
		this->idfirstLE = 0xffffffff;
		this->paramCount = 0;
		this->idtype = IT::T_NO;
		this->pointer = false;
		this->value.len = 0;
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
		char *buf = new char[255];
		prefId[0] = '\0';
		strcpy_s(prefId, 255, nameFunction);
		strcat_s(prefId, 255, word);
		strcpy_s(buf, 255, "kpi"); strcat_s(buf, 255, word);
		if (!isDecFunction)
		{
			for (int i = 0; i < idTable.size; i++)
			{
				if (idTable.table[i].idtype == IT::T_FUNC)
				{
					if (strcmp(buf, idTable.table[i].prefId) == 0)
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

	void ShowIT(IdTable iT, LT::LexTable l, Parm::PARM param, Log::LOG log)
	{
		char *buf = new char[255];
		DW(param.IT, "Таблица идентификаторов: \n");
		DW(param.IT, " IT  |   LT   | УКАЗ. |          ИМЯ         |           ТИП ИДЕНТИФИКАТОРА           |     ЗНАЧЕНИЕ\n");
		sprintf_s(buf, 255, "%s\n", std::string(115, '-').c_str());	DW(param.IT, buf);
		for (int i = 0; i < iT.size; i++)
		{
			sprintf_s(buf, 255, "%-1s%03d%-1s", " ", i, " ");	DW(param.IT, buf);
			sprintf_s(buf, 255, "|%-3s%03d%2s|", " ", iT.table[i].idfirstLE, "");	DW(param.IT, buf);
			if (iT.table[i].pointer) sprintf_s(buf, 255, "%-3s%s%-3s|", " ", "*", " ");
			else sprintf_s(buf, 255, "%-7s|", " ");
			DW(param.IT, buf);
			sprintf_s(buf, 255, "%22s|",iT.table[i].prefId);	DW(param.IT, buf);
			switch (iT.table[i].iddatatype)
			{
				case IT::DT_INT: sprintf_s(buf, 255, "%6s", "int");break;
				case IT::DT_STR: sprintf_s(buf, 255, "%6s", "str");break;
				default: sprintf_s(buf, 255, "%6s", " ");break;
			}
			DW(param.IT, buf); memset(buf, '\n', 254);
			switch (iT.table[i].idtype)
			{
				case IT::T_NO:			sprintf_s(buf, 255, "%34s|", " неизвестно");break;
				case IT::T_VAR:			sprintf_s(buf, 255, "%34s|", " переменная");break;
				case IT::T_FUNC:		sprintf_s(buf, 255, "%34s|", " функция");break;
				case IT::T_FUNC_I:		sprintf_s(buf, 255, "%34s|", " вызываемая функция");break;
				case IT::T_FUNC_IP:		sprintf_s(buf, 255, "%34s|", " параметры вызываемой функции");break;
				case IT::T_FUNC_P:		sprintf_s(buf, 255, "%34s|", " парамтры функции");break;
				case IT::T_CIRCLE_P:	sprintf_s(buf, 255, "%34s|", " параметры в цикле");break;
				case IT::T_CONDITION_P: sprintf_s(buf, 255, "%34s|", " параметры в условии");break;
				case IT::T_LITERAL:		sprintf_s(buf, 255, "%34s|", " литерал");break;
				default:				sprintf_s(buf, 255, "%34s|", " ");break;
			}
			DW(param.IT, buf); memset(buf, '\0', 254);
			if (iT.table[i].idtype == IT::T_VAR || iT.table[i].idtype == IT::T_LITERAL)
			{
				if (iT.table[i].iddatatype == IT::DT_INT) sprintf_s(buf, 255, "%5s", iT.table[i].value.val);
				else {	if (iT.table[i].value.len != 0)		sprintf_s(buf, 255, "%5s[%d]", iT.table[i].value.val, iT.table[i].value.len); }
			}
			DW(param.IT, buf, "\n"); memset(buf, '\0', 254);
		}
	}
}