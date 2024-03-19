#include <iostream>

namespace myNamespace {
    void createWindow(const char* title, int width, int height) {
        std::cout << "Creating window with title: " << title << " and size: " << width << "x" << height << std::endl;
    }
}

void createWindow(const char* title, int width = 700, int height = 900) {
    std::cout << "Creating window with title: " << title << " and size: " << width << "x" << height << std::endl;
}

/// @brief 
/// @return 
int main() {
    createWindow("My Window");

    return 0;
}

