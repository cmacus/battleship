// Battle.cpp : Defines the entry point for the console application.
//

#include "Sea.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
Aim my_aims[100];

int main(int argc, char* argv[])
{
	ComputerSea sea1;
	Sea sea2;
		
	sea1.setComputerShips();

	for (int i=0;i<5;i++)
		sea1.ship[i].hit_count=0;
	
	cout << "B A T T L E S H I P S ! " << endl;
	cout << "Set your ships first";

	// set player ships
	for (int i=0;i<5;i++)
	{
		int sx, sy, o;
		cout << endl << sea2.ship[i].name << ":" << endl << "Starting point x";
		cin >> sx;
		if (sx>COLS-1) 
		{
			cout << "Too many!\n";
			exit(0);
		}
		cout << "Starting point y";
		cin >> sy;
		if (sy>COLS-1)
		{
			cout << "Too many!\n";
			exit(0);
		}
		cout << "Orientation (0=vertical, 1=horizontal):";
		cin >> o;
		if (o!=0 && o!=1)
			exit(0);

		try
		{
			sea2.setShip(i+1,Point(sx,sy),o);
		}

		catch(Sea::Occupied occ)
		{
			cout << "Point " << occ.p.x << "," << occ.p.y << "is occupied by ship " << occ.p.belongsTo;
			i--;
		}
		catch(Sea::Overflow ovr)
		{
			cout << "The ship beginning from " << ovr.startP.x << "," << ovr.startP.y << " and of length " << ovr.length << " exceeds the limits of the sea";
			i--;
		}
	}
	sea2.show();

	
	int my_hit_ship=0; // the type of my ship you hit
	bool you_hit=false; // did you hit
	
	int your_response; // did I hit
	int i_hit_count=0; // my hit count
	int yours_sank_count=0; // your sank count
	int my_sank_count=0; // my sanc count
	int my_aim_count=0; // how many times aim aimed

	Aim my_current_aim,my_last_aim,my_last_but_aim;
	
	do
	{
		int ax,ay;
		cout << endl << "Enter your aim x";
		cin >> ax;
		if (ax>COLS-1)
			exit(0);
		cout << "Enter your aim y";
		cin >> ay;
		if (ay>ROWS-1)
			exit(0);
		
		my_hit_ship=sea1.point[ax][ay].belongsTo;

		if (!my_hit_ship)
		{
			you_hit=false;
			cout << "It is a miss";
		}
		else
		{
			you_hit=true;
			int my_hit_ship_index=my_hit_ship-1;
			sea1.ship[my_hit_ship_index].hit_count++;
			cout << "It is a hit";
			if (sea1.ship[my_hit_ship_index].hit_count==sea1.ship[my_hit_ship_index].length)
			{
				cout << endl << sea1.ship[my_hit_ship_index].name << " sunk";
				my_sank_count++;
				if (my_sank_count==5)
				{
					cout << "You win!" << endl;
					int c;
					cin >> c;
					exit(0);
				}
			}
		}
		
		//The computer's play

		// Selct my current aim
		if (my_aim_count==0) // if this is first aim
		{
			// select a random aim
			my_current_aim.p.x=rand()%COLS;
			my_current_aim.p.y=rand()%ROWS;
		}
		else if (my_aim_count==1) // this is the second aim
		{
			my_last_aim=my_aims[0]; // get my last aim
			if (my_last_aim.has_hit==false) // if last aim has not hit
			{
				// select a random aim
				my_current_aim.p.x=rand()%COLS;
				my_current_aim.p.y=rand()%ROWS;
			}
			else // if last aim has hit
			{
				if (my_last_aim.p.y!=0) // if last aim was not already at the top
				{
					// assume vertical ship
					my_current_aim.p.x=my_last_aim.p.x;
					my_current_aim.p.y=my_last_aim.p.y-1;
				}
				else
				{
					// assume horizontal ship
					my_current_aim.p.x=my_last_aim.p.x-1;
					my_current_aim.p.y=my_last_aim.p.y;
				}
			}
		}
		else if (my_aim_count>1) // if current aim is more than the second try
		{
			my_last_aim=my_aims[my_aim_count-1];
			my_last_but_aim=my_aims[my_aim_count-2]; // get my last but one aim
			if (my_last_but_aim.has_hit) // if last but one aim has hit
			{
				if (my_last_aim.has_hit) // if last aim has hit too
				{
					if (my_last_aim.p.x==my_last_but_aim.p.x) // if the two aims were in same column
						{
							my_current_aim.p.x=my_last_aim.p.x; // continue in the same column
							if (my_last_aim.p.y>my_last_but_aim.p.y) // if last aim was below last but one aim
							{
								if (my_last_aim.p.y!=COLS-1) // if not already at the last row
									my_current_aim.p.y=my_last_aim.p.y+1; // hit the next row
								else
									my_current_aim.p.y=rand()%ROWS;
							}
							else
							{
								if (my_last_aim.p.y!=0) // if not already at the first row
									my_current_aim.p.y=my_last_aim.p.y-1; // hit the previous row
								else
									my_current_aim.p.y=rand()%ROWS;
							}
						}
						else if (my_last_aim.p.y==my_last_but_aim.p.y) // if the two aims were in same row
						{
							my_current_aim.p.y=my_last_aim.p.y; // continue in same row
							if (my_last_aim.p.x>my_last_but_aim.p.x) // if last aim was right to last but one aim
							{
								if (my_last_aim.p.x!=COLS-1)
									my_current_aim.p.x=my_last_aim.p.x+1; // hit the next column
								else
									my_current_aim.p.x=rand()%COLS;
							}
							else
							{
								if (my_last_aim.p.x!=0)
									my_current_aim.p.x=my_last_aim.p.x-1;
								else
									my_current_aim.p.x=rand()%COLS;
							}
						}
					}
				else // if last aim has not hit but last but one aim has hit
				{
					if (my_last_aim.p.x==my_last_but_aim.p.x)
					{
						if (my_last_aim.p.x!=COLS-1)
						{
							my_current_aim.p.x=my_last_aim.p.x+1;
							my_current_aim.p.y=my_last_aim.p.y;
						}
						else
						{
							my_current_aim.p.x=my_last_aim.p.x-1;
							my_current_aim.p.y=my_last_aim.p.y;
						}
					}
					else if (my_last_aim.p.y==my_last_but_aim.p.y)
					{
						my_current_aim.p.x=my_last_aim.p.x;
						if (my_last_aim.p.y!=ROWS-1)
							my_current_aim.p.y=my_last_aim.p.y+1;
						else
							my_current_aim.p.y=my_last_aim.p.y-1;
					}
				}
			}
			else // last but one aim has not hit
			{
				// assume player's ship is vertically upwards
				if (my_last_aim.p.y!=0)
				{
					my_current_aim.p.x=my_last_aim.p.x;
					my_current_aim.p.y=my_last_aim.p.y-1;
				}
				else if (my_last_aim.p.x!=0)
				{
				// assume horizontal
				my_current_aim.p.x=my_last_aim.p.x-1;
				my_current_aim.p.y=my_last_aim.p.y;
				}
			}
		}

		cout << endl << "My aim is " << my_current_aim.p.x << "," << my_current_aim.p.y << endl;
		sea2.show();
		cout << endl << "Hit(1) or miss(0)?";
		cin >> your_response;

		if (your_response) // if you say yes
		{
			my_current_aim.has_hit=true; // this aim has hit
			i_hit_count++;
			int sank_type;
			cout << "Enter the type of ship I sank (0 for none):";
			cin >> sank_type;
			if (sank_type)
			{
				yours_sank_count++;
				my_current_aim.has_hit=false;
				if (yours_sank_count==5)
				{
					cout << "I win!" << endl;
					exit(0);
				}
			}
		}
		else
			my_current_aim.has_hit=false;
		
		if (my_aim_count>98)
			cout << "Phew! Too long a game! I quit!";
		else
			my_aims[my_aim_count++]=my_current_aim;
		} while (true);

	return 0;
}
