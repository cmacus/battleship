// Defines an aim
#include "Point.h"

class Aim
{
public:
	bool has_hit;
	Point p;
	Aim()
	{}
	Aim(Point P)
	{
		p.x=P.x;
		p.y=P.y;
	}

	void operator = (Aim A)
	{
		p.x=A.p.x;
		p.y=A.p.y;
		has_hit=A.has_hit;
	}
};