#create the library
add_library(Listener STATIC
    src/Listener.cpp    
)

set_property(TARGET Listener PROPERTY CXX_STANDARD 17)

#setup the include directories
target_include_directories(Listener
    PUBLIC
    include
)

target_link_libraries(Listener
    PUBLIC
    pthread
)
