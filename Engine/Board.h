#pragma once
#include "Graphics.h"
#include "Location.h"
// Hi Master
class Board
{
public:
	Board(Graphics& gfx);   //Konstructor inicjujacy grafike
	void DrawCell(const Location& loc, Color c);						//Rysuje kwadrat obok kwadratu 
	int SzerokoscTablicy() const;
	int WysokoscTablicy() const;
	bool WazJestWTablicy(const Location& loc) const;
	void RysujRamke();
private:
	static constexpr Color granicyColor = Colors::Blue;
	static constexpr int dimention = 20; //Wymiary komorki weza (Wymiary kwadratow w tablicy)
	static constexpr int width = 32;							 //szerokosc tablicy w ilosci komorek celi(kwadratow)
	static constexpr int height = 24;							 //wysokosc tablicy w ilosci komorek celi(kwadratow)
	Graphics& gfx;					//Przechowujemy w pamieci cache podrecznej informacje o graficznym obiekcie gfx dla wygody by go niw wywolywac caly czas.
	static constexpr int OgonCellPadding = 1;
	static constexpr int granicySzerokosc = 4;
	static constexpr int granicyPadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;


};