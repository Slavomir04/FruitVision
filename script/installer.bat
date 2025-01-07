
git clone https://github.com/Slavomir04/FruitVision.git
cd FruitVision

mkdir build
cd build

set /p PATH=Python 3.10 PATH: 

cmake .. -G "MinGW Makefiles" -DPython3_EXECUTABLE=%PATH%

mingw32-make

pause
