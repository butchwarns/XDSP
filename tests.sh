DIR_BUILD=tests/build
cmake -S . -B $DIR_BUILD -DTESTS_ENABLE=ON  
cmake --build $DIR_BUILD --config Release
ctest --test-dir $DIR_BUILD