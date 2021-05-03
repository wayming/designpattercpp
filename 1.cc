#include <iostream>
#include <chrono>
 
int main()
{
    std::cout << std::boolalpha;
 
    std::chrono::years y {2020};
    std::cout << (++y == std::chrono::years(2021)) << ' ';
    std::cout << (--y == std::chrono::years(2020)) << '\n';
 
    // using namespace std::literals::chrono_literals;
    // y = std::chrono::years(32767);
    // y++;
    std::cout << (int)y << '\n';
}
