cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Добавляем директории для заголовочных файлов
include_directories(include)

# Добавляем библиотеку
add_library(Game src/game.c src/aux.c src/config.c src/logics.c src/ai.c)
# Добавляем и сполняемый файл
add_executable(Sudoku src/main.c)
# Линкуем библиотеку с приложением
target_link_libraries(Sudoku Game m)