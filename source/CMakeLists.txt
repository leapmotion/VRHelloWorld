set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCE_FILES *.cpp)

add_executable(VRHelloWorld ${SOURCE_FILES})

find_package (SDL2 REQUIRED)
if (SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIR})
	target_link_libraries (VRHelloWorld ${SDL2_LIBRARY})
endif (SDL2_FOUND)

include_directories(${LIBRARY_PATH}/LeapSDK/include)
target_link_libraries (VRHelloWorld ${LIBRARY_PATH}/LeapSDK/lib)



find_package (SDL2 REQUIRED)
if (SDL2_FOUND)
	include_directories(${SDL2_INCLUDE_DIR})
	target_link_libraries (VRHelloWorld ${SDL2_LIBRARY})
endif (SDL2_FOUND)

target_link_libraries(VRHelloWorld ${SDL2_BIN}/libSDL2.a)


function(echo_all_cmake_variable_values)
  message(STATUS "")
  get_cmake_property(vs VARIABLES)
  foreach(v ${vs})
    message(STATUS "${v}='${${v}}'")
  endforeach(v)
  message(STATUS "")
endfunction()

#echo_all_cmake_variable_values()
