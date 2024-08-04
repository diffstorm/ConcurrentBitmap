#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include <mutex>
#include <iostream>

class Bitmap {
public:
    Bitmap(int width, int height) 
        : width(width), height(height), bitmap((width * height + 7) / 8, 0) {}

    void resize(int newWidth, int newHeight) {
        std::lock_guard<std::mutex> lock(mtx);
        width = newWidth;
        height = newHeight;
        bitmap.resize((newWidth * newHeight + 7) / 8);
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    void setBit(int x, int y) {
        std::lock_guard<std::mutex> lock(mtx);
        setBitInternal(x, y);
    }

    void clearBit(int x, int y) {
        std::lock_guard<std::mutex> lock(mtx);
        clearBitInternal(x, y);
    }

    bool getBit(int x, int y) const {
        std::lock_guard<std::mutex> lock(mtx);
        return getBitInternal(x, y);
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        std::fill(bitmap.begin(), bitmap.end(), 0);
    }
	
	const std::vector<uint8_t>& get() const {
		std::lock_guard<std::mutex> lock(mtx);
		return bitmap;
	}

    void print() const {
        std::lock_guard<std::mutex> lock(mtx);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << (getBitInternal(x, y) ? '*' : ' ');
            }
            std::cout << '\n';
        }
    }

private:
    bool isValidCoordinate(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    void setBitInternal(int x, int y) {
        if (isValidCoordinate(x, y)) {
            size_t index = y * width + x;
            bitmap[index / 8] |= (1 << (index % 8));
        }
    }

    void clearBitInternal(int x, int y) {
        if (isValidCoordinate(x, y)) {
            size_t index = y * width + x;
            bitmap[index / 8] &= ~(1 << (index % 8));
        }
    }

    bool getBitInternal(int x, int y) const {
        if (isValidCoordinate(x, y)) {
            size_t index = y * width + x;
            return bitmap[index / 8] & (1 << (index % 8));
        }
        return false;
    }

    int width;
    int height;
    std::vector<uint8_t> bitmap;
    mutable std::mutex mtx;
};

#endif // BITMAP_H
