// Ship.h
// Defines a ship
#include "Aim.h"
#include <string>
using namespace std;

enum {DESTROYER=1,CRUISER,SUBMARINE,LINER,CARRIER};
enum {VERTICAL,HORIZONTAL};

string shipnames[5]={"Destroyer","Cruiser","Submarine","Liner","Carrier"};

class Ship
{
public:
	int type; // 1 to 5
	string name; // name
	int length; // 1 to 5
	Point start,end; // beginning and end
	int orient;
	int hit_count;
	
	Ship():hit_count(0){}
	void setShip(int Type, Point Start, int Orient)
	{
		type=Type;
		length=Type;
		orient=Orient;
		start.x=Start.x;
		start.y=Start.y;
		hit_count=0;

		switch(orient)
		{
		case VERTICAL:
			end.x=start.x;
			end.y=start.y+length-1;
			break;
		case HORIZONTAL:
			end.x=start.x+length-1;
			end.y=start.y;
			break;
		}

		name=shipnames[type-1];
	}

};