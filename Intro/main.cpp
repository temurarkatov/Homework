#include<iostream>
using namespace std;

class Point
{
	//—оздава€ структуру или класс мы создаем новый тип данных (пользовательский тип данных)
	//ѕользовательские типы €вл€ютс€ более сложными, поскольку могу включать в себ€ множество
	//однотипных или разнотипных значений, которые €вл€ютс€ характеристиками и состо€ни€ми объектов
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
		//l-value = r-value;
	}
	void set_y(double y)
	{
		this->y = y;
	}
};

//#define STRUCT_POINT

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	int a;		//ќбъ€вление переменной 'a' типа 'int';
	Point A;	//ќбъ€вление переменной 'A' типа 'Point';
	//—оздание объекта 'A' структуры 'Point';
	//—оздание экземпл€ра 'A' структуры 'Point';
	//'A' is instance of struct 'Point'
	//Instantiate - создать объект.
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;

}