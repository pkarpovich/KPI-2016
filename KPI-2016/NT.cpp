#include "stdafx.h"
#define it Lex.iT.table
#define lt Lex.l.table
#define nt nible.table
#define idit(i) Lex.iT.table[Lex.l.table[i].idxTI]
#define ADD_NT(type, ...) Add(nible, setNible(type, __VA_ARGS__))
namespace NT
{
	Nible::Nible(int size)
	{
		this->maxSize = size;
		this->size = 0;
		this->table = new Entry[size];
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
		return 0;
	}

	Entry setNible(int TN, const int TD, const char * p2, const char * p3, const char *p4)
	{
		Entry *temp = new Entry;
		temp->TN = TN;
		temp->TD = TD;
		strcpy_s(temp->p2, NIBLE_MAX_SIZE, p2);
		strcpy_s(temp->p3, NIBLE_MAX_SIZE, p3);
		strcpy_s(temp->p4, NIBLE_MAX_SIZE, p4);
		return *temp;
	}

	void Print(Nible table, Parm::PARM param,Log::LOG log)
	{
		for (int i = 0; i < table.size; i++)
		{
			switch (table.table[i].TN)
			{
			case typeNible::PLUS: DW(param.NT,"PLUS(") break;
			case typeNible::MINUS:DW(param.NT, "MINUS(") break;
			case typeNible::MUL:DW(param.NT, "MUL(") break;
			case typeNible::DIV:DW(param.NT, "DIV(") break;
			case typeNible::IF:DW(param.NT, "IF(") break;
			case typeNible::END_IF:DW(param.NT, "ENDIF(") break;
			case typeNible::CIRCLE:DW(param.NT, "CIRCLE(") break;
			case typeNible::END_CIRCLE:DW(param.NT, "END_CIRCLE(") break;
			case typeNible::MORE:DW(param.NT, "MORE(") break;
			case typeNible::LESS:DW(param.NT, "LESS(") break;
			case typeNible::PRINT:DW(param.NT, "PRINT(") break;
			case typeNible::INIT:DW(param.NT, "INIT(") break;
			case typeNible::LEX_INIT:DW(param.NT, "LEX_INIT(") break;
			case typeNible::PUSH:DW(param.NT, "PUSH(") break;
			case typeNible::POP:DW(param.NT, "POP(") break;
			case typeNible::INC:DW(param.NT, "INC(") break;
			case typeNible::DEC:DW(param.NT, "DEC(") break;
			case typeNible::EQUALITY: DW(param.NT, "EQUAKITY(") break;
			case typeNible::NO_EQUALITY: DW(param.NT, "NO_EQUALITY(") break;
			case typeNible::LESS_OR_EQUALLY: DW(param.NT, "LESS_OR_EQUALLY(") break;
			case typeNible::MORE_OR_EQUALLY: DW(param.NT, "MORE_OR_EQUALLY(") break;
			case typeNible::RETURN:DW(param.NT, "RETURN(") break;
			case typeNible::END_ELSE:DW(param.NT, "END_ELSE(") break;
			case typeNible::ELSE:DW(param.NT, "ELSE(") break;
			case typeNible::FUNC:DW(param.NT, "FUNC(") break;
			case typeNible::PARAM_INIT:DW(param.NT, "PARAM_INIT(") break;
			case typeNible::START_FUNC:DW(param.NT, "START_FUNC(") break;
			case typeNible::END_FUNC:DW(param.NT, "END_FUNC(") break;
			case typeNible::END_MAIN_FUNC:DW(param.NT, "END_MAIN_FUNC("); break;
			case typeNible::FUNC_INVOKE:DW(param.NT, "FUNC_INVOKE(") break;
			case typeNible::FANC_PARAM:DW(param.NT, "FUNC_PARAM(") break;
			case typeNible::BEGIN:DW(param.NT, "BEGIN(") break;
			case typeNible::KPI_LIB:DW(param.NT, "KPI_LIB(") break;
			case typeNible::PUSH_INVOKE:DW(param.NT, "PUSH_INVOKE(") break;
			default: DW(param.NT, "UNKNOWN(") break;
			}
			switch (table.table[i].TD)
			{
			case IT::DT_NO: DW(param.NT, "no,") break;
			case IT::DT_INT: DW(param.NT, "int,") break;
			case IT::DT_STR: DW(param.NT, "str,") break;
			}
			DW(param.NT, table.table[i].p2, ", ", table.table[i].p3, ", ", table.table[i].p4, ")\n");
		}
		DW(param.NT,"\n")
	}

