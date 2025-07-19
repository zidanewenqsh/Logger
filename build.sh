#!/bin/bash

rm -rf build
# Create build directory if it doesn't exist
mkdir -p build
cd build

# Generate Visual Studio 2015 64-bit solution
cmake -G "Visual Studio 14 2015" -A x64 ..

# Build the project
cmake --build . --config RelWithDebInfo

echo "Build completed successfully."
