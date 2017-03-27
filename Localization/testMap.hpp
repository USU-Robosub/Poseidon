#include<utility>
#include<random>
#include<iostream>
#include<cstdlib>
#include<ctime>

struct object
{
	enum type{SPHERE,BOX,FLYING_SQUIRREL,YOUR_MOM};
	double _x;
	double _y;
	type _object_type;
	object(double x, double y, type theType)
	{
		_x=x;
		_y=y;
		_object_type=theType;
	}

};

class testMap
{
	private:
		int _LEFT;
		int _RIGHT;
		int _TOP;
		int _BOTTOM;
		double _MAX_GRADIENT;
		int _OBJ_NUMBER;
	public:
		std::pair<double,double> _currPosition; 
		void setLocation(double,double);
		testMap(double l=-100,double r=100,double t=100,double b=-100,double x=0,double y=0,double max_g=2.5,int obj_type=10); 
		std::pair<double,double>random_advance();
		std::pair<double,double>custome_advance(double,double);
		std::vector<object> objectList;
};
testMap::testMap(double l,double r,double t,double b, double x, double y,double max_g,int obj_number)
{
	_RIGHT=r;
	_LEFT=l;
	_TOP=t;
	_BOTTOM=b;
	_currPosition.first=x;
	_currPosition.second=y; 
	_MAX_GRADIENT=max_g;
	_OBJ_NUMBER=obj_number;
	const int NUM_OF_ENUMS=4;
	std::srand(time(0));
	for(int i=0; i<_OBJ_NUMBER; i++)
	{ 
		double location_y=static_cast<double>(rand())/((static_cast<double>(RAND_MAX/(_TOP-_BOTTOM))))+_LEFT;
		double location_x=static_cast<double>(rand())/((static_cast<double>(RAND_MAX/(_RIGHT-_BOTTOM))))+_BOTTOM;
		object::type temp_type=static_cast<object::type>(rand()%NUM_OF_ENUMS);
		objectList.push_back(object(location_x,location_y,temp_type)); 
	}
}
std::pair<double,double>testMap::custome_advance(double x, double y)
{
	_currPosition.first=x;
	_currPosition.second=y;

	_currPosition.first=(_currPosition.first>_TOP?(_BOTTOM+_currPosition.first-_TOP):_currPosition.first);
	_currPosition.first=(_currPosition.first<_BOTTOM?(_TOP+(_currPosition.first-_BOTTOM)):_currPosition.first); 
	_currPosition.second=(_currPosition.second>_RIGHT?(_LEFT+_currPosition.second-_RIGHT):_currPosition.second);
	_currPosition.second=(_currPosition.second<_LEFT?(_RIGHT+(_currPosition.second-_LEFT)):_currPosition.second);

	return _currPosition;
}
std::pair<double,double>testMap::random_advance()
{

	double gradient_y=static_cast<double>(rand())/((static_cast<double>(RAND_MAX/(_MAX_GRADIENT*2))))-_MAX_GRADIENT;
	double gradient_x=static_cast<double>(rand())/((static_cast<double>(RAND_MAX/(_MAX_GRADIENT*2))))-_MAX_GRADIENT;
	//	std::cout<<"gradient x: "<<gradient_x<<" gradient y: "<<gradient_y<<std::endl;
	_currPosition.first+=gradient_x;
	_currPosition.second+=gradient_y;
	_currPosition.first=(_currPosition.first>_TOP?_BOTTOM:_currPosition.first);
	_currPosition.first=(_currPosition.first<_BOTTOM?_TOP:_currPosition.first); 
	_currPosition.second=(_currPosition.second>_RIGHT?_LEFT:_currPosition.second);
	_currPosition.second=(_currPosition.second<_LEFT?_RIGHT:_currPosition.second);
	return _currPosition;
}
