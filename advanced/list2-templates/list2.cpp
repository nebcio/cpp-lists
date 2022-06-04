#include <iostream>

// 5
template<typename T, typename T2>
auto add1(T& first, T2& second) {
    std::cout << "add1\n";
    return first + second;
}

template<>
inline auto add1(const char* &first, const char* &second) {
    std::cout << "add1 specialization (const char*)\n";
    size_t a = sizeof(first), b = sizeof(second);
    const size_t f = a / sizeof(char);
    const size_t s = b / sizeof(char);

    std::string out;
    for (size_t i = 0; i < f + s; i++) {
        if (i < f) out += first[i];
        else out += second[s - (f + s - i)];
    }

    return out;
}

template<typename T, typename T2>
auto add1(const T* const& first, const T2* const& second) {
    std::cout << "add1 specialization\n";
    return *first + *second;
}

// 6
template<typename T>
constexpr auto hiperszescian(const T a, const T n) {
    int out = 1;
    if (a > 0 && n > 0) {
        for (int i = 1; i <= n; i++) out *= a;
    }
    else out = -1;
    
    return out;
}

// 7
template<typename T, typename ...Args>
auto add(T first, Args ...args) {
    if constexpr (sizeof...(args) == 0) return first;
    else return first + add(args...);
}

int main() {
    int a = 1; float b = 2.1f;
    auto val = add1(a, b);
    std::cout << val << "\n";

    std::cout << "\nZadanie5a:\n";
    auto val2 = add1(&a, &b);
    std::cout << val2 << "\n";

    std::cout << "\nZadanie5b:\n";
    const char* sa = "As";
    const char* sb = "la";

    std::cout << add1(sa, sb) << "\n";

    std::cout << "\nZadanie6:\n";
    constexpr int obj = hiperszescian(3, 5);
    std::cout << "l = 3, n = 5: V = " << obj;

    std::cout << "\n\nZadanie7:\n";
    std::cout << "add(1, 3, 2, 2) = " << add(1, 3, 2, 2) << "\n";
    std::cout << "add(2, 2, 2, 2, 2) = " << add(2, 2, 2, 2, 2) << "\n";

    std::cin.get();
}