#include "stdafx.h"
int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024]; // печать

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
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
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
	}
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	}
	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; }; //конструктор по умолчанию 
	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach) //(результат работы лексического анализатора, грамматика Грейбах)
	{
		grebach = pgrebach;
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
						if(param.SA) CON_MFST_TRACE1
						MFST_TRACE1 //вывод
						savestate(log, param); //сохранить состояние автомата
						st.pop(); //извлекаем верхушку стека
						push_chain(chain); //поместить цепочку правила в стек
						rc = NS_OK; //найдено правило и цепочка... цепочка записана в стек
						if (param.SA) CON_MFST_TRACE2
						MFST_TRACE2 //вывод
					}
					else
					{
						if (param.SA) CON_MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE");
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE");
						savediagnosis(NS_NORULECHAIN); //код завершения
						rc = restate(log, param) ? NS_NORULECHAIN : NS_NORULE; //восстановить состояние автомата
					};
				}
				else rc = NS_ERROR; //неизвестный нетерминальный символ грамматики
			}
			else if ((st.top() == lenta[lenta_position])) //если текущий символ ленты равен вершине стека
			{
				lenta_position++; st.pop(); nrulechain = -1; rc = TS_OK;
				
				if (param.SA) CON_MFST_TRACE3
				MFST_TRACE3
			}
			else
			{
				if (param.SA) CON_MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
					rc = restate(log, param) ? TS_NOK : NS_NORULECHAIN;
			};
		}
		else
		{
			rc = LENTA_END;
			if (param.SA) CON_MFST_TRACE4("LENTA_END")
			MFST_TRACE4("LENTA_END")
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
		if (param.SA) CON_MFST_TRACE6("SAVESTATE:", storestate.size());
		MFST_TRACE6("SAVESTATE:", storestate.size());
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
			if (param.SA) {CON_MFST_TRACE5("RESSTATE")	CON_MFST_TRACE2	}
			MFST_TRACE5("RESSTATE")
				MFST_TRACE2
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
		case LENTA_END: if (param.SA) { CON_MFST_TRACE4("------>LENTA_END") }
						if(param.SA || param.LT || param.IT)
						{
			cout << "------------------------------------------------------------------" << endl;
			cout << setw(4) << left << 0 << " : всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок\n\n" << endl;
		}
			MFST_TRACE4("------>LENTA_END")
			(*log.stream) << "------------------------------------------------------------------" << endl;
			(*log.stream) << setw(4) << left << 0 << " : всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок\n\n" << endl;
			rc = true;
			break;
		case NS_NORULE: if (param.SA) {
			CON_MFST_TRACE4("------>NS_NORULE")
			cout << "------------------------------------------------------------------" << endl;
			cout << getDiagnosis(0, buf, log, param) << endl;
			cout << getDiagnosis(1, buf, log, param) << endl;
			cout << getDiagnosis(2, buf, log, param) << endl;
		}
			MFST_TRACE4("------>NS_NORULE")
			(*log.stream) << "------------------------------------------------------------------" << endl;
			(*log.stream) << getDiagnosis(0, buf, log, param) << endl;
			(*log.stream) << getDiagnosis(1, buf, log, param) << endl;
			(*log.stream) << getDiagnosis(2, buf, log, param) << endl;
			break;
		case NS_NORULECHAIN: if (param.SA) CON_MFST_TRACE4("------>NS_NORULENORULECHAIN")
			MFST_TRACE4("------>NS_NORULENORULECHAIN") break;
		case NS_ERROR: if (param.SA) CON_MFST_TRACE4("------>NS_ERROR")
			MFST_TRACE4("------>NS_ERROR") break;
		case SURPRISE: if (param.SA) CON_MFST_TRACE4("------>SURPRISE")
			MFST_TRACE4("------>SURPRISE") break;
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
		char *rc = "";
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::ERROR_MESSAGE err = Error::getError(errid);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lex.table[lpos].sn, err.message);
			(*log.stream) << "Ошибка " << err.id << ": " << err.message << ". Строка " << lex.table[lpos].sn << endl;
			rc = buf;
		}
		return rc;
	}

	void Mfst::printrules(Log::LOG log, Parm::PARM param, std::stack<MFST::MfstState>& nstate)
	{
		(*log.stream) << "Синтаксический анализ - Выполнен" << endl;
		if(param.R) cout << "Синтаксический анализ - Выполнен" << endl;
		MfstState state;
		nstate = storestate;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			cout <<"Номер правила: "<< state.lenta_position<< endl;
			rule = grebach.getRule(state.nrule);
			if(param.R) CON_MFST_TRACE7
			MFST_TRACE7
		}
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