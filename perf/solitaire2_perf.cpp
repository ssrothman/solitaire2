#include <chrono>
#include <iostream>

int main() {
    const auto start = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::steady_clock::now() - start;
    std::cout << "solitaire2 performance scaffold: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count()
              << " ns\n";
    return 0;
}
