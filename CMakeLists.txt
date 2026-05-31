cmake_minimum_required(VERSION 3.15)
project(daily_problem_solving CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dynamically find all C++ files
file(GLOB_RECURSE SOLUTION_FILES "Codeforces/*.cpp" "LeetCode/*.cpp")

foreach(FILE_PATH ${SOLUTION_FILES})
    # Extract filename without extension
    get_filename_component(TARGET_NAME ${FILE_PATH} NAME_WE)

    # Create the executable
    add_executable(${TARGET_NAME} ${FILE_PATH})

    # This sets the default "Run Configuration" working directory to your root folder!
    set_target_properties(${TARGET_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            XCODE_ATTRIBUTE_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endforeach()