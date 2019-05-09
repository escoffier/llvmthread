cmake_minimum_required(VERSION 3.2)
set (CMAKE_CXX_STANDARD 14)

project(threadpool VERSION 0.1 )

#find_package(LLVM REQUIRED CONFIG)

aux_source_directory(. SRCS)

link_directories(/usr/lib/llvm-3.8/lib/)
add_executable(${PROJECT_NAME} ${SRCS} )
target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/llvm-3.8 )
target_link_libraries(${PROJECT_NAME} PUBLIC  LLVMSupport pthread)