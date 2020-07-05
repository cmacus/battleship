// Point.h
// defines the point structure

class Point 
{
public:
	int x;
	int y;
	int belongsTo;

	Point():x(0),y(0),belongsTo(0)
	{}
	Point(int a,int b):x(a),y(b),belongsTo(0)
	{}
};