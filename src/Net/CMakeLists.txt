                       
aux_source_directory(./src NET_SRC)

add_library(ITACHI_NET SHARED ${NET_SRC})

add_library(ITACHI_NET_STATIC STATIC ${NET_SRC})

include_directories(./include ITACHI_NET)

include_directories(ITACHI_NET_STATIC ./include)

include_directories(ITACHI_NET_STATIC ${PROJECT_SOURCE_DIR}/src/Base/include)


set(LIBRARY_OUTPUT_PATH
     ${PROJECT_SOURCE_DIR}/lib)


