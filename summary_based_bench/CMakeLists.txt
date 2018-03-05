cmake_minimum_required(VERSION 3.4.1)

add_library(summary_based_bench SHARED
           src/main/jni/summary_based_bench.cpp)

target_link_libraries(summary_based_bench
                     android
                     log)