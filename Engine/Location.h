#pragma once

class Location    // class domyslna wartosc dla zmiennych jest pivate. Zamiast slowa class mozna uzyc struct wtedy domyslna wartosc zmiennych jest public.
{
public:
	void Add(const Location& val)
	{
		x += val.x; // x = x + delta_loc.x;
		y += val.y; // y = y + delta_loc.y;
	}
	bool operator == (const Location& rhs) const //Porownanie lokacji z operator //Potrzebne do funkcji WazZjadaSiebie.
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
	
};