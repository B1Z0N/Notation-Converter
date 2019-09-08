cmake_minimum_required(VERSION 3.15.1)

project(NotationConverter)

set(GOOGLE_TEST_HOME_DIR "googletest")

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${GOOGLE_TEST_HOME_DIR}/googlemock/include ${GOOGLE_TEST_HOME_DIR}/googletest/include)
link_directories(${GOOGLE_TEST_HOME_DIR}/build/lib)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")
set(SOURCES )
set(TEST_SOURCES notation_converter_test.cpp)

add_executable(run_tests
  tests/notation_converter_test.cpp
  )

enable_testing()
target_link_libraries(run_tests gtest gmock gtest_main)

# setting up libpthread needed for google test
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(run_tests PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(run_tests "${CMAKE_THREAD_LIBS_INIT}")
endif()

add_test(
  NAME run_tests
  COMMAND run_tests 
  )
