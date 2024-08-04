#include "bitmap.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <thread>
#include <random>

uint32_t crc32(const std::vector<uint8_t>& data) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < data.size(); ++i) {
        crc ^= data[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    return ~crc;
}

void addLine(Bitmap &bmp, int x1, int y1, int x2, int y2) {
    // Bresenham's Line Algorithm
    int dx = std::abs(x2 - x1);
    int dy = -std::abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    while (true) {
        bmp.setBit(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void addCircle(Bitmap &bmp, int x0, int y0, int radius) {
    // Midpoint Circle Algorithm
    int x = radius;
    int y = 0;
    int err = 0;
    while (x >= y) {
        bmp.setBit(x0 + x, y0 + y);
        bmp.setBit(x0 - x, y0 + y);
        bmp.setBit(x0 + y, y0 + x);
        bmp.setBit(x0 - y, y0 + x);
        bmp.setBit(x0 - x, y0 - y);
        bmp.setBit(x0 + x, y0 - y);
        bmp.setBit(x0 - y, y0 - x);
        bmp.setBit(x0 + y, y0 - x);
        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void drawRandomShapes(Bitmap &bmp) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disWidth(0, bmp.getWidth() - 1);
    std::uniform_int_distribution<> disHeight(0, bmp.getHeight() - 1);
    std::uniform_int_distribution<> disRadius(1, std::min(bmp.getWidth(), bmp.getHeight()) / 4);

    std::thread t1([&]() { addLine(bmp, disWidth(gen), disHeight(gen), disWidth(gen), disHeight(gen)); });
    std::thread t2([&]() { addLine(bmp, disWidth(gen), disHeight(gen), disWidth(gen), disHeight(gen)); });
    std::thread t3([&]() { addCircle(bmp, disWidth(gen), disHeight(gen), disRadius(gen)); });
    std::thread t4([&]() { addCircle(bmp, disWidth(gen), disHeight(gen), disRadius(gen)); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void printHelp() {
    std::cout << "Commands:\n"
              << "  resize <width> <height>     - Resize the bitmap\n"
              << "  line <x1> <y1> <x2> <y2>    - Draw a line from (x1, y1) to (x2, y2)\n"
              << "  circle <x0> <y0> <radius>   - Draw a circle with center (x0, y0) and radius\n"
              << "  random_shapes                - Draw 2 circles and 2 lines at random places using 4 threads\n"
              << "  clear                        - Clear the bitmap\n"
              << "  exit                         - Exit the program\n";
}

bool parseInt(const std::string& str, int& result) {
    try {
        result = std::stoi(str);
        return true;
    } catch (std::invalid_argument&) {
        return false;
    }
}

int main() {
    Bitmap bmp(30, 15); // Default size
    uint32_t bcrc = crc32(bmp.get());

    std::string command;
    printHelp();

    while (true) {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "resize") {
            std::string widthStr, heightStr;
            std::cin >> widthStr >> heightStr;
            int width, height;
            if (parseInt(widthStr, width) && parseInt(heightStr, height)) {
                bmp.resize(width, height);
            } else {
                std::cout << "Invalid width or height!\n";
            }
        } else if (command == "line") {
            std::string x1Str, y1Str, x2Str, y2Str;
            std::cin >> x1Str >> y1Str >> x2Str >> y2Str;
            int x1, y1, x2, y2;
            if (parseInt(x1Str, x1) && parseInt(y1Str, y1) && parseInt(x2Str, x2) && parseInt(y2Str, y2)) {
                addLine(bmp, x1, y1, x2, y2);
            } else {
                std::cout << "Invalid coordinates!\n";
            }
        } else if (command == "circle") {
            std::string x0Str, y0Str, radiusStr;
            std::cin >> x0Str >> y0Str >> radiusStr;
            int x0, y0, radius;
            if (parseInt(x0Str, x0) && parseInt(y0Str, y0) && parseInt(radiusStr, radius)) {
                addCircle(bmp, x0, y0, radius);
            } else {
                std::cout << "Invalid center or radius!\n";
            }
        } else if (command == "random_shapes") {
            drawRandomShapes(bmp);
        } else if (command == "clear") {
            bmp.clear();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command!\n";
            printHelp();
            continue;
        }

        // Print if there is a change
        uint32_t crc = crc32(bmp.get());
        if (crc != bcrc) {
            bcrc = crc;
            bmp.print();
        }
    }

    return 0;
}
