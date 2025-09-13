#define _CRT_SECURE_NO_WARNINGS  // MSVC: Отключает предупреждения о небезопасности функций (strcpy, strcpy, strcat). Для других компиляторов это может быть NOP, но помогает в MSVC.
#include <iostream>
#include <cstring>  // Необходимо для strlen, memcpy, memmove и т.д. (стандартные функции для работы со строками и памятью)
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define delimiter "\n-----------------------------------------\n"

class String
{
    int size;  // размер строки в Байтах (с учетом NULL-Terminator)
    char* str; // адрес строки в динамической памяти

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
        // Конструктор по умолчанию создает пустую строку размером 80 Байт
        this->size = size;
        this->str = new char[size] {};
        cout << "DefaultConstructor:\t" << this << endl;
    }
    String(const char* str)
    {
        this->size = strlen(str) + 1; // strlen() возвращает размер строки в символах, +1 нужен чтобы выделилась память под NULL-Terminator
        this->str = new char[size] {};
        // Замена strcpy на memcpy для безопасности и избежания предупреждений о deprecation (memcpy безопаснее для известного размера)
        memcpy(this->str, str, this->size * sizeof(char));
        cout << "Constructor:\t\t" << this << endl;
    }

    // CopyConstructor, CopyAssignment: DeepCopy
    // CopyMethods, CopySemantic
    // Shallow copy - поверхностное копирование
    String(const String& other)
    {
        // this->str = other.str; // Shallow copy
        /// ------------------------------------------------ ///
        // Deep copy:
        this->size = other.size;
        this->str = new char[size] {};
        // Замена strcpy на memcpy
        memcpy(this->str, other.str, this->size * sizeof(char));
        cout << "CopyConstructor:\t" << this << endl;
    }
    String(String&& other)
    {
        // MoveConstructor - ShallowCopy:
        this->size = other.size;
        this->str = other.str;
        // Обнуляем принимаемый объект для того чтобы предотвратить удаление его ресурсов деструктором.
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
        Ошибка на этапе выполнения 'Debug Assertion Failed'
        возникает когда оператор delete[] выполняется 2 раза
        по одному адресу либо, оператору delete[] был передан
        адрес статической памяти.
        -----------------------------------
        */
    }

    // Operators:
    String& operator=(const String& other)
    {
        // this->str = other.str; // Shallow copy - Поверхностное копирование
        /// ------------------------------------- ///
        // 0) Проверяем, не является ли тот объект этим объектом:
        if (this == &other) return *this;
        // 1) Удаляем старую динамическую память
        delete[] this->str;
        // Deep copy - Глубокое копирование:
        this->size = other.size;
        // 2) Выделяем новую динамическую память:
        this->str = new char[size] {};
        // Замена strcpy на memcpy
        memcpy(this->str, other.str, this->size * sizeof(char));
        cout << "CopyAssignment:\t\t" << this << endl;
        return *this;
    }
    String& operator=(String&& other)
    {
        // 0) Проверка, не являются ли 'this' и 'other' одним и тем же объектом.
        if (this == &other) return *this;
        // 1) Удаление старой памяти
        delete[] str;
        // 2) Shallow copy:
        this->size = other.size;
        this->str = other.str;
        // 3) Обнуляем принимаемый объект:
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
    String result(left.get_size() + right.get_size() - 1); // Размер результата: left.size + right.size - 1 (учитывая overlapping NULL)
    // Копируем левую строку (включая её NULL)
    memcpy(result.get_str(), left.get_str(), left.get_size() * sizeof(char));  // Замена strcpy
    // Конкатенируем правую строку (заменяет NULL от левой строки) — используем memmove, чтобы избежать overlap (memmove безопаснее для перекрывающихся областей)
    memmove(result.get_str() + left.get_size() - 1, right.get_str(), right.get_size() * sizeof(char));  // Замена для конкатенации
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

int main() // Изменено с void на int (стандарт C++)
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
    String str4_world = "World";  // Изменено с 'str4' на 'str4_world' для избежания redefinition с декларацией функции ниже
    cout << str4_world << endl;  // Соответственно изменены обращения
    cout << delimiter << endl;
    String str5;
    str5 = str3 + str4_world;  // Изменено
    cout << delimiter << endl;
    cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef COPY_SEMANTIC_CHECK
    String str1_copy = "Hello";  // Изменено с 'str1' на 'str1_copy' для избежания redefinition (если активировать оба define)
    str1_copy = str1_copy;  // И здесь
    cout << str1_copy << endl;  // И здесь
    String str2_copy;  // Изменено с 'str2' на 'str2_copy'
    str2_copy = str1_copy;  // И здесь
    cout << str2_copy << endl;  // И здесь
    /*char* str = new char[8]{ "Hello" };
    cout << str << endl;
    Clear(str);
    Clear(str);*/
    // delete[] str;
        /*int arr[] = { 3,5,8,13,21 };
        delete[] arr;*/
#endif // COPY_SEMANTIC_CHECK

        // MoveMethods (MoveSemantic) — переименованы переменные для избежания redefinition
    String str11; // Было str1 — переименовано
    str11.print();
    String str21(5); // Было str2 — переименовано
    // Single-argument Constructor (int)
    str21.print();
    String str31 = "Hello"; // Было str3 — переименовано
    // Single-argument Constructor (const char str[])
    str31.print();
    // Удалена String str4(); — это декларация функции, конфликтующая с переменной str4 из CONSTRUCTORS_CHECK. Теперь конфликта нет.
    // Если нужно создать объект вместо функции, используйте {}:
    String str51{}; // Было str5 — переименовано; явный вызов DefaultConstructor()
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
    //!!! Фигурные скобки для вызова конструкторов следует использовать с большой осторожностью !!!

    return 0; // Добавлено для int main()
}