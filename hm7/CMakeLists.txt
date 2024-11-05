cmake_minimum_required(VERSION 3.28.3)

set(PATCH_VERSION "1" CACHE INTERNAL "PATCH_VERSION" )
set(PROJECT_VERSION 0.0.${PATCH_VERSION})


project(bulk VERSION ${PROJECT_VERSION} LANGUAGES C CXX)


configure_file(version.h.in version.h)

include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

set ( SRC_HEADER
   src/CmdFileWriter.hpp
   src/CommandParser.hpp
   src/CmdParserState.hpp
)
set ( SRC
   src/CmdFileWriter.cpp
   src/CommandParser.cpp
   src/CmdParserState.cpp
)

add_executable(bulk ${SRC_HEADER} ${SRC} main.cpp)

set_property(TARGET bulk PROPERTY CXX_STANDARD 20)


include("functions.cmake")
generate_packages(${PROJECT_NAME})

