#include "stdafx.h"
#define it lex.iT.table
#define lt lex.l.table
#define nt nible.table
#define idit(i) lex.iT.table[lex.l.table[i].idxTI]
namespace NT
{
	Nible Create(int size)
	{
		Nible *newNible = new Nible;
		newNible->maxSize = size;
		newNible->size = 0;
		newNible->table = new Entry[size];
		return *newNible;
	}
	void Add(Nible& table, Entry entry)
	{
		if (entry.TN == NT::INIT || entry.TN == NT::LEX_INIT)
		{
			for (int i = 0; i < table.size; i++)
			{
				if (table.table[i] == entry)	return;
			}
		}	
		table.table[table.size++] = entry;
	}

	void Delete(Nible& table, Entry entry)
	{
		for (int i = 0; i < table.size; i++)
		{
			if (table.table[i] == entry)
			{
				for (int k = i + 1; k <= table.size; k++)
				{
					table.table[i++] = table.table[k];
				}
				table.size--;
				break;
			}
		}
	}

	int lastNible(Nible& table, typeNible TN)
	{
		for (int i = table.size; i >= 0; i--)
		{
			if (table.table[i].TN == TN)	return i;
		}
	}


	void Print(Nible table)
	{
		cout << endl;
		for (int i = 0; i < table.size; i++)
		{
			switch (table.table[i].TN)	
			{
			case typeNible::PLUS:cout << "PLUS( "; break;
			case typeNible::MINUS:cout << "MINUS( "; break;
			case typeNible::MUL:cout << "MUL( "; break;
			case typeNible::DIV:cout << "DIV( "; break;
			case typeNible::IF:cout << "IF( "; break;
			case typeNible::ENDIF:cout << "ENDIF( "; break;
			case typeNible::CIRCLE:cout << "CIRCLE( "; break;
			case typeNible::ENDCIRCLE:cout << "ENDCIRCLE( "; break;
			case typeNible::MORE:cout << "MORE( "; break;
			case typeNible::LESS:cout << "LESS( "; break;
			case typeNible::PRINT:cout << "PRINT( "; break;
			case typeNible::INIT:cout << "INIT( "; break;
			case typeNible::INT_D:cout << "PUSH("; break;
			case typeNible::INT_E:cout << "POP("; break;
			case typeNible::LEX_INIT: cout << "LEX_INIT( "; break;
			case typeNible::RETURN:cout << "RETURN( "; break;
			case typeNible::ENDELSE:cout << "ENDELSE( "; break;
			case typeNible::ELSE:cout << "ELSE( "; break;
			case typeNible::FUNC:cout << "FUNC( "; break;
			case typeNible::PARAM_INIT:cout << "PARAM_INIT( "; break;
			case typeNible::STARTFUNC:cout << "STARTFUNT( "; break;
			case typeNible::ENDFUNC:cout << "ENDFUNC( "; break;
			case typeNible::FUNCINVOKE:cout << "FUNCINVOKE( "; break;
			case typeNible::FANCPARAM:cout << "FUNCPARAM( "; break;
			case typeNible::BEGIN:cout << "BEGIN( "; break;
			case typeNible::PUSHINVOKE:cout << "PUSHINVOKE( "; break;
			default: cout << "UNKNOWN( "; break;
			}
			switch(table.table[i].TD)
			{
			case IT::DT_NO: cout << "no, "; break;
			case IT::DT_INT: cout << "int, "; break;
			case IT::DT_STR: cout << "str, "; break;
			case IT::DT_BOOL: cout << "bool, "; break;
			}
			cout << table.table[i].p2 << ", " << table.table[i].p3 << ", " << table.table[i].p4 << ")" << endl;
		}
		cout << endl;
	}

	bool operator==(Entry e1, Entry e2)
	{
		if (strcmp(e1.p2, e2.p2) == 0 && strcmp(e1.p3, e2.p3) == 0 && strcmp(e1.p4, e2.p4) == 0 && e1.TD == e2.TD && e1.TN == e1.TN)
		{
			return true;
		}
		return false;
	}

