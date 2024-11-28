cmake_minimum_required(VERSION 3.14)

project(connectivity_algorithm)


SET(EXE_LIST "3.1_sequential_search")

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


# set_target_properties(1_fast_search 2_fast_union
# 	PROPERTIES
# 		CXX_STANDARD 17
# 		CXX_STANDARD_REQUIRED ON
# )


# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
# 	target_compile_options(1_fast_search 2_fast_union
# 		PRIVATE 
# 			-g
# 			-Wall
# 			-Wextra
# 			-Werror
# 			-pedantic
# 	)
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
# 	target_compile_options(1_fast_search 2_fast_union
# 		PRIVATE
# 			/EHsc
# 			/W4
# 			/WX
# 	)
# endif()

