set -e
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/Debug/sk_realtime_renderer
set +e