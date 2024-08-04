#include <gtest/gtest.h>
#include "bitmap.h"

// Test constructor
TEST(BitmapTest, Constructor) {
    Bitmap bmp(10, 5);
    EXPECT_EQ(bmp.getWidth(), 10);
    EXPECT_EQ(bmp.getHeight(), 5);
    // Check if all bits are initialized to 0
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 10; ++x) {
            EXPECT_FALSE(bmp.getBit(x, y));
        }
    }
}

// Test setting and getting bits
TEST(BitmapTest, SetAndGetBit) {
    Bitmap bmp(10, 5);
    bmp.setBit(3, 2);
    EXPECT_TRUE(bmp.getBit(3, 2));
    bmp.clearBit(3, 2);
    EXPECT_FALSE(bmp.getBit(3, 2));
}

// Test resizing
TEST(BitmapTest, Resize) {
    Bitmap bmp(10, 5);
    bmp.setBit(3, 2);
    bmp.resize(20, 10);
    EXPECT_EQ(bmp.getWidth(), 20);
    EXPECT_EQ(bmp.getHeight(), 10);
    // Check that the bit was cleared after resizing
    EXPECT_FALSE(bmp.getBit(3, 2));
}

// Test clearing the bitmap
TEST(BitmapTest, Clear) {
    Bitmap bmp(10, 5);
    bmp.setBit(3, 2);
    bmp.clear();
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 10; ++x) {
            EXPECT_FALSE(bmp.getBit(x, y));
        }
    }
}

// Test getting the bitmap data
TEST(BitmapTest, GetBitmap) {
    Bitmap bmp(10, 5);
    bmp.setBit(3, 2);
    const auto& data = bmp.get();
    // Verify the internal representation
    size_t index = 2 * 10 + 3;
    EXPECT_EQ(data[index / 8], 1 << (index % 8));
}

// Test invalid coordinates
TEST(BitmapTest, InvalidCoordinates) {
    Bitmap bmp(10, 5);
    EXPECT_NO_THROW(bmp.setBit(10, 5));
    EXPECT_NO_THROW(bmp.clearBit(10, 5));
    EXPECT_FALSE(bmp.getBit(10, 5));
    EXPECT_FALSE(bmp.getBit(-1, -1));
}

// Test print function (output should be visually checked)
TEST(BitmapTest, Print) {
    Bitmap bmp(5, 5);
    bmp.setBit(0, 0);
    bmp.setBit(4, 4);
    bmp.print();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
