# Installation
mkdir build

cd build

cmake ..

cmake --build . --config Release --target install -- -j $(nproc)

# Using
#include <include/RoboticsGtestExtenstion.hpp>
