scriptdir="$(dirname "$0")"
cd "$scriptdir"
cd ..

DIR_BUILD=tests/build
cmake -S . -B $DIR_BUILD -DTESTS_ENABLE=ON  
cmake --build $DIR_BUILD --config Release