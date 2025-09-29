#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		//����������� �� ��������� - ������� ������ ������.
		Head = nullptr;		//���� ������ ����, �� ��� ������ ��������� �� 0.
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}

	//			Adding elements:
	void push_front(int Data)
	{
		//1) ������� ������� � ��������� � ���� ����������� ��������:
		Element* New = new Element(Data);

		//2) ����������� �����, ��������� ������� � ������ ������:
		New->pNext = Head;

		//3) ��������� ������ �� ����� ������� (���������� ����� ������� � ������):
		Head = New;
	}

	//					Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� ���������� �������� �������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Element element = 5;

	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}