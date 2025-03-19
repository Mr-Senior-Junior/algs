cmake_minimum_required(VERSION 3.14)

project(connectivity_algorithm)


SET(EXE_LIST "4.1_sieve_of_Eratosthenes;4.2_Bernoulli_trials;4.3_josephus;4.4_list_reverse;4.5_list_insert_sort;4.6_point_distance_count")

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
