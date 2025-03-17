cmake_minimum_required(VERSION 3.10)
project(ppong C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(/opt/homebrew/Cellar/SDL2/2.32.2/include)
link_directories(/opt/homebrew/Cellar/SDL2/2.32.2/lib)

link_libraries(SDL2main SDL2)

add_executable(ppong
	src/main.c
	)

