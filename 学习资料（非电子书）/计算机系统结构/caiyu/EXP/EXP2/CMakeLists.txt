cmake_minimum_required(VERSION 3.24)
project(EXP2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(/usr/local/include)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fopenmp")
find_library(OPENMP_LIB libomp.dylib /usr/local/lib)

add_executable(EXP2 debug.c)
target_link_libraries(EXP2 LINK_PUBLIC ${OPENMP_LIB})

#add_executable(mul mul.c)
#target_link_libraries(mul LINK_PUBLIC ${OPENMP_LIB})
#add_executable(findpi findpi.c)
#target_link_libraries(findpi LINK_PUBLIC ${OPENMP_LIB})
#add_executable(hellomp hellomp.c)
#target_link_libraries(hellomp LINK_PUBLIC ${OPENMP_LIB})
#
#add_executable(debug debug.c)
#target_link_libraries(debug LINK_PUBLIC ${OPENMP_LIB})

add_executable(debug debug.c)