cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0135 NEW) # Нужно, чтобы лишних предупреждений не возникало при тестах

project(geometrical_library_project)

add_library(geometry 
	# Базовые примитивы
	src/BasePrimitives/Point3D.cpp 
	src/BasePrimitives/Vector3D.cpp
	src/BasePrimitives/Matrix2x2.cpp
 
	# Кривые - отрезок прямой, кривая Безье и B-сплайн
	src/Curves/LineSegment.cpp 
	src/Curves/BezierCurve.cpp 
	src/Curves/BSplineCurve.cpp 
	src/Curves/ICurve.cpp 

	# Поверхности Безье и сплайновая
	src/Surfaces/BezierSurface.cpp
	src/Surfaces/BSplineSurface.cpp
	src/Surfaces/ISurface.cpp
	
	src/BoundingBox/BoundingBox.cpp
)

target_include_directories(geometry PUBLIC include)

# Подключение тестов от Гугла 
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Делаем так, чтобы GTest собирался без лишних сообщений
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Мы включаем функцию CTest
enable_testing()

# Создаем исполняемый файл с уникальным именем (например, geometry_tests)
add_executable(geometry_tests tests/test_main.cpp)

# Линкуем тесты
target_link_libraries(geometry_tests 
    geometry 
    gtest 
    gtest_main 
)

# Регистрируем тесты
add_test(NAME AllTests COMMAND geometry_tests)