cmake_minimum_required(VERSION 3.15.1)

project(NotationConverter)

set(GOOGLE_TEST_HOME_DIR "googletest")

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${GOOGLE_TEST_HOME_DIR}/googlemock/include ${GOOGLE_TEST_HOME_DIR}/googletest/include)
link_directories(${GOOGLE_TEST_HOME_DIR}/build/lib)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(SOURCES 
  src/notation_converter.cpp 
  src/syntax_tree.cpp 
  main.cpp
)

set(TEST_SOURCES
  tests/notation_converter_test.cpp
  tests/syntax_tree_test.cpp
)

add_executable(run_tests ${TEST_SOURCES} ${SOURCES})
target_link_libraries(run_tests gtest gmock)

# setting up libpthread needed for google test
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(run_tests PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(run_tests "${CMAKE_THREAD_LIBS_INIT}")
endif()

