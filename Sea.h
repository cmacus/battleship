// Sea.h
// Defines the sea
#include "Ship.h"
#include <iostream>
#include <cmath>
using namespace std;

const int ROWS=10;
const int COLS=10;

class Sea
{
public:
	Point point[ROWS][COLS];
	Ship ship[5];

	class Occupied
	{
	public:
		Point p;
		Occupied(Point P)
		{
			p.x=P.x;
			p.y=P.y;
			p.belongsTo=P.belongsTo;
		}
	};

	class Overflow
	{
	public:
		Point startP;
		int length;
		Overflow(Point StartP, int Length)
		{
			startP.x=StartP.x;
			startP.y=StartP.y;
			length=Length;
		}
	};

	Sea()
	{
		// Set points
		for (int i=0;i<COLS;i++)
			for (int j=0;j<ROWS;j++)
			{
				point[i][j].x=i;
				point[i][j].y=j;
				point[i][j].belongsTo=0;
			}
		// Give ship names
		for (int i=0;i<5;i++)
			ship[i].name=shipnames[i];
	}
	

	void setShip(int Type,Point Start,int Orient)
	{
		int Length=Type;
		switch(Orient)
		{
		case VERTICAL:
			for (int i=0;i<Length;i++)
			{
				if (point[Start.x][Start.y+i].belongsTo !=0)
				{
					for (int j=0;j<i;j++)
					{
						point[Start.x][Start.y+j].belongsTo=0;
					}
					throw Occupied(point[Start.x][Start.y+i]);
				}
				if (Length>ROWS-Start.y)
					throw Overflow(point[Start.x][Start.y+i],Length);
				point[Start.x][Start.y+i].belongsTo=Type;
			}
			break;
		case HORIZONTAL:
			for (int i=0;i<Length;i++)
			{
				if (point[Start.x+i][Start.y].belongsTo !=0)
				{
					for (int j=0;j<i;j++)
					{
						point[Start.x+j][Start.y].belongsTo=0;
					}
					throw Occupied(point[Start.x+i][Start.y]);
				}
				if (Length>COLS-Start.x)
					throw Overflow(point[Start.x+i][Start.y],Length);
				point[Start.x+i][Start.y].belongsTo=Type;
			}
			break;
		}
		ship[Type-1].setShip(Type,Start,Orient);
	}

	void show()
	{
		for (int j=0;j<ROWS;j++)
			for (int i=0;i<COLS;i++)
			{
				cout << " " << point[i][j].belongsTo;
				if (i==COLS-1)
					cout << endl;
			}
	}
};

class ComputerSea: public Sea
{
public:
	void setComputerShips()
	{
		// Set ships for the computer
			for (int i=0;i<5;i++)
			{
				try
				{
					
					setShip(i+1,Point(i,3),VERTICAL);
				}

				catch(Occupied occ)
				{
					cout << endl <<  "Point "<< occ.p.x <<"," << occ.p.y << " belongs to ship " << occ.p.belongsTo << endl;
				}

				catch (Overflow ovr)
				{
					cout << endl << "The ship starting at " << ovr.startP.x << "," << ovr.startP.y << " and of length " << ovr.length << " exceeds the limits of the sea" << endl;
				}
			}
	}
};
