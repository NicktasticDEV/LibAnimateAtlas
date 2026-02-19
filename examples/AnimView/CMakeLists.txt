cmake_minimum_required(VERSION 3.25)
project(AnimView)

set(ANIMATEATLAS_EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/../../external")

# OpenGL
if (NOT TARGET OpenGL::GL)
    find_package(OpenGL REQUIRED)
endif()

# GLAD
if (NOT TARGET Glad)
    add_subdirectory("${ANIMATEATLAS_EXTERNAL_DIR}/glad" "${CMAKE_BINARY_DIR}/external/glad")
endif()

# GLFW
if (NOT TARGET glfw)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    add_subdirectory("${ANIMATEATLAS_EXTERNAL_DIR}/glfw" "${CMAKE_BINARY_DIR}/external/glfw")
endif()

# ImGui (static library built from bundled sources)
if (NOT TARGET imgui)
    add_library(imgui STATIC
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/imgui.cpp"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/imgui_draw.cpp"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/imgui_tables.cpp"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/imgui_widgets.cpp"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/imgui_demo.cpp"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/backends/imgui_impl_glfw.cpp"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
    )

    target_include_directories(imgui PUBLIC
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui"
        "${ANIMATEATLAS_EXTERNAL_DIR}/imgui/backends"
    )

    target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
endif()

add_executable(${PROJECT_NAME}
    src/Main.cpp
    
    # Core
    src/Core/Application.cpp
    src/Core/Window.cpp
    
    # UI
    src/UI/UILayer.cpp
    src/UI/Panels/ViewportPanel.cpp
    src/UI/Panels/TimelinePanel.cpp
    src/UI/Panels/LibraryPanel.cpp
)

# private include directories for this target
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Link against the main library target from the root project
# (The root project name is AnimateAtlas)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        AnimateAtlas
    OpenGL::GL
    Glad
    glfw
    imgui
)
