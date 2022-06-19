cmake_minimum_required(VERSION 3.22)
project(7_1)

set(CMAKE_CXX_STANDARD 17)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_subdirectory(third-party/fmt)

set(SOURCES
    src/main.cpp
    src/application.cpp
    src/abcu_course.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            include/
            fmt
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            fmt
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data ${OUTPUT_DIR}/data)