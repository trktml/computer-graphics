cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
include_directories("${PROJECT_SOURCE_DIR}/src/utils")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/types")

FILE(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/**.cc)
FILE(GLOB_RECURSE header_files ${PROJECT_SOURCE_DIR}/**.h)

message(STATUS "source_files=${source_files}")
message(STATUS "header_files=${header_files}")

set(engine_sources
	${source_files}
	${header_files}
)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )

install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
