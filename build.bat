rmdir /Q /S build

echo NO_TESTING

cmake . -G "Visual Studio 16 2019" -B build "-DCMAKE_TOOLCHAIN_FILE="settings/settings.cmake"

cmake --build build

#cmake --open build

pause