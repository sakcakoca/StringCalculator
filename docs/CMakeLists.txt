set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

# It will create doxygen documentation for stringcalculator.hpp file and also it will use mainpage.md while creating documentation.
# When you build all targets with cmake it will also build documentation by using doxygen because"ALL" parameter is supplied.
# Documentation can be built also by building "docs" target.
# Build result of documentation (.html or .xml or etc.) will appear in BUILD_DIRECTORY/docs/html folder.

doxygen_add_docs(docs stringcalculator.hpp "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
		ALL
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include"
                COMMENT "Building doxygen documentation")
