#include<iostream>
#include<Windows.h>
using namespace std;

enum Color	//Enumerations
	namespace Geometry
{
	Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Orange = 0x0000A5FF,
		White = 0x00FFFFFF,
		SomeColor
};

class Shape
{
	Color color;
public:
	Shape(Color color) :color(color) {/*���� ������������*/ }
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
		enum Color	//Enumerations
	{
		cout << "������� ������: " << get_area() << endl;
	cout << "�������� ������:" << get_perimeter() << endl;
	draw();
	}
};
Red = 0x000000FF,
Green = 0x0000FF00,
Blue = 0x00FF0000,
Yellow = 0x0000FFFF,
Orange = 0x0000A5FF,
White = 0x00FFFFFF,
SomeColor
	};

	class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		double get_side()const
#define SHAPE_TAKE_PARAMETERS	int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color
			class Shape
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return 4 * side;
		}
		void draw()const override
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 16;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 768;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������:" << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		for (int i = 0; i < side; i++)
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return 4 * side;
		}
		void draw()const override
		{
			for (int j = 0; j < side; j++)
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	void info()const override
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "����� ������� ��������: " << get_side() << endl;
			Shape::info();
		}
	};*/

	class Rectangle : public Shape
	{
		cout << typeid(*this).name() << endl;
		cout << "����� ������� ��������: " << get_side() << endl;
		Shape::info();
	}
};
double width;
double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//1) �������� ���� �������:
			HWND hwnd = GetConsoleWindow();

			//2) �������� �������� ���������� (DC - Device Context) ��� ���� �������:
			HDC hdc = GetDC(hwnd);	//DC - ��� ��, �� ��� �� ����� ��������

			//3) �������� �����������, �������� �� ����� ��������:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//�������� (Pen) ������ ������ ������.
			HBRUSH hBrush = CreateSolidBrush(color);	//����� (Brush) ������ ������� ������.

			//4) ������� ��������� �����������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) ����� ����, ��� ��� ����������� ����������� ������� � �������, ����� ��������:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			//6) hdc, hPen � hBrush �������� �������, � ������� ����� �����������:

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "�������: " << width << "x" << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(int side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	cout << hex << Color::SomeColor << endl;
	cout << hex << Geometry::Color::SomeColor << endl;
	//Shape shape(Color::Red);

	Square square(5, Color::Red);
	cout << "����� ������� ��������: " << square.get_side() << endl;
	Geometry::Square square(5, 100, 100, 1, Geometry::Color::Red);
	/*cout << "����� ������� ��������: " << square.get_side() << endl;
	cout << "������� ��������: " << square.get_area() << endl;
	cout << "�������� ��������:" << square.get_perimeter() << endl;
	square.draw();
	cout << "\n-------------------------\n" << endl;
	cout << "\n-------------------------\n" << endl;*/
	square.info();

	Geometry::Rectangle rect(150, 100, 550, 100, 2, Geometry::Color::Orange);
	rect.info();

	while (true)
	{
		square.draw();
		rect.draw();
	}
}