	Nible genNible(LA::LexAnaliz lex, Log::LOG log)
	{
		Nible nible = Create(9000);

		stack<char> stack;
		bool check = 0, isAction = 0, isReturn = 0;
		char *funcName = new char[50];	char *equallu = new char[50];
		int paramCount = 0;
		for (int i = 0; i < lex.iT.size; i++)
		{
			if (!it[i].pointer)
			{
				switch (it[i].idtype)
				{
				case IT::T_LITERAL:
					if(it[i].iddatatype == IT::DT_INT)
						Add(nible, setNible(NT::LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val));
					else if(it[i].iddatatype == IT::DT_STR)
						Add(nible, setNible(NT::LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val));
					break;
				case IT::T_VAR:
					if (it[i].iddatatype == IT::DT_INT)
						Add(nible, setNible(NT::INIT, it[i].iddatatype, it[i].prefId, it[i].value.val));
					else if (it[i].iddatatype == IT::DT_STR)
						Add(nible, setNible(NT::INIT, it[i].iddatatype, it[i].prefId, it[i].value.val));
					break;
				case IT::T_FUNC_IP:
						if (it[i].iddatatype == IT::DT_INT)
							Add(nible, setNible(NT::LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val));
				case IT::T_CIRCLE_P:
						if (it[i].iddatatype == IT::DT_INT)
							Add(nible, setNible(NT::LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val));
				}
			}
		}
		for (int i = 0; i < lex.l.size; i++)
		{
			if (PN::needPN(lex, log, lex.l.table[i].sn))
			{
				check = false;
				//PN::PolishNotation(lex, log, i);
				int sn = lex.l.table[i].sn;
				while (!check)
				{
					if (lex.l.table[++i].lexema == LEX_EQUALLU)
					{
						strcpy(equallu, lex.iT.table[lex.l.table[i - 1].idxTI].prefId);
						check = true;	// доходим до начала строки
					}
				}
				while (lex.l.table[i].sn == sn)
				{
					switch (lex.l.table[i].lexema)
					{
					case LEX_VARIABLE: case LEX_LITERAL:
						if (idit(i).idtype == IT::T_FUNC_I) { isAction = true; Add(nible, setNible(NT::FUNCINVOKE, IT::DT_INT, idit(i).prefId)); break; }
						if (idit(i).idtype == IT::T_FUNC_IP) { Add(nible, setNible(NT::FANCPARAM, IT::DT_INT, idit(i).prefId)); break; }
							Add(nible, setNible(NT::INT_D, IT::DT_NO, idit(i).prefId)); break;
						break;
					case LEX_ACTION:
					{
						switch (lt[i].automat)
						{
						case FST::PLUS: Add(nible, setNible(NT::PLUS, IT::DT_NO)); break;
						case FST::MINUS: Add(nible, setNible(NT::MINUS, IT::DT_NO)); break;
						case FST::STAR: Add(nible, setNible(NT::MUL, IT::DT_NO)); break;
						case FST::DIRSLASH:Add(nible, setNible(NT::DIV, IT::DT_NO)); break;
						}
						break;
					}
					case LEX_RIGHTTHESIS:
						Add(nible, setNible(NT::PUSHINVOKE, IT::DT_NO)); break;
					}
					i++;
				}
				Add(nible, setNible(NT::INT_E, IT::DT_NO, equallu));
			}
			switch (lex.l.table[i].lexema)
			{
			case LEX_CIRCLE: case LEX_SIN: case LEX_CONDITION: case LEX_FUNCTION: case LEX_SOUT:	stack.push(lt[i].lexema); break;
			case LEX_KPI_LIB: Add(nible, setNible(NT::KPILIB, IT::DT_NO)); break;
			case LEX_SEMICOLON: 
			{
				check = false;
				paramCount = 0;
				while (!stack.empty()) stack.pop();
				if (isAction)
				{
					isAction = false;
					
				}
				break;
			}
			case LEX_LEFTBRACE:	
				if (lt[i].braceType == IT::T_FUNC)
					Add(nible, setNible(NT::STARTFUNC, IT::DT_NO));
				break;
			case LEX_RIGHTBRACE:
			{
				switch (lt[i].braceType)
				{
				case IT::T_FUNC:
					if(strcmp(funcName,"begin") == 0) Add(nible, setNible(NT::ENDMAINFUNC, IT::DT_NO, funcName));
					else	Add(nible, setNible(NT::ENDFUNC, IT::DT_NO, funcName)); 
					break;
				case IT::T_CIRCLE: Add(nible, setNible(NT::ENDCIRCLE, IT::DT_NO));	break;
				case IT::T_ELSE: Add(nible, setNible(NT::ENDELSE, IT::DT_NO)); break;
				case IT::T_CONDITION: Add(nible, setNible(NT::ENDIF, IT::DT_NO));
					if (lt[i + 1].lexema != 'e')	Add(nible, setNible(NT::ENDELSE, IT::DT_NO)); break;
				}
				break;
			}
			case LEX_ELSE:	Add(nible, setNible(NT::ELSE, IT::DT_NO)); break;
			case LEX_BEGIN_FUNCTION: Add(nible, setNible(NT::BEGIN, IT::DT_NO)); strcpy(funcName, "begin"); break;
			case LEX_BOOL_ACTION:
				if(lt[i].automat == FST::MORE)	Add(nible, setNible(NT::MORE, IT::DT_NO));
				else if(lt[i].automat == FST::LESS) Add(nible, setNible(NT::LESS, IT::DT_NO));
				break;
			case LEX_RETURN: isReturn = true; break;				
			case LEX_ENDL: strcpy(nt[lastNible(nible,NT::PRINT)].p3, "endl"); break;
			case LEX_ACTION: isAction = true; break;
			case LEX_EQUALLU:	stack.push(lt[i].lexema); strcpy(equallu, lex.iT.table[lex.l.table[i - 1].idxTI].prefId);	break;
			case LEX_VARIABLE: case LEX_LITERAL:
			{
				if (LA::WhereI(lex, i) == IT::T_FUNC_P)
				{
					paramCount++;
					if(paramCount == 1)		Add(nible, setNible(NT::PARAM_INIT, IT::DT_INT, idit(i).prefId, "0"));
					else Add(nible, setNible(NT::PARAM_SECOND_INIT, IT::DT_INT, idit(i).prefId, "0"));
					break;
				}
				if (isReturn) { Add(nible, setNible(NT::RETURN, IT::DT_INT, idit(i).prefId)); isReturn = false; break; }
				if (idit(i).idtype == IT::T_CONDITION_P) { Add(nible, setNible(NT::FANCPARAM, IT::DT_INT, idit(i).prefId)); break; }
				while (!stack.empty())
				{
					switch (stack.top())
					{
					case LEX_FUNCTION: Add(nible, setNible(NT::FUNC, idit(i).iddatatype, idit(i).prefId)); strcpy(funcName, idit(i).prefId); break;
					case LEX_SOUT: Add(nible, setNible(NT::PRINT, idit(i).iddatatype, idit(i).prefId)); break;
					case LEX_CONDITION: Add(nible, setNible(NT::IF, IT::DT_NO, idit(i).prefId, it[lt[i].idxTI + 1].prefId)); break;
					case LEX_CIRCLE: Add(nible, setNible(NT::CIRCLE, IT::DT_NO, idit(i).prefId, it[lt[i].idxTI + 1].prefId)); break;
					case LEX_EQUALLU:Add(nible, setNible(NT::INT_D, IT::DT_NO, idit(i).value.val)); Add(nible, setNible(NT::INT_E, IT::DT_NO, equallu)); break;
					}
					stack.pop();
				}
				break;
			}
			}
		}
		Print(nible);
		return nible;
	}
	Entry setNible(int TN, int TD,const char * p2,const char * p3,const char *p4)
	{
		Entry *temp = new Entry;
		temp->TN = TN;
		temp->TD = TD;
		strcpy(temp->p2, p2);
		strcpy(temp->p3, p3);
		strcpy(temp->p4, p4);
		return *temp;
	}
}