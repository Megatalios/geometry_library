cmake_minimum_required(VERSION 3.15)

project(geometrical_library_project)

add_library(geometry 
	# Базовые примитивы - вектор и точка
	src/BasePrimitives/Point3D.cpp 
	src/BasePrimitives/Vector3D.cpp
 
	# Кривые - отрезок прямой, кривая Безье и B-сплайн
	src/Curves/LineSegment.cpp 
	src/Curves/BezierCurve.cpp 
	src/Curves/BSpline.cpp 
	src/Curves/ICurve.cpp 

	# Поверхности Безье и сплайновая
	src/Surfaces/BezierSurface.cpp
	src/Surfaces/BSplineSurface.cpp
	
	src/BoundingBox/BoundingBox.cpp
)

target_include_directories(geometry PUBLIC include)

add_executable(app app/main.cpp)

target_link_libraries(app geometry)