#include "stdafx.h"
int FST_TRACE_n = -1;

char *sbuf = new char[205];
char *rbuf = new char[205];
char *lbuf = new char[1024];
char *buf = new char[255];

namespace MFST
{
	MfstState::MfstState()
	{
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	}
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)	// запоминаем наше правило
	{
		lenta_position = pposition;
		st = pst;
		nrule = pnrule;
		nrulechain = pnrulechain;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
		trace_pos = -1;
	}
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
		trace_pos = FST_TRACE_n;
	}
	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; }; //конструктор по умолчанию 
	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach) //(результат работы лексического анализатора, грамматика Грейбах)
	{
		grebach = pgrebach;
		//plex.table[plex.size++].lexema = '$';
		lex = plex;		
		lenta = new short[lenta_size = plex.size];
		for (int k(0); k < lenta_size; k++) lenta[k] = TS(lex.table[k].lexema); //заносит в ленту терминалы
		lenta_position = 0;
		st.push(grebach.stbottomT); //добавляет дно стека
		st.push(grebach.startN); //добавляет стартовый символ
		nrulechain = -1; //изначально правило равно -1
	}

	Mfst::RC_STEP Mfst::step(Log::LOG log, Parm::PARM param) //выполнить шаг автомата
	{
		RC_STEP rc = SURPRISE; //код возврата = ошибка возврата
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top())) //извлекаем последний элемент стека и проверяем нетерминал ли он
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0) //смотрим, если такое правило есть идём дальше, если нет то елсе
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{								//получаем следующую цепочку и выводим её номер, илбо возвращаем -1
						TRACE1;	DW(param.SA, buf);
						savestate(log, param); //сохранить состояние автомата
						st.pop(); //извлекаем верхушку стека
						push_chain(chain); //поместить цепочку правила в стек
						rc = NS_OK; //найдено правило и цепочка... цепочка записана в стек
						TRACE2; DW(param.SA, buf);
					}
					else
					{
						TRACE4("TNS_NORULECHAIN/NS_NORULE"); DW(param.SA, buf);
						savediagnosis(NS_NORULECHAIN); //код завершения
						rc = restate(log, param) ? NS_NORULECHAIN : NS_NORULE; //восстановить состояние автомата
					};
				}
				else rc = NS_ERROR; //неизвестный нетерминальный символ грамматики
			}
			else if ((st.top() == lenta[lenta_position])) //если текущий символ ленты равен вершине стека
			{
				lenta_position++; st.pop(); nrulechain = -1; rc = TS_OK;
				TRACE3; DW(param.SA, buf);
			}
			else
			{
				TRACE4("TS_NOK/NS_NORULECHAIN"); DW(param.SA, buf);
				rc = restate(log, param) ? TS_NOK : NS_NORULECHAIN;
			};
		}
		else
		{
			rc = LENTA_END;
			TRACE4("LENTA_END"); DW(param.SA, buf);
		};
		return rc;
	}

	bool Mfst::push_chain(GRB::Rule::Chain chain) //поместить цепочку правила в стек (цепочка правила)
	{
		for (int k = chain.size - 1; k >= 0; k--) //к = длинне цепочке-1. заносим цепочку в стек
			st.push(chain.nt[k]);
		return true;
	}

	bool Mfst::savestate(Log::LOG log, Parm::PARM param) //сохранить состояние автомата
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain)); //стек для сохранения состояния. заносим сохраняемое состояние
		TRACE6("SAVESTATE:", storestate.size()); DW(param.SA, buf);
		return true;
	}

	bool Mfst::restate(Log::LOG log, Parm::PARM param) //восстановить состояние автомата
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			TRACE5("RESSTATE"); DW(param.SA, buf);
			TRACE2; DW(param.SA, buf);
		}
		return rc;
	}

	bool Mfst::savediagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k(0);
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) diagnosis[j].lenta_position = -1;
		}
		return rc;
	}

	bool Mfst::start(Log::LOG log, Parm::PARM param)
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(log, param);
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step(log, param);
		switch (rc_step)
		{
		case LENTA_END:TRACE4("------>LENTA_END"); DW(param.SA, buf);
						if(param.SA || param.LT || param.IT)
						{
			cout << "------------------------------------------------------------------" << endl;
			cout << setw(4) << left << 0 << " : всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок\n\n" << endl;
		}
			(*log.stream) << "------------------------------------------------------------------" << endl;
			(*log.stream) << setw(4) << left << 0 << " : всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок\n\n" << endl;
			rc = true;
			break;
		case NS_NORULE:
			DW(param.SA, "------>NS_NORULE\n");
			sprintf_s(buf, 255, "%s\n", std::string(40, '-').c_str());	DW(param.SA, buf);
			DW(true, getDiagnosis(0, buf, log, param), "\n");
			DW(true, getDiagnosis(1, buf, log, param), "\n");
			DW(true, getDiagnosis(2, buf, log, param), "\n");
			system("pause");
			break;
		case NS_NORULECHAIN: TRACE4("------>NS_NORULENORULECHAIN"); DW(param.SA, buf); break;
		case NS_ERROR: TRACE4("------>NS_ERROR"); DW(param.SA, buf); break;
		case SURPRISE: TRACE4("------>SURPRISE"); DW(param.SA, buf); break;
		};
		return rc;
	}

	char* Mfst::getCSt(char* buf)
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = st._Get_container()[k];
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		}
		buf[st.size()] = 0x00;
		return buf;
	}

	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++) buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}

	char* Mfst::getDiagnosis(short n, char* buf, Log::LOG log, Parm::PARM param)
	{
		Error::ErrorTable eT(ERROR_MAX_ENTRY);
		char *rc = "";
		int errid = 0;
		int lpos = -1;
		short pos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			pos = diagnosis[n].trace_pos;
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::Entry err = Error::GetError(eT,errid);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "Ошибка %d: строка %d,позиция в трассировкe: %d, %s",
				err.id, lex.table[lpos].sn, pos, err.message);
			rc = buf;
		}
		return rc;
	}

	void Mfst::printrules(Log::LOG log, Parm::PARM param)
	{
		DW(param.R,"\nПравила:\n")
		MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			rule = grebach.getRule(state.nrule);
			TRACE7; DW(param.R, buf);
		}
		DW(param.R, "\n");
	}

	bool Mfst::savededucation()
	{
		MfstState state;
		deducatuon.nrules = new short[deducatuon.size = storestate.size()];
		deducatuon.nrulechains = new short[deducatuon.size];
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			deducatuon.nrules[k] = state.nrule;
			deducatuon.nrulechains[k] = state.nrulechain;
		}
		return true;
	}
}