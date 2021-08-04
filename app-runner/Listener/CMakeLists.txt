#create the library
add_library(Listener STATIC
	src/Listener.cpp	
)

set_property(TARGET Listener PROPERTY CXX_STANDARD 17)

#needed for visual studio/xcode to list headers
target_sources(Listener
	PRIVATE
	"include/Listener.h"
)

#setup the include directories
target_include_directories(Listener
	PUBLIC
	include
)

target_link_libraries(Listener
	PUBLIC
	pthread
)
