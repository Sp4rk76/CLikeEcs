set(prefix "${PROJECT_SOURCE_DIR}/lib/OpenGL")
set(exec_prefix "${prefix}")
set(libdir "${exec_prefix}/lib")
set(OPENGL_PREFIX "${PROJECT_SOURCE_DIR}/lib/OpenGL")
set(OPENGL_EXEC_PREFIX "${PROJECT_SOURCE_DIR}/lib/OpenGL")
set(OPENGL_LIBDIR "${exec_prefix}/lib")
set(OPENGL_INCLUDE_DIRS "${prefix}/include")
set(OPENGL_LIBRARIES "-L${OPENGL_LIBDIR} -lopengl32 -lglu32") # add smthg else ?
string(STRIP "${OPENGL_LIBRARIES}" OPENGL_LIBRARIES)