
project(sim)

add_executable(
    matpod_sim
    ../src/main.cpp
    # Not servos.cpp
    ../src/testprograms.cpp
    matsim_main.cpp
    servos_sim.cpp
    )

target_include_directories(
    matpod_sim
    PRIVATE
    fakelibs
    ../src
    )
