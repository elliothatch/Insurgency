#include "StdAfx.h"
#include "Line.h"


Line::Line(int x1, int y1, int x2, int y2)
	:m_point1(x1,y1),
	 m_point2(x2,y2),
	 m_points()
{

}

Line::Line(std::pair<int,int> p1, std::pair<int, int> p2)
{
}


Line::~Line(void)
{
}

std::vector<std::pair<int,int>> Line::calculatePoints(std::pair<int,int> p1, std::pair<int,int> p2)
{
	std::vector<std::pair<int,int>> points;
	/*
	if(p1.first > p2.first)
		std::swap(p1.first, p2.first);

	//same x
	if(p1.first == p2.first)
	{
		if(p1.second > p2.second)
			std::swap(p1.second, p2.second);

		for(int i = p1.second; i<p2.second; i++)
		{
			points.push_back(std::pair<int,int>(p1.first, i));
		}
		return points;
	}
	//same y
	if(p1.second == p2.second)
	{
		if(p1.first < p2.first)
			std::swap(p1.first, p2.first);
		
		for(int i = p1.first; i<p2.first; i++)
		{
			points.push_back(std::pair<int,int>(i, p1.second));
		}
		return points;
	}

	int deltaX = p2.first - p1.first;
	int deltaY = p2.second - p1.second;

	if(deltaY > 0)
	{

	}
	*/
	return points;
}