# 1. Создайте папку build
mkdir build
cd build

# 2. Запустите CMake
cmake ..

# 3. Соберите проект
cmake --build .

# 4. Запустите программу
./calculator

# 5. Просмотрите логи
cat logs/calculator.log