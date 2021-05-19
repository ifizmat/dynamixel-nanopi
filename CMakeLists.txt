cmake_minimum_required(VERSION 3.14)
project(example_01_led)

file(GLOB SRC_DYNAMIXEL
     "../dynamixel_sdk/*.cpp"
)



add_executable(test01)

target_sources(test01 PRIVATE
    test01.cpp
    ${SRC_DYNAMIXEL}
)

target_compile_definitions(test01 PRIVATE -DFMT_HEADER_ONLY=1)
target_compile_options(test01 PRIVATE -Wno-psabi)
target_include_directories(test01 PRIVATE
    ../
    ../dynamixel_sdk
)