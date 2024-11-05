#include <iostream>
#include <set>
#include "ANSI_colors.hpp"
#include "benchmark.hpp"

int main()
{
    using clock = std::chrono::high_resolution_clock;
    std::set<int> set;
    
    auto time_start = clock::now().time_since_epoch().count();
    char command;
    while(std::cin >> command) {
        int lower, upper, answer;
        switch (command) {
            case 'k':
                std::cin >> lower;
                set.insert(lower);
                break;

            case 'q':
                std::cin >> lower >> upper;
                if (lower < upper)
                    answer = distance(set.lower_bound(lower), set.upper_bound(upper));
                NO_OPT(answer);
                break;
        }
    }
    auto time_end = clock::now().time_since_epoch().count();
    long double time = (static_cast<long double>(time_end - time_start)) * NSEC_TO_SEC;
    std::cout << time << "\n";

    return 0;
}