#pragma once

//all enums will be defined this way to properly scope them
//to create a variable of Enum-type
//CreatureStat::E
//to access values
//CreatureStat::Speed
struct CreatureStat
{
	enum E
	{
		Speed,
		Strength,
		Count
	};
};