add_library(git
    dummy.h 
    dummy.cpp)

target_link_libraries(git 
    PUBLIC 
		${Boost_LIBRARIES}
)
	
target_include_directories(git 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		${Boost_INCLUDE_DIRS}
)