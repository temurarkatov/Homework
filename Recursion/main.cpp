#include<iostream>
using namespace std;

void elevator(int floor);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Ââåäèòå íîìåð ýòàæà: "; cin >> n;
	elevator(n);
	//cout << "Recusion";
	//main();
}
void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Âû â ïîäâàëå" << endl;
		return;
	}
	cout << "Âû íà " << floor << " ýòàæå" << endl;
	elevator(floor - 1);
	cout << "Âû íà " << floor << " ýòàæå" << endl;
}