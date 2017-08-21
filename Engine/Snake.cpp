#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	constexpr int liczbaKolorowychSegmentow = 4;
	constexpr Color OgonWeza[liczbaKolorowychSegmentow]= {
		{ 10, 100, 32 },
		{ 10, 130, 48 },
		{ 18, 160, 48 },
		{ 10, 130, 48 }
	
	};

	for (int i = 0; i < nSegmentsMax; ++i)
	{
		segments[i].InicjacjaBody(OgonWeza[i % liczbaKolorowychSegmentow]);
	}
	segments[0].InicjacjaGlowy(loc);
}

void Snake::PrzesunPrzez(const Location & Delta_loc)
{
	
		for (int i = nSegments - 1; i > 0; --i)
		{
			segments[i].PrzejdzDoPoprzedniegoPS(segments[i - 1]);  //Przesuniecie body weza o jeden segment od ogona w kierunku glowy.
		}
		//if (!CofanieWeza(Delta_loc))

		
			segments[0].PrzesunGlowe(Delta_loc);
		
		//segments[0].PrzesunGlowe(Delta_loc);						//Przesuwa glowe o wartosc Delta_loc

}

void Snake::PowodujeWzrostWeza()
{
	if (nSegments < nSegmentsMax)
	{
		//segments[nSegments].InicjacjaBody();            //Teraz to sie dzieje w konstruktorze
		++nSegments;
	}
}

Location Snake::SprawdzNastepnaGlowyLokacje(const Location & Delta_loc) const
{
	Location l(segments[0].SprawdzLokacjeSegmentu());
	l.Add(Delta_loc);
	return l;					//Zwraca kopie lokacji
	 
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}

}

bool Snake::WazZjadaSiebieBezOgonka(const Location & Ogon) const
{
	
	
	for (int i = 0; i < nSegments-1; ++i)							// -1 oznacza bez ogona (ostatniego segmentu)
	{
		if (segments[i].SprawdzLokacjeSegmentu() == Ogon)
		{
			return true;
		}
		
	}
	return false;
}

bool Snake::WazZjadaSiebie(const Location & Ogon) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].SprawdzLokacjeSegmentu() == Ogon)
		{
			return true;
		}
	}
	return false;
}

bool Snake::CofanieWeza(const Location & Delta_loc) const
{

	if (SprawdzNastepnaGlowyLokacje(Delta_loc) == segments[1].SprawdzLokacjeSegmentu())
	{
		return true;
	}
	return false;
	/*Location Pierwszy(segments[0].SprawdzLokacjeSegmentu());    //To ja dodalem 
	Pierwszy.Add(Delta_loc);

	if (Pierwszy == segments[0].SprawdzLokacjeSegmentu())
	{
		return true;
	}
	return false;*/

}

void Snake::Segment::InicjacjaGlowy(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::glowyColor;
}

void Snake::Segment::InicjacjaBody(Color c_in)
{
	c = c_in;
}

void Snake::Segment::PrzejdzDoPoprzedniegoPS(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::PrzesunGlowe(const Location & Delta_loc)
{
	assert(abs(Delta_loc.x) + abs(Delta_loc.y) == 1);
	loc.Add(Delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::SprawdzLokacjeSegmentu() const
{
	return loc;
}

Location Snake::NieWchodzNaSiebie(Location & delta_correction) const    //Korektoruje przesuniecie aby waz nie konczyl gry kiedy ma ogon i porusza sie w gore a my nacisniemy strzalke w dol. W prawo a my nacisniemy sztrzalke w lewo.
{																		//Dzieki temu porusza sie w dotychczasowym kierunku.
	if (SprawdzNastepnaGlowyLokacje(delta_correction) == segments[1].SprawdzLokacjeSegmentu())
	{
		delta_correction.x *= (-1);
		delta_correction.y *= (-1);
	}
	
	return delta_correction;
}
