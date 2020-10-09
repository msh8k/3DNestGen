//#include "stdafx.h"
//#include "xorshiro.h"
//
//#include <iostream>
//#include <chrono>
//
//
//int main()
//{
//	Xorshiro x;
//	    uint64_t boundary = std::numeric_limits<uint64_t>::max ( ) / 7;
//	    std::cout << "Longest possible uint64_t / 7: " << boundary << std::endl;
//	    std::cout << "First random: " << x.next ( ) << std::endl << "Second random: " << x.next ( ) << std::endl;
//	    for (int j = 0; j < 20; ++j) {
//	        auto start = std::chrono::high_resolution_clock::now();
//	        for (int i = 0; i < 1000000; ++i) {
//	            x.next();
//	        };
//	        auto finish = std::chrono::high_resolution_clock::now();
//	
//	        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
//	        std::cout << microseconds.count() << " µs\n";
//	        if (microseconds > std::chrono::seconds(1))
//	            break;
//	    }
//
//    return 0;
//}
