#include <iostream>
#include "ConsoleGameEngine.h"
using namespace std;



class Matrix : public olcConsoleGameEngine
{
public:
	Matrix()
	{
		m_sAppName = L"Matrix";
	}

private:
	struct string_Streamer
	{
		int nColumn = 0;
		float fPosition = 0;
		float fSpeed = 0;
		wstring sText;
	};

	list<string_Streamer> list_Streamers;

	int nMaxStreamers = 180;

	wchar_t Random_Character()
	{
		return (wchar_t)(rand() % 0x1EF + 0x00C0);
	}

	void PrepareStreamer(string_Streamer* s)
	{
		s->nColumn = rand() % ScreenWidth();
		s->fPosition = 0;
		s->fSpeed = rand() % 40 + 5;
		s->sText.clear();

		int nStreamerLength = rand() % 80 + 10;
		for (int i = 0; i < nStreamerLength; i++)
			s->sText.append(1, Random_Character());
	}


protected:	

	virtual bool OnUserCreate()
	{
		for (int n = 0; n < nMaxStreamers; n++)
		{
			string_Streamer s;
			PrepareStreamer(&s);
			list_Streamers.push_back(s);
		}
		return true;
	}


	virtual bool OnUserUpdate(float fElapsedTime)
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, 0);

		for (auto& s : list_Streamers)
		{
			s.fPosition += fElapsedTime * s.fSpeed;
			for (int i = 0; i < s.sText.size(); i++)
			{		
				short colour = s.fSpeed < 15.0f ? FG_DARK_GREEN : FG_GREEN; 
				if (i == 0)
					colour = FG_WHITE;
				else {
					if (i <= 2)
						colour = FG_GREY;
				}

				int nCharIndex = (i - (int)s.fPosition) % s.sText.size();
				Draw(s.nColumn, (int)s.fPosition - i, s.sText[nCharIndex], colour);
			
				if (rand() % 1000 < 5)
					s.sText[i] = Random_Character();
			}

			if (s.fPosition - s.sText.size() >= ScreenHeight())
				PrepareStreamer(&s);
		}
		return true;
	}
};


int main()
{

	Matrix matrix_effect;
	matrix_effect.ConstructConsole(128, 80, 12, 12);
	matrix_effect.Start();
	return 0;
}
