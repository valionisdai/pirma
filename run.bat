cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-O3 -funroll-loops -march=native" CMakeLists.txt
cmake --build .
cmake --install .
Work_with_Files.exe
pause

