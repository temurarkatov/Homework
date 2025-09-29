#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)
		void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				//Äëÿ òîãî ÷òîáû äåðåâî áàëàíñèðîâàëîñü ïðè óäàëåíèè ýëåìåíòîâ,
				//ïåðåä óäàëåíèåì åãî íóæíî âçâåñèòü:
				if (count(Root->pLeft) > count(Root->pRight))
				{
					//è åñëè ëåâàÿ âåòêà òÿæåëåå ÷åì ïðàâàÿ, òî áåðåì èç íåå ìàêñèìàëüíîå çíà÷åíèå,
					//ïîòîìó ÷òî îíî áëèæå âñåãî ê óäàëÿåìîìó çíà÷åíèþ:
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					//â ïðîòèâíîì ñëó÷àå áåðåì ìèíèìàëüíîå çíà÷åíèå èç ïðàâîé âåòêè,
					//ïîòîìó ÷òî îíî áëèæå âñåãî ê óäàâëÿåìîìó çíà÷åíèþ:
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)
		int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root)
		int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}


	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Ââåäèòå êîëè÷åñòâî ýëåìåíòîâ: "; cin >> n;
	Tree tree;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue() << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
		tree.insert(rand() % 100);
	}
	tree.print(tree.getRoot());
	tree.print();
	cout << endl;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: " << tree.count(tree.getRoot()) << endl;
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.minValue() << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << tree.maxValue() << endl;
	cout << "Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: " << tree.count() << endl;
	cout << "Ñóììà ýëåìåíòîâ äåðåâà: " << tree.sum() << endl;
	cout << "Ñðåäíåå-àðèôìåòè÷åñêîå ýëåìåíòîâ äåðåâà: " << tree.avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "Ìèíèìàëüíîå çíà÷åíèå â äåðåâå: " << u_tree.minValue() << endl;
	cout << "Ìàêñèìàëüíîå çíà÷åíèå â äåðåâå: " << u_tree.maxValue() << endl;
	cout << "Êîëè÷åñòâî ýëåìåíòîâ äåðåâà: " << u_tree.count() << endl;
	cout << "Ñóììà ýëåìåíòîâ äåðåâà: " << u_tree.sum() << endl;
	cout << "Ñðåäíåå-àðèôìåòè÷åñêîå ýëåìåíòîâ äåðåâà: " << u_tree.avg() << endl;
#endif // BASE_CHECK

	Tree tree =
	{
					50,

			25,				75,

		16,		32,		58,		85
	};
	tree.print();

	int value;
	//cout << "Ââåäèòå óäàëÿåìîå çíà÷åíèå: "; cin >> value;
	tree.erase(25);
	tree.erase(32);
	tree.erase(50);
	tree.erase(75);
	tree.print();

}