	bool operator==(Entry e1, Entry e2)
	{
		if (strcmp(e1.p2, e2.p2) == 0 && strcmp(e1.p3, e2.p3) == 0 && strcmp(e1.p4, e2.p4) == 0 && e1.TD == e2.TD && e1.TN == e1.TN)
		{
			return true;
		}
		return false;
	}

	Nible genNible(LA::LexAnaliz Lex, Log::LOG log, Parm::PARM param)
	{
		Nible nible(9000);

		stack<char> stack;
		std::stack<int> circleCount;
		bool isReturn = 0;
		char *funcName = new char[NIBLE_MAX_SIZE];	char *equallu = new char[NIBLE_MAX_SIZE]; char *buf = new char[NIBLE_MAX_SIZE];
		int paramCount = 0, conditionCount = 0;
		for (int i = 0; i < Lex.iT.size; i++)
		{
			if (!it[i].pointer)
			{
				switch (it[i].idtype)
				{
				case IT::T_LITERAL:
					if (it[i].iddatatype == IT::DT_INT)	ADD_NT(LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val);
					else if (it[i].iddatatype == IT::DT_STR) ADD_NT(LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val);
					break;
				case IT::T_VAR:
					if (it[i].iddatatype == IT::DT_INT)	ADD_NT(INIT, it[i].iddatatype, it[i].prefId, it[i].value.val);
					else if (it[i].iddatatype == IT::DT_STR) ADD_NT(INIT, it[i].iddatatype, it[i].prefId, it[i].value.val);
					break;
				case IT::T_FUNC_IP: case IT::T_CIRCLE_P: case IT::T_CONDITION_P:
					if (it[i].iddatatype == IT::DT_INT) ADD_NT(LEX_INIT, it[i].iddatatype, it[i].prefId, it[i].value.val);
					break;
				}
			}
		}
		for (int i = 0; i < Lex.l.size; i++)
		{
			if (PN::needPN(Lex, log, lt[i].sn))
			{
				bool check = false;
				int sn = lt[i].sn;
				while (!check)
				{
					switch (lt[++i].lexema)
					{
					case LEX_EQUALLU: strcpy_s(equallu, NIBLE_MAX_SIZE, it[lt[i - 1].idxTI].prefId); check = true; break;
					case LEX_INC: strcpy_s(equallu, NIBLE_MAX_SIZE, it[lt[i - 1].idxTI].prefId); check = true; i--; break;
					}
				}
				while (lt[i].sn == sn)
				{
					switch (lt[i].lexema)
					{
					case LEX_VARIABLE: case LEX_LITERAL:
					{
						switch (idit(i).idtype)
						{
						case IT::T_FUNC_I: ADD_NT(FUNC_INVOKE, IT::DT_INT, idit(i).prefId); break;
						case IT::T_FUNC_IP: ADD_NT(FANC_PARAM, IT::DT_INT, idit(i).prefId); break;
						default: ADD_NT(PUSH, IT::DT_NO, idit(i).prefId); break;
						}
						break;
					}
					case LEX_ACTION:
					{
						switch (lt[i].automat)
						{
						case FST::PLUS: ADD_NT(PLUS); break;
						case FST::MINUS: ADD_NT(MINUS); break;
						case FST::STAR: ADD_NT(MUL); break;
						case FST::DIRSLASH: ADD_NT(DIV); break;
						}
						break;
					}
					case LEX_INC:
					{
						switch (lt[i].automat)
						{
						case FST::INC: ADD_NT(INC, IT::DT_NO, idit(i - 1).prefId); break;
						case FST::DEC: ADD_NT(DEC, IT::DT_NO, idit(i - 1).prefId); break;
						}
						break;
					}
					}
					i++;
				}
				Add(nible, setNible(NT::POP, IT::DT_NO, equallu)); i--; continue;
			}
			if (!circleCount.empty())	_itoa_s(circleCount.top(), buf, 10, 10);
			switch (lt[i].lexema)
			{
			case LEX_CIRCLE: case LEX_SIN: case LEX_CONDITION: case LEX_FUNCTION: case LEX_SOUT:	stack.push(lt[i].lexema); break;
			case LEX_KPI_LIB: ADD_NT(KPI_LIB); break;
			case LEX_SEMICOLON: paramCount = 0;	while (!stack.empty()) stack.pop();	break;
			case LEX_LEFTBRACE:	if (lt[i].braceType == IT::T_FUNC)	ADD_NT(START_FUNC);	break;	// начало функ.
			case LEX_RIGHTBRACE:
			{
				switch (lt[i].braceType)
				{
				case IT::T_FUNC:
						if (strcmp(funcName, "begin") == 0) ADD_NT(END_MAIN_FUNC, IT::DT_NO, funcName);
					else	ADD_NT(END_FUNC, IT::DT_NO, funcName);
					break;
				case IT::T_CIRCLE: ADD_NT(END_CIRCLE, IT::DT_NO, buf); circleCount.pop(); break;
				case IT::T_ELSE:  ADD_NT(END_ELSE, IT::DT_NO, buf); circleCount.pop(); break;
				case IT::T_CONDITION: 	ADD_NT(END_IF, IT::DT_NO, buf);
					if (lt[i + 1].lexema != 'e') { ADD_NT(END_ELSE, IT::DT_NO, buf); circleCount.pop();	}break;
				} break;
			}
			case LEX_ENDL: strcpy_s(nt[lastNible(nible, NT::PRINT)].p3, NIBLE_MAX_SIZE, "endl"); break;
			case LEX_BEGIN_FUNCTION: ADD_NT(BEGIN); strcpy_s(funcName, NIBLE_MAX_SIZE, "begin"); break;
			case LEX_BOOL_ACTION:
				switch (lt[i].automat)
				{
				case FST::MORE: ADD_NT(MORE, IT::DT_NO, buf); break;
				case FST::LESS: ADD_NT(LESS, IT::DT_NO, buf); break;
				case FST::EQUALITY: ADD_NT(EQUALITY, IT::DT_NO, buf); break;
				case FST::NO_EQUALITY: ADD_NT(NO_EQUALITY, IT::DT_NO, buf); break;
				case FST::LESS_OR_EQUALLY: ADD_NT(LESS_OR_EQUALLY, IT::DT_NO, buf); break;
				case FST::MORE_OR_EQUALLY: ADD_NT(MORE_OR_EQUALLY, IT::DT_NO, buf); break;
				} 
				break;
			case LEX_RETURN: isReturn = true; break;				
			case LEX_EQUALLU:	stack.push(lt[i].lexema); strcpy_s(equallu, NIBLE_MAX_SIZE, it[lt[i - 1].idxTI].prefId); break;
			case LEX_VARIABLE: case LEX_LITERAL:
			{
				if (LA::WhereI(Lex, i) == IT::T_FUNC_P)
				{
					paramCount++;
					if (paramCount == 1)	ADD_NT(PARAM_INIT, IT::DT_INT, idit(i).prefId, "0");
					else ADD_NT(PARAM_SECOND_INIT, IT::DT_INT, idit(i).prefId, "0");
					break;
				}
				if (isReturn && strcmp(funcName, "begin") != 0) {	ADD_NT(RETURN, IT::DT_INT, idit(i).prefId); isReturn = false; break; }
				while (!stack.empty())
				{
					switch (stack.top())
					{
					case LEX_FUNCTION: ADD_NT(FUNC, idit(i).iddatatype, idit(i).prefId);
						strcpy_s(funcName, NIBLE_MAX_SIZE,idit(i).prefId); break;
					case LEX_SOUT: ADD_NT(PRINT, idit(i).iddatatype, idit(i).prefId); break;
					case LEX_CONDITION: circleCount.push(++conditionCount); _itoa_s(circleCount.top(), buf, 10, 10);
						ADD_NT(IF, IT::DT_NO, idit(i).prefId, it[lt[i].idxTI + 1].prefId); break;
					case LEX_CIRCLE: circleCount.push(++conditionCount); _itoa_s(circleCount.top(), buf, 10, 10);
						ADD_NT(CIRCLE, IT::DT_NO, idit(i).prefId, it[lt[i].idxTI + 1].prefId, buf); break;
					case LEX_EQUALLU:
						if (it[lt[i - 2].idxTI].iddatatype != IT::DT_STR)
						{
							ADD_NT(PUSH, IT::DT_NO, idit(i).prefId); 
							ADD_NT(POP, IT::DT_NO, equallu);
						}
						else ADD_NT(STR_PUSH, IT::DT_STR, idit(i).prefId, equallu);
						break;
					}
					stack.pop();
				}
				break;
			}
			}
		}
		Print(nible, param, log);
		return nible;
	}
}