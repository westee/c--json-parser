cmake_minimum_required(VERSION 3.26)
project(proj_json)

set(CMAKE_CXX_STANDARD 17)

add_library(json
        src/json_node.cpp
        src/json_parser.cpp
        include/json_parser.h
        include/json_nodes.h
)

target_include_directories(json
        PUBLIC
        include
)

# 添加可执行文件
add_executable(main main.cpp)

# 添加依赖库 代表main连接了src/json_node.cpp src/json_node.cpp
target_link_libraries(main json)