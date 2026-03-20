cmake_minimum_required(VERSION 3.25)
project(AnimateAtlas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ====================================================================================
# Library Options
# ====================================================================================
option(ANIMATEATLAS_BUILD_EXAMPLES "Build AnimateAtlas example projects" ON)

# ====================================================================================
# Settings
# ====================================================================================
# Output directories
set(ANIMATEATLAS_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Output directory for built artifacts")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ANIMATEATLAS_OUTPUT_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ANIMATEATLAS_OUTPUT_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ANIMATEATLAS_OUTPUT_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}")
# ====================================================================================




message(STATUS "")
message(STATUS "========== Configuring AnimateAtlas ==========")




# ====================================================================================
# Source and Header Files
# ====================================================================================

# ========= AnimateAtlas ==========
# Source files
set(AnimateAtlas_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Display/AtlasSprite.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Models/AnimationData.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Models/SpriteMapData.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Experimental/TestParse.cpp"
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/includes> 
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
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

# None so far

# ====================================================================================




# ====================================================================================
# Installation
# ====================================================================================

# ========== General Desktop Platform ==========
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    install(TARGETS ${PROJECT_NAME} 
        EXPORT AnimateAtlasTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )

    install(DIRECTORY include/ DESTINATION include)
    # Vendor libraries
    install(DIRECTORY external/includes/nlohmann DESTINATION include)
    install(DIRECTORY external/includes/glm DESTINATION include)
    
    install(EXPORT AnimateAtlasTargets
        NAMESPACE AnimateAtlas::
        DESTINATION lib/cmake/AnimateAtlas
    )
endif()

# ====================================================================================




# ====================================================================================
# Examples
# ====================================================================================
if(ANIMATEATLAS_BUILD_EXAMPLES)
    message(STATUS "Building AnimateAtlas example projects")
    add_subdirectory(examples)
endif()
# ====================================================================================




message(STATUS "========== Finished Configuring AnimateAtlas ==========")
message(STATUS "")