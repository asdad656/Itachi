
aux_source_directory(./src BASE_SRC)

add_library(ITACHI_BASE SHARED ${BASE_SRC})

add_library(ITACHI_BASE_STATIC STATIC ${BASE_SRC})


include_directories(ITACHI_BASE ./include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
