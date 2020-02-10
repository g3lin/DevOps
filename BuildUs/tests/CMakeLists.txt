add_executable(buildtests 
    unittests.cpp
	catch.hpp
)


target_link_libraries(buildtests
    PRIVATE
    build
)

target_include_directories(buildtests
    PRIVATE
    build
)



