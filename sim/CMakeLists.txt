
project(sim)

add_executable(
    matpod_sim
    ../src/main.cpp
    # Not servos.cpp
    ../src/testprograms.cpp
    ../src/walkcycle.cpp
    matsim_main.cpp
    servosim.cpp
    )

target_include_directories(
    matpod_sim
    PRIVATE
    fakelibs
    ../src
    lib/sdlpp/include
    )

target_compile_features(matpod_sim PRIVATE cxx_std_17)

find_package(Threads REQUIRED)
target_link_libraries(matpod_sim PRIVATE Threads::Threads)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(matpod_sim ${SDL2_LIBRARIES})
