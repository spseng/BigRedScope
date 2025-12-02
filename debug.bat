cd ${PWD}

cmake -S . -B build
cmake --build build --config Release --parallel
cmake --install build --config Release