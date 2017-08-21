#include "Board.h"
#include "Graphics.h"
#include <assert.h>

Board::Board(Graphics & gfx) 
	:
	gfx(gfx)					//Inicjuemy grafike przez referencje w konstruktorze
{}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	const int off_x = x + granicySzerokosc + granicyPadding;
	const int off_y = y + granicySzerokosc + granicyPadding;

	gfx.DrawSquare(loc.x * dimention + off_x + OgonCellPadding, loc.y * dimention + off_y + OgonCellPadding, dimention - OgonCellPadding*2, dimention - OgonCellPadding*2, c); //Rysuje kwadrat obok kwadratu 
}

int Board::SzerokoscTablicy() const
{
	return width;
}

int Board::WysokoscTablicy() const
{
	return height;
}

bool Board::WazJestWTablicy(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width
		   && loc.y >= 0 && loc.y < height;
}

void Board::RysujRamke()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (granicySzerokosc + granicyPadding) * 2 + height*dimention;
	const int right= left + (granicySzerokosc + granicyPadding) * 2 + width*dimention;
	//Gora Ramki
	gfx.DrawSquarePoints(left, top, right, top + granicySzerokosc, granicyColor);
	//Lewa Strona
	gfx.DrawSquarePoints(left, top + granicySzerokosc, left + granicySzerokosc, bottom - granicySzerokosc, granicyColor);
	//Prawa Strona
	gfx.DrawSquarePoints(right - granicySzerokosc, top + granicySzerokosc, right, bottom - granicySzerokosc, granicyColor);
	//Dol Ramki
	gfx.DrawSquarePoints(left, bottom - granicySzerokosc, right, bottom, granicyColor);

}
