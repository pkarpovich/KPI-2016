#include "stdafx.h"
#define it lex.iT.table
#define lt lex.l.table
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
			case IT::NO: cout << "no, "; break;
			case IT::INT: cout << "int, "; break;
			case IT::STR: cout << "str, "; break;
			case IT::BOOL: cout << "bool, "; break;
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

		enum lexem { PRINT, SIN, INIT, RETURN, IF, FUNC };
		stack<lexem> stack;
		vector<char *>vec;
		bool firstAction = false;
		bool check = false;
		bool isPrint = false;
		bool isAction = false;
		bool isLess = false; bool isMore = false;
		bool isIF = false; bool inIF = false; bool inElse = false;
		bool isCircle = false; bool inCircle = false;
		bool isFunc = false; bool isFuncParam = false; bool inFunc = false; bool isReturn = false;
		char *funcName = new char[50];
		char *buf = "null\0";
		char *equallu = new char[50];
		char *p2 = new char[50]; p2[0] = '\0';
		char *p3 = new char[50]; p3[0] = '\0';
		char *p4 = new char[50]; p4[0] = '\0';
		typeNible ND;
		for (int i = 0; i < lex.iT.size; i++)
		{
			if (!it[i].pointer)
			{
				switch (it[i].idtype)
				{
				case IT::L:
					if(it[i].iddatatype == IT::INT)
						Add(nible, setNible(NT::LEX_INIT, it[i].iddatatype, it[i].prefId, _itoa(it[i].value.vint, p3, 10)));
					else if(it[i].iddatatype == IT::STR)
						Add(nible, setNible(NT::LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.vstr.str));
					break;
				case IT::V:
					if (it[i].iddatatype == IT::INT)
						Add(nible, setNible(NT::INIT, it[i].iddatatype, it[i].prefId, _itoa(it[i].value.vint, p3, 10)));
					else if (it[i].iddatatype == IT::STR)
						Add(nible, setNible(NT::INIT, it[i].iddatatype, it[i].prefId, it[i].value.vstr.str));
					break;
				}
			}
		}
		for (int i = 0; i < lex.l.size; i++)
		{
			switch (lex.l.table[i].lexema)
			{
			case LEX_SEMICOLON: 
			{
				check = false;
				while (!stack.empty()) stack.pop();
				if (isAction)
				{
					isAction = false;
					PN::PolishNotation(lex, log, i);
					while (!check)	if (lex.l.table[--i].lexema == LEX_EQUALLU) check = true;	// доходим до начала строки
					while (lex.l.table[i].lexema != ';' && lex.l.table[i].lexema != '#' )
					{
						switch (lex.l.table[i].lexema)
						{
						case LEX_VARIABLE: case LEX_LITERAL:
							if(idit(i).idtype != IT::F)
							Add(nible, setNible(NT::INT_D, IT::NO, idit(i).prefId)); break;
						case LEX_ACTION:
						{
							if (strcmp(idit(i).id, "+") == 0) { Add(nible, setNible(NT::PLUS, IT::NO)); break; }
							else if (strcmp(idit(i).id, "-") == 0) { Add(nible, setNible(NT::MINUS, IT::NO)); break; }
							else if (strcmp(idit(i).id, "*") == 0) { Add(nible, setNible(NT::MUL, IT::NO)); break; }
							else if (strcmp(idit(i).id, "/") == 0) { Add(nible, setNible(NT::DIV, IT::NO)); break; }
						}
						}
						i++;
					}
					Add(nible, setNible(NT::INT_E, IT::NO, equallu));
					--i;
				}
				break;
			}
			case LEX_LEFTTHESIS:
			{
				if (isFunc)
				{
					isFunc = false;
					isFuncParam = true;
					inFunc = true;
				}				
				break;
			}
			case LEX_RIGHTTHESIS:
			{
				isFunc = false; isFuncParam = false;
				if(nible.table[nible.size-1].TN == NT::FANCPARAM) Add(nible, setNible(NT::PUSHINVOKE, IT::NO));
				if (isIF || isCircle)
				{
					strcpy(p2, vec.back()); vec.pop_back();
					strcpy(p3, vec.back()); vec.pop_back();
					if (isIF)
					{
						Add(nible, setNible(NT::IF, IT::NO, p2, p3));
						isIF = false; inIF = true;
					}
					else if (isCircle)
					{
						Add(nible, setNible(NT::CIRCLE, IT::NO, p2, p3));
						isCircle = false; inCircle = true;
					}
					if (isLess) { Add(nible, setNible(NT::LESS, IT::NO));	isLess = false; }
					if (isMore) { Add(nible, setNible(NT::MORE, IT::NO));	isMore = false; }
				}
				break;
			}
			case LEX_LEFTBRACE:
			{
				if (inFunc) Add(nible, setNible(NT::STARTFUNC, IT::NO)); break;
			}
			case LEX_RIGHTBRACE:
			{
				if (inIF)		{	Add(nible, setNible(NT::ENDIF, IT::NO,""));	inIF = false;	break;}
				if (inElse)		{	Add(nible, setNible(NT::ENDELSE, IT::NO, "")); inElse = false;	break;}
				if (inCircle)	{	Add(nible, setNible(NT::ENDCIRCLE, IT::NO, "")); inCircle = false;	break;}
				if(inFunc)		{	Add(nible, setNible(NT::ENDFUNC, IT::NO, funcName)); inFunc = false; break;}
				break;
				
			}
			case LEX_ELSE:
			{
				strcpy(nible.table[nible.size - 1].p2, "jmp @endElse\n");
				Add(nible, setNible(NT::ELSE, IT::NO));
				inElse = true;
				break;
			}
			case LEX_BEGIN_FUNCTION: Add(nible, setNible(NT::BEGIN, IT::NO));
			case LEX_INTEGER: 
				if (!isFunc) 
				{
					stack.push(lexem::INIT);
				}
			break;
			case LEX_SOUT: stack.push(lexem::PRINT); break;
			case LEX_BOOL_ACTION: 
				stack.push(lexem::IF); 
				if (strcmp(idit(i).id, ">") == 0)		isMore = true;
				else if (strcmp(idit(i).id, "<") == 0)	isLess = true;
				break;
			case LEX_CIRCLE: isCircle = true; break;
			case LEX_SIN: stack.push(lexem::SIN); break;
			case LEX_CONDITION: isIF = true; break;
			case LEX_RETURN: 
			{
				isReturn = true; break;
			}				
			case LEX_ENDL: strcpy(nible.table[nible.size - 1].p3, "endl"); break;
			case LEX_ACTION: isAction = true; break;
			case LEX_FUNCTION: stack.push(lexem::FUNC); isFunc = true; break;
			case LEX_EQUALLU:	strcpy(equallu, lex.iT.table[lex.l.table[i - 1].idxTI].prefId);	break;
			case LEX_VARIABLE: case LEX_LITERAL:
			{
				if (isFuncParam) { Add(nible, setNible(NT::PARAM_INIT, IT::INT, idit(i).prefId, "0")); break; }
				if (isIF)	{	vec.push_back(idit(i).prefId);	break;	}
				if (isCircle)	{	vec.push_back(idit(i).prefId);	break;	}
				if (isReturn && inFunc) { Add(nible, setNible(NT::RETURN, IT::INT, idit(i).prefId)); break; }
				if (idit(i).idtype == IT::F && idit(i).pointer) { isAction = true; Add(nible, setNible(NT::FUNCINVOKE, IT::INT, idit(i).prefId)); break; }
				if (idit(i).idtype == IT::IP) { Add(nible, setNible(NT::FANCPARAM, IT::INT, idit(i).prefId)); break; }
				while (!stack.empty())
				{
					switch (stack.top())
					{
					case lexem::FUNC: Add(nible, setNible(NT::FUNC, idit(i).iddatatype, idit(i).prefId)); strcpy(funcName, idit(i).prefId); break;
					case lexem::PRINT: Add(nible, setNible(NT::PRINT, idit(i).iddatatype, idit(i).prefId)); break;
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
	Entry setNible(typeNible TN, IT::IDDATATYPE TD,const char * p2,const char * p3,const char *p4)
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