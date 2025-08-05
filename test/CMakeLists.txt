cmake_minimum_required(VERSION 3.15)
project(digestpp-test CXX)

find_package(digestpp 1.0.0 REQUIRED)

add_executable(examples examples.cc)
add_executable(test test.cc)
add_executable(test_vectors test_vectors.cc)

target_link_libraries(examples PRIVATE digestpp::digestpp)
target_link_libraries(test PRIVATE digestpp::digestpp)
target_link_libraries(test_vectors PRIVATE digestpp::digestpp)

