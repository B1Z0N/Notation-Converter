cmake_minimum_required(VERSION 3.15.1)

project(NotationConverter)

set(GOOGLE_TEST_HOME_DIR "googletest")

# include project dir
include_directories(${PROJECT_SOURCE_DIR}/include)

# include and link gtest dirs
include_directories(${GOOGLE_TEST_HOME_DIR}/googlemock/include ${GOOGLE_TEST_HOME_DIR}/googletest/include)
link_directories(${GOOGLE_TEST_HOME_DIR}/build/lib)

# some additional flags to compile with
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -g")

set(SOURCES 
  src/notation_converter.cpp 
  src/syntax_tree.cpp 
)

set(TEST_SOURCES
  tests/notation_converter_test.cpp
  tests/syntax_tree_test.cpp
  tests/main.cpp

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

# generate static library from the sources
add_library(notaconv STATIC ${SOURCES})

# set the location for library installation -- current folder in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS notaconv DESTINATION .)