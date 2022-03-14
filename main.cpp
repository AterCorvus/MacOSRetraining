#include <iostream>
#include <memory>
#include <string>

#include "Product.pb.h"

using namespace std;

const string version = "0.0.1";

int main() {
    product_info::Product product;
    product.set_version(version);
    cout << "Service is running, enter A to stop\n";
    char ch;
    while(true) {
        ch  = getchar();
        if (ch == 'A') break;
    }
}