#pragma once

namespace Div
{
	struct Divide
	{
		char word[DEV_MAX_WORD][DEV_WORD_SIZE];			// ������ ����
		int count_word;				// ����������� ����
		int	lines;					// ������
		Divide();
	};

	Divide DivideWord(In::IN, Log::LOG);		// ���������� in.txt �� �����
	void AddDivideWord(Divide &, int, char);	// ���������� ����� � ������
}