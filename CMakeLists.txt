cmake_minimum_required(VERSION 3.15)
 
project(geometrical_library_project)
 
add_library(geometry src/Point3D.cpp src/Vector3D.cpp src/LineSegment.cpp src/BezierCurve.cpp src/BSpline.cpp)
 
target_include_directories(geometry PUBLIC include)
 
add_executable(app app/main.cpp)
 
target_link_libraries(app geometry)