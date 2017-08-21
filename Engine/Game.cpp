/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	brd(gfx),						//inicjacja konstruktora Board
	snake{ {2, 2}},
	goal(rng, brd, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (graZaczeta)
	{

		if (!gameZakonczona)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				Delta_loc = { 0, -1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				Delta_loc = { 0, 1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				Delta_loc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				Delta_loc = { 1, 0 };
			}

			++SnakeIloscRuchow;

			if (SnakeIloscRuchow >= SnakeSpeed)
			{
				SnakeIloscRuchow = 0;
				Delta_loc = snake.NieWchodzNaSiebie(Delta_loc);								//Korektoruje przesuniecie aby waz nie konczyl gry kiedy ma ogon i porusza sie w gore a my nacisniemy strzalke w dol. W prawo a my nacisniemy sztrzalke w lewo.
				const Location next = snake.SprawdzNastepnaGlowyLokacje(Delta_loc);
				if (!brd.WazJestWTablicy(next) ||
					snake.WazZjadaSiebieBezOgonka(next))
				{
					gameZakonczona = true;
				}
				else
				{
					const bool eating = next == goal.GetLocation();
					if (eating)//wnd.kbd.KeyIsPressed(VK_CONTROL))
					{
						snake.PowodujeWzrostWeza();
					}
					//if (!snake.CofanieWeza(next))

					snake.PrzesunPrzez(Delta_loc);

					if (eating)
					{
						goal.LosujGoal(rng, brd, snake);
					}
				}
			}

			++SnakePrzyspieszeniaLicznik;

			if (SnakePrzyspieszeniaLicznik >= SnakePrzyspieszenie)
			{
				SnakePrzyspieszeniaLicznik = 0;
				SnakeSpeed = std::max(--SnakeSpeed, SnakeSpeedMin);     //Zwraca wieksza z liczb podanych w nawiasie
				
				/*--SnakeSpeed;
				if (SnakeSpeed < 0)
				{
					SnakeSpeed = 0;
				}*/
			}

		}
	}
	else
	{
		graZaczeta = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}


void Game::ComposeFrame()
{
	if (graZaczeta)
	{

		snake.Draw(brd);
		goal.Draw(brd);
		//snake.probka(Delta_loc);
		if (gameZakonczona)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);

		}
		brd.RysujRamke();
	}
	else
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
	/*std::uniform_int_distribution<int>kolor(0, 255);
	for (int i = 0; i < brd.SzerokoscTablicy(); ++i)         //UWAGA!!! PETLE BEDA NAM RYSOWAC KWADRATY W LINI PIONOWEJ OD GORY DO DOLU.
	{														 //PETLE TYLKO JE ROZMIESZCZA A FUNKCJA DrawCell NARYSUJE MALE KWADRATY.
		for (int i1 = 0; i1 < brd.WysokoscTablicy(); ++i1)
		{
			Location loc = { i, i1 };					//Uwaga tutaj tworzymy konstraktor dla klasy Location dla obiectu loc. To jest inicjacja loc.
			Color c(kolor(rng), kolor(rng), kolor(rng));//Mozemy tak zrobic konstraktor dla loc jesli nie ma pivate danych oraz nie zostal zainicjowany w klasie. 
			brd.DrawCell(loc, c);
		}
	}*/
}
