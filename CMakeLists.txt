cmake_minimum_required(VERSION 3.25)
project(AnimateAtlas)

# ====================================================================================
# Options
# ====================================================================================
option(ANIMATEATLAS_BUILD_EXAMPLES "Build AnimateAtlas example projects" ON)

# ====================================================================================
# Output directories (keep build/ clean; put artifacts in out/)
# ====================================================================================
# Note: This does NOT move CMake-generated files (CMakeCache.txt, build system files).
# Those always live in your chosen build directory (e.g. via `cmake -B <dir>`).
set(ANIMATEATLAS_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Output directory for built artifacts")

# Single-config generators (Ninja/Makefiles)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ANIMATEATLAS_OUTPUT_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ANIMATEATLAS_OUTPUT_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ANIMATEATLAS_OUTPUT_DIR}/lib")

# Multi-config generators (Visual Studio / Ninja Multi-Config)
if(CMAKE_CONFIGURATION_TYPES)
    foreach(OUTPUTCONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
        string(TOUPPER "${OUTPUTCONFIG}" OUTPUTCONFIG_UPPER)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ANIMATEATLAS_OUTPUT_DIR}/${OUTPUTCONFIG}/bin")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ANIMATEATLAS_OUTPUT_DIR}/${OUTPUTCONFIG}/lib")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ANIMATEATLAS_OUTPUT_DIR}/${OUTPUTCONFIG}/lib")
        set(CMAKE_PDB_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} "${ANIMATEATLAS_OUTPUT_DIR}/${OUTPUTCONFIG}/pdb")
    endforeach()
endif()
# ====================================================================================




message(STATUS "")
message(STATUS "========== Configuring AnimateAtlas ==========")




# ====================================================================================
# Source and Header Files
# ====================================================================================

# ========= AnimateAtlas ==========
# Source files
set(AnimateAtlas_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Internal/Parsing/SpriteMapData.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Internal/Parsing/AnimationData.cpp"

)
# Header files
set(AnimateAtlas_INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# ====================================================================================




# ====================================================================================
# Library Target
# ====================================================================================
add_library(${PROJECT_NAME} ${AnimateAtlas_SRC})
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${AnimateAtlas_INCLUDE}>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/includes"
)
# ====================================================================================




# ====================================================================================
# Defines
# ====================================================================================

# ===== General Desktop Platform =====
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE ANIMATEATLAS_PLATFORM_DESKTOP
    )
    message(STATUS "Building for: Desktop Platform")
endif()

# ========== Windows Platform ==========
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE ANIMATEATLAS_PLATFORM_WINDOWS
    )
    message(STATUS "Building for: Windows")

    set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# ========== MacOS Platform ==========
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE ANIMATEATLAS_PLATFORM_MACOS
    )
    message(STATUS "Building for: macOS")
endif()

# ========== Debug Mode ==========
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE ANIMATEATLAS_BUILD_DEBUG
    )
    message(STATUS "Building config: Debug")
endif()

# ====================================================================================




# ====================================================================================
# Dependencies
# ====================================================================================

# ========== Desktop Dependencies ==========
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_package(OpenGL REQUIRED)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glad")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image")

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            OpenGL::GL
            Glad
            stb_image
    )
endif()

# ====================================================================================




# ====================================================================================
# Installation
# ====================================================================================

# ========== General Desktop Platform ==========
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    install(TARGETS ${PROJECT_NAME} 
        # TODO: Find a way so that we don't have to add some libraries here kinda like GLFW
        Glad
        stb_image

        EXPORT AnimateAtlasTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()

install(DIRECTORY include/ DESTINATION include)
install(EXPORT AnimateAtlasTargets
    NAMESPACE AnimateAtlas::
    DESTINATION lib/cmake/AnimateAtlas
)

# ====================================================================================




# ====================================================================================
# Examples
# ====================================================================================
#[[
if(ANIMATEATLAS_BUILD_EXAMPLES)
    message(STATUS "Building AnimateAtlas example projects")
    add_subdirectory(examples)
endif()
]]#

if(ANIMATEATLAS_BUILD_EXAMPLES)
    message(STATUS "Building AnimateAtlas example projects")
    add_subdirectory(examples)
endif()
# ====================================================================================




message(STATUS "========== Finished Configuring AnimateAtlas ==========")
message(STATUS "")