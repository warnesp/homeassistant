#create the library
add_library(Config STATIC
    src/Config.cpp  
)

set_property(TARGET Config PROPERTY CXX_STANDARD 17)

#setup the include directories
target_include_directories(Config
    PUBLIC
    include
)

target_link_libraries(Config
    PUBLIC
)
