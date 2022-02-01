cmake_minimum_required(VERSION 3.3 FATAL_ERROR )

project (lab)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

set(SOURCES_STAGE
    Src/main.cpp
    Src/Parser/CodeLexer.cpp
    Src/Parser/CodeParser.cpp
    Src/Parser/CodeVisitor.cpp
    )

add_executable( labrun ${SOURCES_STAGE} )

target_link_libraries( labrun ${CONAN_LIBS} )

set_target_properties(labrun PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

install(TARGETS labrun DESTINATION ~/.local/bin)
