cmake_minimum_required(VERSION 3.4.1)

add_library(leak SHARED
           src/main/jni/leak.cpp)

# Include libraries needed for hello-jni lib
target_link_libraries(leak
                     android
                     log)