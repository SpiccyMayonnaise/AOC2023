add_custom_target(inputs
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/inputs ${CMAKE_CURRENT_BINARY_DIR}/inputs
)

add_executable(day1 day1.cpp)
add_dependencies(day1 inputs)

add_executable(day2 day2.cpp)
add_dependencies(day2 inputs)

add_executable(day3 day3.cpp)
add_dependencies(day3 inputs)