cmake_minimum_required(VERSION 3.0)

project(psp2cxml-tool C)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

set(COMMON_COMPILE_OPTION "-Wl,-q -Wall -O2 -fno-inline -fno-builtin -fshort-wchar -Wunused-result")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_COMPILE_OPTION}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_OPTION} -fno-rtti -fno-exceptions")

enable_language(CXX)

ExternalProject_add(libz_download
  URL https://www.zlib.net/fossils/zlib-1.3.1.tar.gz
  URL_HASH SHA256=9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23
  DOWNLOAD_DIR ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

set(libz_src
  libz_download-prefix/src/libz_download/adler32.c
  libz_download-prefix/src/libz_download/compress.c
  libz_download-prefix/src/libz_download/crc32.c
  libz_download-prefix/src/libz_download/deflate.c
  # libz_download-prefix/src/libz_download/gzclose.c
  # libz_download-prefix/src/libz_download/gzlib.c
  # libz_download-prefix/src/libz_download/gzread.c
  # libz_download-prefix/src/libz_download/gzwrite.c
  libz_download-prefix/src/libz_download/infback.c
  libz_download-prefix/src/libz_download/inffast.c
  libz_download-prefix/src/libz_download/inflate.c
  libz_download-prefix/src/libz_download/inftrees.c
  libz_download-prefix/src/libz_download/trees.c
  libz_download-prefix/src/libz_download/uncompr.c
  libz_download-prefix/src/libz_download/zutil.c
)

add_custom_command(
  OUTPUT ${libz_src}
  DEPENDS libz_download
)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/libz_download-prefix/src/libz_download
)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/cxml/tinyxml2.cpp
  src/cxml/xml.cpp
  src/cxml/sha1.c
  src/cxml/cxml.cpp
  src/rcs.cpp
  src/rco.cpp
  ${libz_src}
)

add_executable(${PROJECT_NAME}-invalid_parent_warn
  src/main.cpp
  src/cxml/tinyxml2.cpp
  src/cxml/xml.cpp
  src/cxml/sha1.c
  src/cxml/cxml.cpp
  src/rcs.cpp
  src/rco.cpp
  ${libz_src}
)

set_target_properties(${PROJECT_NAME}-invalid_parent_warn
  PROPERTIES LINK_FLAGS ""
  COMPILE_FLAGS "-DPSP2CXML_INVALID_PARENT_WARN"
)

if(DEFINED WIN_BUILD)
  set_target_properties(${PROJECT_NAME}
    PROPERTIES LINK_FLAGS "-static -lgcc -lstdc++ -lwinpthread"
  )

  set_target_properties(${PROJECT_NAME}-invalid_parent_warn
    PROPERTIES LINK_FLAGS "-static -lgcc -lstdc++ -lwinpthread"
  )
endif()
