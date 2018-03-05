cmake_minimum_required(VERSION 3.4.1)

add_library(heap_summary SHARED
           src/main/jni/heap_summary.cpp)

target_link_libraries(heap_summary
                     android
                     log)