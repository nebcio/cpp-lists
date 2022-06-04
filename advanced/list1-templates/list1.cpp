#include <iostream>
#include <vector>
#include "wektor.h"

// 1
template<typename T, typename T2>
auto add1(T& first, T2& second) {
    return first + second;
}

// 2
template<typename T, typename T2, typename Op>
auto add2(T& first, T2& second, Op operation) {
    return operation(first, second);
}


int main()
{
    // 1
    int a = 10, b = 4;
    float c = 5.3f, d = 2.1f;
    std::string s1 = "kot", s2 = "pies";

    std::cout << "Zadanie 1:\n\nadd1(int, int): ";
    std::cout << add1(a, b);

    std::cout << "\nadd1(float, float): ";
    std::cout << add1(c, d);

    std::cout << "\nadd1(float, int): ";
    std::cout << add1(c, a);

    std::cout << "\nadd1(int, float): ";
    std::cout << add1(a, c);

    std::cout << "\nadd1(string, string): ";
    std::cout << add1(s1, s2);

    // 2
    std::cout << "\n\nZadanie 2:\n\nadd2(int, int, f): ";
    std::cout << add2(a, b, [](int a, int b) { return a + b; });

    std::cout << "\nadd2(float, float, f): ";
    std::cout << add2(c, d, [](float a, float b) { return a + b; });

    std::cout << "\nadd2(float, int, f): ";
    std::cout << add2(c, a, [](float a, int b) { return a + b; });

    std::cout << "\nadd2(int, float, f): ";
    std::cout << add2(a, c, [](int a, float b) { return a + b; });

    std::cout << "\nadd2(string, string, f): ";
    std::cout << add2(s1, s2, [](std::string a, std::string b) { return a + b; });

    // 3
    std::cout << "\n\nZadanie 3:\n\n";
    wektor<double, 3, 4.0> da;
    da[2] = 2.1; da[1] += 4; da[0] *= 2;

    wektor<int, 3> ia;
    ia[2] = 3; ia[0] = 1;

    std::vector<int> v = { 1, 2, 3 };
    std::vector<double> vd = { 1.0, 2.1, 3.0 };

    std::cout << "Wektory:\nia: " << ia << "\n";
    std::cout << "da: " << da << "\n";

    // 4
    std::cout << "\nZadanie 4:\n\nia * v: " << (ia * v) << std::endl;
    std::cout << "da * v: " << (da * v) << std::endl;
    std::cout << "ia * vd: " << (ia * vd) << std::endl;


    std::cin.get();
}