#define _CRT_SECURE_NO_WARNINGS  // ��� MSVC: ��������� �������������� � ������������ ��������
#include <iostream>
#include <ctime>  // ������������ <ctime> ��� �������������
#include <initializer_list>  // ��������� ��� std::initializer_list
using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------------------------\n"

class ForwardList;  // Forward declaration

class Element
{
    int Data;         // �������� ��������
    Element* pNext;   // ����� ���������� ��������
    static int count;

public:
    Element(int Data, Element* pNext = nullptr)
    {
        this->Data = Data;
        this->pNext = pNext;
        count++;
#ifdef DEBUG
        cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
    }
    ~Element()
    {
        count--;
#ifdef DEBUG
        cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
    }
    friend class Iterator;
    friend class ForwardList;
    friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;

class Iterator
{
    Element* Temp;

public:
    Iterator(Element* Temp = nullptr) : Temp(Temp)
    {
        cout << "ItConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        cout << "ItDestructor:\t" << this << endl;
    }
    Iterator& operator++()
    {
        Temp = Temp->pNext;
        return *this;
    }
    bool operator==(const Iterator& other) const
    {
        return this->Temp == other.Temp;
    }
    bool operator!=(const Iterator& other) const
    {
        return this->Temp != other.Temp;
    }
    int operator*() const
    {
        return Temp->Data;
    }
    int& operator*()
    {
        return Temp->Data;
    }
};

class ForwardList
{
protected:  // �������� � private �� protected ��� ������� � friends/derived
    Element* Head;
    size_t size;

public:
    Element* get_Head() const
    {
        return Head;
    }
    size_t get_size() const
    {
        return size;
    }
    Iterator begin()
    {
        return Iterator(Head);  // ���������� ��� ����������� ���� ��������
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    ForwardList()
    {
        // ����������� �� ��������� - ������� ������ ������.
        Head = nullptr;  // ���� ������ ����, �� ��� ������ ��������� �� 0.
        size = 0;
        cout << "FLConstructor:\t" << this << endl;
    }
    explicit ForwardList(int size) : ForwardList()  // ����������: ������ ������������� ForwardList(), explicit moved to declaration
    {
        while (size--) push_front(0);
        cout << "FLSizeConstructor:\t" << this << endl;
    }
    ForwardList(const std::initializer_list<int>& il) : ForwardList()
    {
        // initializer_list - ��� ���������.
        // ��������� - ��� ������, ������� ���������� �������� ������ �������� � ������.
        // ���������� ��� ������� ���������� � ������� �� ����������� ������ ��� �������� ��������.
        // � ������ ���������� ���� ����� begin(), ������� ���������� �������� �� ������ ����������,
        // � ����� end(), ������� ���������� �������� �� ����� ����������.
        cout << typeid(il.begin()).name() << endl;
        for (int const* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }
        cout << "FLitConstructor:\t" << this << endl;
    }
    ForwardList(const ForwardList& other) : ForwardList()
    {
        // Deep copy (��������� �����������):
        *this = other;
        cout << "FLCopyConstructor:\t" << this << endl;
    }
    ForwardList(ForwardList&& other) : ForwardList()
    {
        *this = std::move(other);
        cout << "FLMoveConstructor:\t" << this << endl;
    }
    ~ForwardList()
    {
        clock_t t_start = clock();
        while (Head) pop_front();
        clock_t t_end = clock();
        cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
    }

    // Operators:
    ForwardList& operator=(const ForwardList& other)
    {
        if (this == &other) return *this;  // 0) ���������, �� �������� �� 'this' � 'other' ����� ��������.
        while (Head) pop_front();  // 1) ������ �������� ������� ��������� �� ������
        // 2) Deep copy (��������� �����������):
        for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
            push_front(Temp->Data);
        // push_back(Temp->Data);
        reverse();  // ����������: �������� () ��� ������
        cout << "FLCopyAssignment:\t" << this << endl;
        return *this;
    }
    ForwardList& operator=(ForwardList&& other)
    {
        if (this == &other) return *this;
        while (Head) pop_front();
        this->Head = other.Head;
        this->size = other.size;
        other.Head = nullptr;
        other.size = 0;
        cout << "FLMoveAssignment:\t" << this << endl;
        return *this;
    }
    int operator[](int index) const
    {
        Element* Temp = Head;
        for (int i = 0; i < index; i++) Temp = Temp->pNext;
        return Temp->Data;
    }
    int& operator[](int index)
    {
        Element* Temp = Head;
        for (int i = 0; i < index; i++) Temp = Temp->pNext;
        return Temp->Data;
    }

    // Adding elements:
    void push_front(int Data)
    {
        // 1) ������� ������� � ��������� � ���� ����������� ��������:
        // Element* New = new Element(Data);
        // 2) ����������� �����, ��������� ������� � ������ ������:
        // New->pNext = Head;
        // 3) ��������� ������ �� ����� ������� (���������� ����� ������� � ������):
        // Head = New;
        Head = new Element(Data, Head);
        size++;
    }
    void push_back(int Data)
    {
        if (Head == nullptr) return push_front(Data);
        Element* Temp = Head;
        while (Temp->pNext) Temp = Temp->pNext;
        Temp->pNext = new Element(Data);
        size++;
    }
    void insert(int Data, int Index)
    {
        if (Index == 0) return push_front(Data);
        if (Index >= size) return push_back(Data);
        // 1) ������� �� ������� �������� (������� ����� �����������)
        Element* Temp = Head;
        for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
        // 2) ������� ����������� �������:
        // Element* New = new Element(Data);
        // 3) �������������� ����� ������� � ��� ���������� ��������:
        // New->pNext = Temp->pNext;
        // 4) �������������� ���������� ������� � ������:
        // Temp->pNext = New;
        Temp->pNext = new Element(Data, Temp->pNext);
        size++;
    }

    // Removing elements:
    void pop_front()
    {
        // 1) ���������� ����� ���������� ��������:
        Element* Erased = Head;
        // 2) ��������� ��������� ������� �� ������:
        Head = Head->pNext;
        // 3) ������� ��������� ������� �� ������:
        delete Erased;
        size--;
    }
    void pop_back()
    {
        if (Head == nullptr || Head->pNext == nullptr) return pop_front();  // ����������: ��������� == nullptr
        Element* Temp = Head;
        while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;
        delete Temp->pNext;
        Temp->pNext = nullptr;
        size--;
    }

    // Methods:
    void reverse()  // ����������: ������ ������ �����
    {
        ForwardList reverse_list;  // �������� ��� ��������� ���������� � ������
        while (Head)  // ���� ������ �������� ��������
        {
            reverse_list.push_front(Head->Data);  // ��������� �������� ������� � ��������� ������
            pop_front();  // � ������� ��������� ������� ������
        }
        // ��������� ��� ������ ���������:
        /*Head = reverse_list.Head;
        size = reverse_list.size; */
        *this = std::move(reverse_list);  // ��� ���������� �������, ������� ����� ������� �������� MoveAssignment, ���� �� ����, � ��������� ������ behavior is undefined.
        reverse_list.Head = nullptr;  // ��������� ��������� ������ �������� ��������� ����������, ��� ���� ����� ������ ����������, ������� ��������� ��� �������, � �� ��������� �� �� �� ������, �� ������� ��������� ��� �������� ������, ������������� ���������� ������ � ��� �������� ������.
    }

    void print() const
    {
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
        cout << "���������� ��������� ������: " << size << endl;
        cout << "����� ���������� ���������: " << Element::count << endl;
    }

    friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
    ForwardList fusion;
    for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
        fusion.push_back(Temp->Data);  // �������� �� push_back ��� ����������� �������
    for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
        fusion.push_back(Temp->Data);  // �������� ��� ������� ����� �����
    return fusion;
}

void Print(int arr[])
{
    cout << typeid(arr).name() << endl;
    cout << sizeof(arr) / sizeof(arr[0]) << endl;
    /*
    for (int i : arr)
    {
        cout << i << tab;
    }
    cout << endl;
    */
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
#define MOVE_SEMANTIC_CHECK  // ������ ��������
//#define RANGE_BASED_FOR_ARRAY

int main()  // �������� � void �� int ��� ��������� C++
{
    setlocale(LC_ALL, "");

#ifdef BASE_CHECK
    int n;
    cout << "������� ������ ������: "; cin >> n;
    ForwardList list;
    for (int i = 0; i < n; i++)
    {
        list.push_back(rand() % 100);
        // list.push_front(rand() % 100);
    }
    // list.push_back(123);
    list.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
    ForwardList list1;
    list1.push_back(0);
    list1.push_back(1);
    list1.push_back(1);
    list1.push_back(2);
    // list1.print();
    for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab; cout << endl;
    ForwardList list2;
    list2.push_back(3);
    list2.push_back(5);
    list2.push_back(8);
    list2.push_back(13);
    list2.push_back(21);
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);
    // list2.print();
    for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab; cout << endl;
    int a = 2;
    int b = 3;
    int c = a + b;
    // ForwardList fusion = list1 + list2; // CopyConstructor
    ForwardList list3;
    cout << delimiter << endl;
    list3 = list1 + list2; // CopyAssignment
    cout << delimiter << endl;
    // list3.print();
    for (int i = 0; i < list3.get_size(); i++) cout << list3[i] << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK
    int n;
    cout << "������� ������ ������: "; cin >> n;
    ForwardList list;
    clock_t t_start = clock();
    for (int i = 0; i < n; i++)
    {
        // list.push_back(rand() % 100);
        list.push_front(rand() % 100);
    }
    clock_t t_end = clock();
    cout << "ForwardList filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
#endif // PERFORMANCE_CHECK

#ifdef SUBSCRIPT_OPERATOR_CHECK
    int n;
    cout << "������� ������ ������: "; cin >> n;
    clock_t start;
    clock_t end;
    ForwardList list(n);
    start = clock();
    for (int i = 0; i < list.get_size(); i++)
        list[i] = rand() % 100;
    end = clock();
    cout << "������ �������� �� " << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
    for (int i = 0; i < list.get_size(); i++)
        cout << list[i] << tab;
    cout << endl;
#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
    int n;
    cout << "������� ������ ������: "; cin >> n;
    clock_t t_start, t_end;
    ForwardList list1;
    t_start = clock();
    for (int i = 0; i < n; i++)
        list1.push_front(rand() % 100);
    t_end = clock();
    cout << "������ �������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
    t_start = clock();
    ForwardList list2 = list1;
    t_end = clock();
    cout << "����������� ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������" << endl;
    // for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab; cout << endl;
    // for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab; cout << endl;
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
    clock_t t_start, t_end;
    ForwardList list1;
    ForwardList list2;
    t_start = clock();
    for (int i = 0; i < 3000000; i++) list1.push_front(rand());
    for (int i = 0; i < 3000000; i++) list2.push_front(rand());
    t_end = clock();
    cout << "Lists filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
    system("PAUSE");
    t_start = clock();
    ForwardList list3 = list1 + list2;
    t_end = clock();
    cout << "Lists concatenated for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
    system("PAUSE");
    t_start = clock();
    ForwardList list4 = list3;
    t_end = clock();
    cout << "Lists copied for " << double(t_end - t_start) / CLOCKS_PER_SEC << " seconds" << endl;
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
    int arr[] = { 3, 5, 8, 13, 21 };
    cout << sizeof(arr) << endl;
    cout << sizeof(arr[0]) << endl;
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout << arr[i] << tab;
    }
    cout << endl;
    // Range-based for - for ��� ���������. ��� ���������� ���������� ��������� (�����-�� ����� ���������)
    // https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
    for (int i : arr)
    {
        cout << i << tab;
    }
    cout << endl;
    cout << typeid(arr).name() << endl;
    Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

    ForwardList list = { 3, 5, 8, 13, 21 };  // ������������ �������� � �������� ������� ����� ������� ������ ������� ������ ������ 'initializer_list';
    list.print();
    for (int i : list) cout << i << tab; cout << endl;  // ������ �������� � Iterator

    return 0;  // ���������
}