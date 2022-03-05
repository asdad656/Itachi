message(STATUS "-------------Executable Creating----------------------")

aux_source_directory(
    ./
    EXECUTABLE_SRC
)

#生成测试文件
foreach(val_ ${EXECUTABLE_SRC})

    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${val_})

    add_executable(${FILE_NAME} ${val_})

    include_directories(${FILE_NAME} ${PROJECT_SOURCE_DIR}/src/Base/include)

    target_link_libraries(${FILE_NAME} ITACHI_BASE)

    add_dependencies(${FILE_NAME} ITACHI_BASE)
endforeach()




set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)




message(STATUS "-------------Executable Create Successful---------------------")
