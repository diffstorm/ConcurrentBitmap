# Bitmap Library

[![Build Status](https://github.com/diffstorm/ConcurrentBitmap/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/diffstorm/ConcurrentBitmap/actions)
[![Language](https://img.shields.io/github/languages/top/diffstorm/ConcurrentBitmap)](https://github.com/diffstorm/ConcurrentBitmap)

This is a simple header-only bitmap library implemented in C++. It provides methods to manipulate a bitmap represented as a vector of a byte, supporting operations such as setting and clearing individual bits, drawing lines and circles, and visualizing the bitmap in the console.

## Features

- **setBit**: Sets a bit at the specified (x, y) coordinates.
- **clearBit**: Clears a bit at the specified (x, y) coordinates.
- **getBit**: Retrieves the state of a bit at the specified (x, y) coordinates.
- **print**: Prints the bitmap to the console.
- **clear**: Clears the entire bitmap.
- **get**: Returns the entire bitmap.

## Usage

Include the `bitmap.h` file in your project:

```cpp
#include "bitmap.h"
```

### Example

```cpp
#include "bitmap.h"
#include <iostream>

int main() {
    Bitmap bitmap(10, 10);
    bitmap.setBit(1, 1);
    bitmap.print();
    return 0;
}
```

### Console Simulator

A console-based simulator is provided to interact with the bitmap class. The available commands are:

- `resize <width> <height>` : Resize the bitmap
- `line <x1> <y1> <x2> <y2>` : Draw a line from (x1, y1) to (x2, y2)
- `circle <x0> <y0> <radius>` : Draw a circle with center (x0, y0) and radius
- `random_shapes` : Draw 2 circles and 2 lines at random places using 4 threads
- `clear` : Clear the bitmap
- `exit` : Exit the simulator

## Building and Running

### Building

1. Install [CMake](https://cmake.org/).
2. Install [Google Test](https://github.com/google/googletest).
3. Clone the repository.
4. Navigate to the project directory.

```sh
git clone https://github.com/diffstorm/ConcurrentBitmap.git
git submodule update --init --recursive
mkdir -p build
cd build
cmake ..
make
```

### Running the Simulator

After building the project, you can run the simulator with:

```sh
./BitmapSimulator
```

### Running Tests

To run the unit tests, use:

```sh
./BitmapTest
```

