#pragma once
#include "Board.h"
//#include "Location.h" to jest wszystko public wiec nie musimy deklarowac


class Snake //Pierwsza klasa reprezentuje calego weza
{
private:
	class Segment //Deklaracja klasy w klasie. Odnosi sie ona do segmentu weza.
	{
	public:
		void InicjacjaGlowy(const Location& loc);						//Inicjacja weza gdy ROSNIE (Glowy i Tulowia)  //Przesuwa sie za glowa. Przesuniecie segmentow od ostatniego (ogona)
		void InicjacjaBody(Color c_in);											
		void PrzejdzDoPoprzedniegoPS(const Segment& next);				//Follow// //Powoduje przejcie segmentow od ostatniego (ogon) do miejca poprzedniego segmentu. To powoduje ruch weza.
		void PrzesunGlowe(const Location& Delta_loc);					//MoveBy// //Przesuwa glowe o przesuniecie weza delta. Delta wartosc przesuniecia
		//void RysujPrzesuwajacySieSegment(Board& brd);
		void Draw(Board& brd) const;
		const Location& SprawdzLokacjeSegmentu() const;
		
	private:
		Location loc;
		Color c;

	};
public:
	Snake(const Location& loc);									//Inicjacja weza
	void PrzesunPrzez(const Location& Delta_loc);				//MoveBy//
	void PowodujeWzrostWeza();									//Grow//
	Location SprawdzNastepnaGlowyLokacje(const Location& Delta_loc) const;
	//void RysujWezaNaBoard(Board& brd) const;
	void Draw(Board& brd) const;
	bool WazZjadaSiebieBezOgonka(const Location& Ogon) const;
	bool WazZjadaSiebie(const Location& Ogon) const;
	bool CofanieWeza(const Location & Delta_loc) const;
	Location NieWchodzNaSiebie(Location& delta_correction) const;    //Korektoruje przesuniecie aby waz nie konczyl gry kiedy ma ogon i porusza sie w gore a my nacisniemy strzalke w dol. W prawo a my nacisniemy sztrzalke w lewo.
										            		   //Teraz waz po takim zdarzeniu kontynuuje swoj ruch w poprzednio wybranym kierunku.
private:
	static constexpr Color glowyColor = Colors::Yellow;
	//static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;				//Maksymalna dlugosc weza
	Segment segments[nSegmentsMax];							//Tablica jego elementow
	int nSegments = 1;										//Biezaca dlugosc weza. Uzywana ilosc aktualnie elementow tablicy.
};