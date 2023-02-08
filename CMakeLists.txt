cmake_minimum_required(VERSION 3.20)

project(testpad VERSION 0.0.1)

find_package(crashpad CONFIG REQUIRED)

add_executable(testpad src/main.cpp)

target_link_libraries(testpad PRIVATE crashpad::crashpad)

find_program(CRASHPAD_HANDLER crashpad_handler)
add_custom_command(TARGET testpad POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CRASHPAD_HANDLER}
    ${CMAKE_CURRENT_BINARY_DIR}/$<$<CONFIG:Release>:Release>$<$<CONFIG:Debug>:Debug>/crashpad_handler$<$<PLATFORM_ID:Windows>:.exe>
)
