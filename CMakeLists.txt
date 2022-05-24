cmake_minimum_required(VERSION 3.20)

project(Csontest)

set(C_STANDARD 11)

# add_library(Cson_lib
#     Cson.c    
# )

add_executable(Csontest 
    testcson.c
)

# target_link_libraries(Csontest Cson_lib)