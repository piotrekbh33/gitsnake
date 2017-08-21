#include "Goal.h"

Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	LosujGoal(rng, brd, snake);
}

void Goal::LosujGoal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	std::uniform_int_distribution<int>xPositionLosowa(0, brd.SzerokoscTablicy() - 1);
	std::uniform_int_distribution<int>yPositionLosowa(0, brd.WysokoscTablicy() - 1);

	Location newLoc;

	do                                                      //Petla sprawdza czy Goal nie pojawil sie na wezu
	{
		newLoc.x = xPositionLosowa(rng);
		newLoc.y = yPositionLosowa(rng);
	} while (snake.WazZjadaSiebie(newLoc));
		loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;// TODO: insert return statement here
}
