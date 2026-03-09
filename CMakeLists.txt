cmake_minimum_required(VERSION 3.20)

project(geometrical_engine)

add_library(geometry src/Point3D.cpp src/Vector3D.cpp)

target_include_directories(geometry PUBLIC include)
# 2. Создаем исполняемый файл из main.cpp
add_executable(app app/main.cpp) # Замени app/main.cpp на свой путь, если он другой

# 3. Линкуем библиотеку к исполняемому файлу
target_link_libraries(app geometry)