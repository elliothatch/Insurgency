#pragma once
#include <vector>
class Line
{
public:

	Line(int x1, int y1, int x2, int y2);
	Line(std::pair<int,int> p1, std::pair<int, int> p2);

	~Line(void);

private:
	std::vector<std::pair<int,int>> calculatePoints(std::pair<int,int> p1, std::pair<int,int> p2);

	std::pair<int,int> m_point1;
	std::pair<int,int> m_point2;

	std::vector<std::pair<int,int>> m_points;
};

