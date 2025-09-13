#define _CRT_SECURE_NO_WARNINGS  // MSVC: ��������� �������������� � �������������� ������� (strcpy, strcpy, strcat). ��� ������ ������������ ��� ����� ���� NOP, �� �������� � MSVC.
#include <iostream>
#include <cstring>  // ���������� ��� strlen, memcpy, memmove � �.�. (����������� ������� ��� ������ �� �������� � �������)
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimiter "\n-----------------------------------------\n"

class String
{
    int size;  // ������ ������ � ������ (� ������ NULL-Terminator)
    char* str; // ����� ������ � ������������ ������

public:
    int get_size() const
    {
        return size;
    }
    const char* get_str() const
    {
        return str;
    }
    char* get_str()
    {
        return str;
    }

    // Constructors:
    explicit String(int size = 80)
    {
        // ����������� �� ��������� ������� ������ ������ �������� 80 ����
        this->size = size;
        this->str = new char[size] {};
        cout << "DefaultConstructor:\t" << this << endl;
    }
    String(const char* str)
    {
        this->size = strlen(str) + 1; // strlen() ���������� ������ ������ � ��������, +1 ����� ����� ���������� ������ ��� NULL-Terminator
        this->str = new char[size] {};
        // ������ strcpy �� memcpy ��� ������������ � ��������� �������������� � deprecation (memcpy ���������� ��� ���������� �������)
        memcpy(this->str, str, this->size * sizeof(char));
        cout << "Constructor:\t\t" << this << endl;
    }

    // CopyConstructor, CopyAssignment: DeepCopy
    // CopyMethods, CopySemantic
    // Shallow copy - ������������� �����������
    String(const String& other)
    {
        // this->str = other.str; // Shallow copy
        /// ------------------------------------------------ ///
        // Deep copy:
        this->size = other.size;
        this->str = new char[size] {};
        // ������ strcpy �� memcpy
        memcpy(this->str, other.str, this->size * sizeof(char));
        cout << "CopyConstructor:\t" << this << endl;
    }
    String(String&& other)
    {
        // MoveConstructor - ShallowCopy:
        this->size = other.size;
        this->str = other.str;
        // �������� ����������� ������ ��� ���� ����� ������������� �������� ��� �������� ������������.
        other.size = 0;
        other.str = nullptr;
        cout << "MoveConstructor:\t" << this << endl;
    }
    ~String()
    {
        delete[] str;
        str = nullptr;
        size = 0;
        cout << "Destructor:\t\t" << this << endl;
        /*
        -----------------------------------
        ������ �� ����� ���������� 'Debug Assertion Failed'
        ��������� ����� �������� delete[] ����������� 2 ����
        �� ������ ������ ����, ��������� delete[] ��� �������
        ����� ����������� ������.
        -----------------------------------
        */
    }

    // Operators:
    String& operator=(const String& other)
    {
        // this->str = other.str; // Shallow copy - ������������� �����������
        /// ------------------------------------- ///
        // 0) ���������, �� �������� �� ��� ������ ���� ��������:
        if (this == &other) return *this;
        // 1) ������� ������ ������������ ������
        delete[] this->str;
        // Deep copy - �������� �����������:
        this->size = other.size;
        // 2) �������� ����� ������������ ������:
        this->str = new char[size] {};
        // ������ strcpy �� memcpy
        memcpy(this->str, other.str, this->size * sizeof(char));
        cout << "CopyAssignment:\t\t" << this << endl;
        return *this;
    }
    String& operator=(String&& other)
    {
        // 0) ��������, �� �������� �� 'this' � 'other' ����� � ��� �� ��������.
        if (this == &other) return *this;
        // 1) �������� ������ ������
        delete[] str;
        // 2) Shallow copy:
        this->size = other.size;
        this->str = other.str;
        // 3) �������� ����������� ������:
        other.size = 0;
        other.str = nullptr;
        cout << "MoveAssignment:\t\t" << this << endl;
        return *this;
    }
    char operator[](int i) const
    {
        return str[i]; // Index operator, Subscript operator
    }
    char& operator[](int i)
    {
        return str[i];
    }

    // Methods:
    void print() const
    {
        cout << "Size:\t" << size << endl;
        cout << "Str:\t" << str << endl;
    }
};

String operator+(const String& left, const String& right)
{
    String result(left.get_size() + right.get_size() - 1); // ������ ����������: left.size + right.size - 1 (�������� overlapping NULL)
    // �������� ����� ������ (������� � NULL)
    memcpy(result.get_str(), left.get_str(), left.get_size() * sizeof(char));  // ������ strcpy
    // ������������� ������ ������ (�������� NULL �� ����� ������) � ���������� memmove, ����� �������� overlap (memmove ���������� ��� ��������������� ��������)
    memmove(result.get_str() + left.get_size() - 1, right.get_str(), right.get_size() * sizeof(char));  // ������ ��� ������������
    return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
    return os << obj.get_str();
}

void Clear(char* str)
{
    delete[] str;
}

#define CONSTRUCTORS_CHECK
//#define CONSTRUCTORS_CHECK
//#define COPY_SEMANTIC_CHECK

int main() // �������� � void �� int (�������� C++)
{
    setlocale(LC_ALL, "");
    int a = 2;
    a = 3;

#ifdef CONSTRUCTORS_CHECK
    String str1;
    str1.print();
    String str2(5); // Conversion from 'int' to 'String'
    str2.print();
    String str3 = "Hello";
    str3.print();
    cout << str3 << endl;
    String str4_world = "World";  // �������� � 'str4' �� 'str4_world' ��� ��������� redefinition � ����������� ������� ����
    cout << str4_world << endl;  // �������������� �������� ���������
    cout << delimiter << endl;
    String str5;
    str5 = str3 + str4_world;  // ��������
    cout << delimiter << endl;
    cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK
    String str1_copy = "Hello";  // �������� � 'str1' �� 'str1_copy' ��� ��������� redefinition (���� ������������ ��� define)
    str1_copy = str1_copy;  // � �����
    cout << str1_copy << endl;  // � �����
    String str2_copy;  // �������� � 'str2' �� 'str2_copy'
    str2_copy = str1_copy;  // � �����
    cout << str2_copy << endl;  // � �����
    /*char* str = new char[8]{ "Hello" };
    cout << str << endl;
    Clear(str);
    Clear(str);*/
    // delete[] str;
        /*int arr[] = { 3,5,8,13,21 };
        delete[] arr;*/
#endif // COPY_SEMANTIC_CHECK

        // MoveMethods (MoveSemantic) � ������������� ���������� ��� ��������� redefinition
    String str11; // ���� str1 � �������������
    str11.print();
    String str21(5); // ���� str2 � �������������
    // Single-argument Constructor (int)
    str21.print();
    String str31 = "Hello"; // ���� str3 � �������������
    // Single-argument Constructor (const char str[])
    str31.print();
    // ������� String str4(); � ��� ���������� �������, ������������� � ���������� str4 �� CONSTRUCTORS_CHECK. ������ ��������� ���.
    // ���� ����� ������� ������ ������ �������, ����������� {}:
    String str51{}; // ���� str5 � �������������; ����� ����� DefaultConstructor()
    str51.print();
    String str6{ 6 }; // Single-argument Constructor (int)
    str6.print();
    String str7{ "World" };
    str7.print();
    String str8 = str7;
    str8.print();
    String str9(str8);
    str9.print();
    String str10{ str9 };
    str10.print();
    //!!! �������� ������ ��� ������ ������������� ������� ������������ � ������� ������������� !!!

    return 0; // ��������� ��� int main()
}