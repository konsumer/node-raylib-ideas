cmake_minimum_required(VERSION 3.19)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)
endif()

if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0042 NEW)
endif()

# this will read package.json and set raylib/NAPI version
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/package.json PKG_STR)
string(JSON PROJECT_NAME GET ${PKG_STR} ${IDX} name)
string(JSON RAYLIB_VERSION GET ${PKG_STR} ${IDX} version)
string(JSON NAPI_VERSION GET ${PKG_STR} ${IDX} binary napi_versions 0)

message(STATUS "Building ${PROJECT_NAME} for Raylib ${RAYLIB_VERSION} on NAPI ${NAPI_VERSION}")
string(REGEX MATCH "^([0-9]+)\\.([0-9]+)\\.([0-9]+)" RAYLIB_VERSION_MATCH ${RAYLIB_VERSION})
set(RAYLIB_VERSION_MAJOR ${CMAKE_MATCH_1})
set(RAYLIB_VERSION_MINOR ${CMAKE_MATCH_2})
set(RAYLIB_VERSION_PATCH ${CMAKE_MATCH_3})

project (${PROJECT_NAME})
add_definitions(-DNAPI_VERSION=${NAPI_VERSION})
# add_definitions(-DNAPI_EXPERIMENTAL)

include(FetchContent)
# set(FETCHCONTENT_QUIET OFF)

# this will grab remote raylib and build it as lib
FetchContent_Declare(raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION_MAJOR}.${RAYLIB_VERSION_MINOR}.zip
)
FetchContent_MakeAvailable(raylib)

if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    # Don't build raylib's examples and games
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()

include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES "src/lib.c")

add_library(node-${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(node-${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(node-${PROJECT_NAME} ${CMAKE_JS_LIB} raylib)

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()