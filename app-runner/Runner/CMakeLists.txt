# configure a header file to pass some of the CMake settings
# to the source code. Generate in the output location so it 
# does not get added to source control
configure_file (
    "include/AppRunnerConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/AppRunnerConfig.h"
)

add_executable(app-runner 
    src/AppRunner.cpp   
    src/Arguments.cpp   
    src/Commands.cpp
)

set_property(TARGET app-runner PROPERTY CXX_STANDARD 17)

#because the generated file is put in the output location, include it
target_include_directories(app-runner
    PRIVATE
    include
    "${CMAKE_CURRENT_BINARY_DIR}/include"
)

target_link_libraries (app-runner
    PRIVATE
    Config
    Listener
)
