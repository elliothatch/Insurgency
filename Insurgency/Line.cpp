#include "StdAfx.h"
#include "Line.h"


Line::Line(int x1, int y1, int x2, int y2)
	:m_point1(x1,y1),
	 m_point2(x2,y2),
	 m_points(calculatePoints(m_point1, m_point2))
{
}

Line::Line(std::pair<int,int> p1, std::pair<int, int> p2)
	:m_point1(p1),
	 m_point2(p2),
	 m_points(calculatePoints(m_point1, m_point2))
{
}


Line::~Line(void)
{
}

std::vector<std::pair<int,int>> Line::calculatePoints(std::pair<int,int> p1, std::pair<int,int> p2)
{
	std::vector<std::pair<int,int>> points;
	int x1 = p1.first;
	int y1 = p1.second;
	int x2 = p2.first;
	int y2 = p2.second;
	int delta_x = x2 - x1;
	char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
 
    int delta_y = y2 - y1;
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
 
	points.push_back(std::pair<int,int>(x1, y1));
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
 
            error += delta_y;
            x1 += ix;
 
			points.push_back(std::pair<int,int>(x1, y1));
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
 
            error += delta_x;
            y1 += iy;
 
			points.push_back(std::pair<int,int>(x1, y1));
        }
	}
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