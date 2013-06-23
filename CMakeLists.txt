project(neuralnet)
cmake_minimum_required(VERSION 2.8)

FILE(GLOB MyCSources *.cpp)

ADD_EXECUTABLE(neuralnet ${MyCSources})

include_directories(neuralnet /usr/include/SDL)

install(TARGETS neuralnet RUNTIME DESTINATION bin)

target_link_libraries(neuralnet SDL SDL_image SDL_gfx)
