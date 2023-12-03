add_custom_target(inputs
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/inputs ${CMAKE_CURRENT_BINARY_DIR}/inputs
)

add_executable(day1 day1.cpp
		utils.h)
add_dependencies(day1 inputs)