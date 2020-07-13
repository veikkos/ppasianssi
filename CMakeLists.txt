cmake_minimum_required(VERSION 3.0)
project(ppasianssi VERSION 1.0.0)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(EMCC 1)
endif()

# EMCC can retrieve SDL2 by itself
if (NOT EMCC)
    set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/cmake-modules)

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake-modules/FindSDL2.cmake")
        file(DOWNLOAD "https://github.com/tcbrindle/sdl2-cmake-scripts/raw/master/FindSDL2.cmake" "${CMAKE_BINARY_DIR}/cmake-modules/FindSDL2.cmake")
    endif()

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake-modules/FindSDL2_image.cmake")
        file(DOWNLOAD "https://github.com/tcbrindle/sdl2-cmake-scripts/raw/master/FindSDL2_image.cmake" "${CMAKE_BINARY_DIR}/cmake-modules/FindSDL2_image.cmake")
    endif()

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
else()
    set(USE_FLAGS "-O3 -s ASYNCIFY -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' --preload-file assets/ --shell-file ${CMAKE_SOURCE_DIR}/src/web/shell.html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

if (WIN32)
    add_compile_options(/MP /MT /WX /wd4996)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

# Library
file(GLOB SOURCES
    src/*.h src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    )

# Game with GUI
add_executable(${PROJECT_NAME}-gui src/game/main.cpp)

target_link_libraries(${PROJECT_NAME}-gui ${PROJECT_NAME})

if (NOT EMCC)
    # Simulation
    add_executable(${PROJECT_NAME}-simulation ${SOURCES} src/simulation/main.cpp)

    target_link_libraries(${PROJECT_NAME}-simulation ${PROJECT_NAME})
endif()
