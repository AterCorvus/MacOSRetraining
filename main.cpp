#include <iostream>

int main() {
    std::cout << "Service is running, enter A to stop\n";
    char ch;
    while(true) {
        ch  = getchar();
        if (ch == 'A') break;
    }
}