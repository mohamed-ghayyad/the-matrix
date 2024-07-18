#include<iostream>
#include<windows.h>
#include<limits>

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
int main(){
    int matrixSize = 10;
    setupConsole();
    while(true){
        std::cout << "Enter The matrix(10000): ";
        std::cin >> matrixSize;
        if(matrixSize > 0){
            for(int i = 0; i < matrixSize; i++){
                for(int j = 0; j < matrixSize; j++){
                    if(i%2 == j%2){
                        std::cout << "\033[1;32m1\033[0m ";
                    }else if(i%3 == j%5){
                        std::cout << "\033[1;32m1\033[0m ";
                    }else{
                        std::cout << "\033[1;32m0\033[0m ";
                    }
                }
                std::cout << std::endl;
            }
            break;
        }else{
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        }
    }
    restoreConsole();
    return 0;
}
