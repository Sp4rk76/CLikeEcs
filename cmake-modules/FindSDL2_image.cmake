# sdl2 cmake project-config input for ./configure scripts

set(prefix "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.1")
set(exec_prefix "${prefix}")
set(libdir "${exec_prefix}/lib")
set(SDL2_IMAGE_PREFIX "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.1")
set(SDL2_IMAGE_EXEC_PREFIX "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.1")
set(SDL2_IMAGE_LIBDIR "${exec_prefix}/lib")
set(SDL2_IMAGE_INCLUDE_DIRS "${prefix}/include/SDL2")
set(SDL2_IMAGE_LIBRARIES "-L${SDL2_IMAGE_LIBDIR} -lSDL2_image")
string(STRIP "${SDL2_IMAGE_LIBRARIES}" SDL2_IMAGE_LIBRARIES)
