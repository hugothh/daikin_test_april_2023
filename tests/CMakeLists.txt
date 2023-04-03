
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(daikin_test1 daikin_test1.cpp)

target_include_directories(daikin_test1 PUBLIC ../source/thermo/include)

#    PRIVATE

target_link_libraries(daikin_test1 
    GTest::gtest_main
    daikinthermolib
)

add_test(
    NAME daikin_gtest1
    COMMAND daikin_test1
)

