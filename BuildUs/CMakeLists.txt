cmake_minimum_required(VERSION 3.12)
project(GitUS
    VERSION 1.0
    LANGUAGES C CXX
    DESCRIPTION "Client build")

set(Boost_USE_STATIC_LIBS on)
find_package(Boost 1.71.0 REQUIRED COMPONENTS iostreams filesystem zlib)
			
set(CXX_STANDARD 17)

add_subdirectory(build)
add_subdirectory(tests)

add_executable(BuildUs main.cpp)

target_link_libraries(BuildUs
    PRIVATE
      build
)
