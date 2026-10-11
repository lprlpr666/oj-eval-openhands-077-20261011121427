cmake_minimum_required(VERSION 3.10)

project(problem_077 LANGUAGES CXX)

# Set C++ standard
cmake_policy(SET CMP0014 NEW)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(.)

# This is a header-only library, so we don't create an executable
# The OJ will include our headers in their test code
