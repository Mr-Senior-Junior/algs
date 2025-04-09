cmake_minimum_required(VERSION 3.14)

project(connectivity_algorithm)


SET(EXE_LIST "5.1_binary_number;5.2_hanoi;5.3_fibonacci_bag;5.4_trees")

FOREACH(EXE ${EXE_LIST})

	add_executable(${EXE} "${EXE}.cpp")
	
	set_target_properties(${EXE}
		PROPERTIES
			CXX_STANDARD 20
			CXX_STANDARD_REQUIRED ON
	)

	if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_compile_options(${EXE}
			PRIVATE 
				-g
				-Wall
				-Wextra
				-Werror
				-pedantic
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${EXE}
			PRIVATE
				/EHsc
				/W4
				/WX
		)
	endif()

ENDFOREACH()
