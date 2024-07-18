#include <iostream>
#include <windows.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole(void) {
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }
    
    if(!GetConsoleMode(stdoutHandle, &outMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;
    
    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) {
        exit(GetLastError());
    }   
}

void restoreConsole(void) {
    // Reset colors
    printf("\x1b[0m");  
    
    // Reset console mode
    if(!SetConsoleMode(stdoutHandle, outModeInit)) {
        exit(GetLastError());
    }
}

int main() {
    int matrixSize = 10;
    int speed = 100; // Default speed in milliseconds
    int density = 50; // Default density percentage (0-100)

    setupConsole();
    srand(time(0)); // Seed for random number generation
    
    while (true) {
        std::cout << "Enter the matrix size (e.g., 10): ";
        std::cin >> matrixSize;
        
        if (matrixSize > 0) {
            std::cout << "Enter the delay time in milliseconds (e.g., 100 for 0.1 seconds): ";
            std::cin >> speed;
            
            std::cout << "Enter the density percentage (0-100): ";
            std::cin >> density;
            
            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    if (rand() % 100 < density) {
                        std::cout << "\033[1;32m1\033[0m ";
                    } else {
                        std::cout << "\033[1;32m0\033[0m ";
                    }
                }
                std::cout << std::endl;
                Sleep(speed); // Control the speed by introducing a delay
            }
            break;
        } else {
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        }
    }

    restoreConsole();
    return 0;
}
