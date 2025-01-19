scriptdir="$(dirname "$0")"
cd "$scriptdir"

DIR_BUILD=build
ctest --test-dir $DIR_BUILD