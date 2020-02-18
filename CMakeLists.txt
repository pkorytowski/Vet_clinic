cmake_minimum_required(VERSION 3.5)

project(Vet_clinic LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "inc/*.h")
file(GLOB UIS "src/*.ui")
file(COPY vet.db
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(Vet_clinic ${SOURCES} ${HEADERS} ${UIS})
target_link_libraries(Vet_clinic PRIVATE Qt5::Widgets Qt5::Sql)


find_package(Qt5 COMPONENTS Sql Widgets REQUIRED)
