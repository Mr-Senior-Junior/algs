cmake_minimum_required(VERSION 3.14)

project(connectivity_algorithm)


aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)

foreach(SRC ${SRC_LIST})

	get_filename_component(EXE ${SRC} NAME_WLE)
	add_executable(${EXE} ${SRC})
	
	set_target_properties(${EXE}
		PROPERTIES
			CXX_STANDARD 20
			CXX_STANDARD_REQUIRED ON
	)

	target_include_directories(${EXE}
		PRIVATE
			"../../0_common/C++"
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

endforeach()
