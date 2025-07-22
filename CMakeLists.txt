cmake_minimum_required(VERSION 3.16)
project(MyCloud LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    src/main.cpp
    src/screens/dashboard.cpp
    src/screens/appSetup.cpp
    src/screens/login.cpp
    src/utilities/auth.cpp
    src/utilities/bcrypt.cpp
    src/utilities/blowfish.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(SQLite3 REQUIRED)

qt6_add_resources(RESOURCES resources.qrc)

add_executable(MyCloud ${SOURCES} ${RESOURCES})
target_link_libraries(MyCloud Qt6::Widgets)