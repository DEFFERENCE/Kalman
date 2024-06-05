cmake_minimum_required(VERSION 3.10)
project(KalmanFilterPlot)

set(CMAKE_CXX_STANDARD 11)

# Find Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(KalmanFilterPlot src/main.cpp src/Kalman_C.cpp)

# Link against Python libraries
target_link_libraries(KalmanFilterPlot ${PYTHON_LIBRARIES})
