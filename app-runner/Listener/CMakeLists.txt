#create the library
add_library(Listener STATIC
	src/Listener.cpp	
)

#needed for visual studio/xcode to list headers
target_sources(MathLib
	PRIVATE
	"include/Listener.h"
)

#setup the include directories
target_include_directories(Listener
	PUBLIC
	include
)
