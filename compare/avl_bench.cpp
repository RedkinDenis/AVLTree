#include <iostream>
#include "tree.hpp"
#include "benchmark.hpp"
#include <chrono>
#include <sstream>

int main()
{
    using clock = std::chrono::high_resolution_clock;
    
    std::stringstream st;
    auto time_start = clock::now();

    run<int>(std::cin, st);

    auto time_end = clock::now();
    auto time = std::chrono::duration<long double>(time_end - time_start).count();
    std::cout << time << "\n";

    return 0;
}
