# configure a header file to pass some of the CMake settings
# to the source code. Generate in the output location so it 
# does not get added to source control
configure_file (
  "include/TutorialConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/include/TutorialConfig.h"
)

add_executable(AppRunner 
	src/AppRunner.cpp	
)

#needed for visual studio/xcode to list headers
target_sources(AppRunner
	PRIVATE
	"${CMAKE_CURRENT_BINARY_DIR}/include/TutorialConfig.h"
)

#because the generated file is put in the output location, include it
target_include_directories(AppRunner
	PRIVATE
	include
	"${CMAKE_CURRENT_BINARY_DIR}/include"
)

target_link_libraries (AppRunner
	PRIVATE
	Listener
)
