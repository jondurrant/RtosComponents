# Add library cpp files

add_library(RTOSComponents STATIC)
target_sources(RTOSComponents PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/AgentInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/BlinkAgent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/WatchdogBlinkAgent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RGBLEDAgent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RGBpwm.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ColorUtils.cpp
)

# Add include directory
target_include_directories(RTOSComponents PUBLIC 
	${CMAKE_CURRENT_LIST_DIR}/src
)

# Add the standard library to the build
target_link_libraries(RTOSComponents PUBLIC pico_stdlib FreeRTOS-Kernel hardware_pwm)

