add_library(hashing common.h DiskManager.hpp Record.hpp)
target_include_directories(hashing PUBLIC "${PROJECT_SOURCE_DIR}/src")
set_target_properties(hashing PROPERTIES LINKER_LANGUAGE CXX)
