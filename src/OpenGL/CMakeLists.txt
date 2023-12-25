message( Processing 'OpenGL/CMakeLists.txt'...)

list(APPEND SRCS
    ${CMAKE_CURRENT_LIST_DIR}/openGLDebug.cpp
    ${CMAKE_CURRENT_LIST_DIR}/shaders.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IndexBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/VertexArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/VertexBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/VertexBufferLayout.cpp
)