cmake_minimum_required(VERSION 3.10.0)

project(sort_visualizer)

set (CMAKE_CXX_STANDARD 11)

set(SRCS main.cpp)

add_executable(${PROJECT_NAME} ${SRCS})

if(UNIX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

elseif(WIN32)

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/SDL2_mingw_64/include/
                           #${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/SDL2_vc/include/
                           )
target_link_libraries(${PROJECT_NAME} PRIVATE 
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/SDL2_mingw_64/lib/libSDL2.dll.a
                      ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/SDL2_mingw_64/lib/libSDL2main.a
                      #${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/SDL2_vc/lib/x64/SDL2main.lib
                      #${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/SDL2_vc/lib/x64/SDL2.lib
                      )
endif()
