cmake_minimum_required(VERSION 3.12)
project(Logger)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)


# # 设置输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# 调试标志
if(NOT CMAKE_BUILD_TYPE)
  # set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_BUILD_TYPE Debug)
endif()


include_directories(include)
# 自动收集 src 目录下的所有 .cpp 和 .cu 文件
# file(GLOB_RECURSE SOURCE_FILES 
#      "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
#      "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cu")

# set(ENV{LD_LIBRARY_PATH} "/usr/local/lib:$ENV{LD_LIBRARY_PATH}")
# 添加可执行文件
# add_executable(MyExecutable ${SOURCE_FILES})
# add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
add_library(Logger SHARED src/Logger.cpp include/Logger.h)

add_executable(main src/main.cpp)
target_link_libraries(main Logger)
if(WIN32)
  # 定义宏，通常用于导出DLL符号
  target_compile_definitions(Logger PRIVATE THREADPOOL_EXPORTS)
endif()

# 添加依赖库
# target_link_libraries(${EXE_NAME} opencv_core opencv_imgproc opencv_imgcodecs m nvonnxparser)
# target_link_libraries(${PROJECT_NAME} m nvonnxparser)
# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${CUDA_LIBRARIES} ${TENSORRT_LIBRARY} ${Boost_LIBRARIES})
