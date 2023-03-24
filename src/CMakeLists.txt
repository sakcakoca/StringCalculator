# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.


file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${StringCalculator_SOURCE_DIR}/include/*.hpp")
#set(HEADER_LIST "${StringCalculator_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(stringcalc_library stringcalculator.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(stringcalc_library PUBLIC ../include)

# This depends on (header only) boost
#target_link_libraries(modern_library PRIVATE Boost::boost)

# All users of this library will need at least C++20
target_compile_features(stringcalc_library PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
