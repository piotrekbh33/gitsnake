/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "SpriteCodex.h"
#include "Goal.h"
//#include "Location.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board brd;
	Snake snake;
	//Location Delta_loc;
	//int Delta_loc.x = 1;
	Location Delta_loc = { 1, 0 };
	//
	std::mt19937 rng;
	Goal goal;
	static constexpr int SnakeSpeedMin = 4;
	int SnakeSpeed = 20;							// 20 oznacza 20 frames odswiezenia ekranu. W rzeczywistosci to jest 3 ruchy na secunde.
	int SnakeIloscRuchow = 0;						//Przechowuje ilosc przesuniec weza.
	static constexpr int SnakePrzyspieszenie = 180;					//180 oznacza 3s. Biore 180 i dziele przez czestotliwosc odswiezania ekranu (60Hz) co daje 3 sekundy.
	int SnakePrzyspieszeniaLicznik = 0;
	bool gameZakonczona = false;
	bool graZaczeta = false;
	
	

	/********************************/
};