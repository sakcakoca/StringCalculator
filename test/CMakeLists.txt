# Testing library
#FetchContent_Declare(
#  catch
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG v2.13.6)
#FetchContent_MakeAvailable(catch)
# Adds Catch2::Catch2

# Find Google Test package
find_package(GTest REQUIRED COMPONENTS gtest gmock gtest_main gmock_main)

# Tests need to be added as executables first
set(TEST_EXECUTABLE_NAME "StringCalculatorTester")
add_executable(${TEST_EXECUTABLE_NAME} StringCalculatorTester.cpp)

# I'm using C++17 in the test
target_compile_features(${TEST_EXECUTABLE_NAME} PRIVATE cxx_std_17)



# Should be linked to the main library, as well as the GoogleTest testing library
target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE stringcalc_library GTest::gtest GTest::gtest_main) #Catch2::Catch2)


# Discover tests for ctest
include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE_NAME})