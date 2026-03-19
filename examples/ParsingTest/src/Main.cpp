#include <iostream>
#include <AnimateAtlas/Core/Experimental/TestParse.h>

int main(int argc, char* argv[]) {

    // Clear screen
    std::cout << "\033[2J\033[1;1H"; 

    std::cout << "========================================" << std::endl;
    std::cout << "Animate Atlas Parse Test" << std::endl;
    std::cout << "========================================" << std::endl;

    if (argc >= 2) {
        //std::cout << argv[1] << std::endl;
    }
    else {
        std::cout << "No file provided for parsing." << std::endl;
        return 0;
    }

    //animData.testParse(argv[1]);
    AnimateAtlas::Core::Experimental::testParse(argv[1]);

    return 0;
}