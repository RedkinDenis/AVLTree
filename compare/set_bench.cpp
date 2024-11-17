#include <iostream>
#include <set>
#include "benchmark.hpp"
#include <chrono>

void run (std::istream &inp = std::cin);

int main()
{
    using clock = std::chrono::high_resolution_clock;    
    auto time_start = clock::now();
    
    run();

    auto time_end = clock::now();
    auto time = std::chrono::duration<long double>(time_end - time_start).count();
    std::cout << time << "\n";

    return 0;
}

void run (std::istream &inp) {
        
    std::set<int> set;
    char command = 0;
    while (inp >> command) {
        int key, low, up;

        switch(command) {
            case 'k': 
                inp >> key;
                set.insert(key);
                break;
            
            case 'q': 
                inp >> low; inp >> up;
                break;
            
            default:
                std::cerr << "Error input, need command: \"k\" or \"q\"\n";
                exit(-1);
                break;
        }
    }
}