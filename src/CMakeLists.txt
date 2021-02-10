file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.hpp")
add_library(hashing ${HEADER_LIST})
target_include_directories(hashing PUBLIC "${PROJECT_SOURCE_DIR}/src")
set_target_properties(hashing PROPERTIES LINKER_LANGUAGE CXX)
