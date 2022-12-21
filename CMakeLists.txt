cmake_minimum_required(VERSION 3.2)
project(Matrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SRC_LIST  
    source/main.cpp
    source/matrix.cpp
    source/linreg.cpp
)
# file(GLOB CPPS "*.cpp")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} ${SRC_LIST})
# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})k