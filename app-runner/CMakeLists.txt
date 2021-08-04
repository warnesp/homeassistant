cmake_minimum_required (VERSION 3.6)

project(AppRunner VERSION 1.0)


# add the Listener library
add_subdirectory (Config)
add_subdirectory (Listener)

add_subdirectory(Runner)


