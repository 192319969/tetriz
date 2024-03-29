cmake_minimum_required(VERSION 3.15)
project(tetriz)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/terminal/src terminal)
aux_source_directory(${PROJECT_SOURCE_DIR}/utils/src utils)
aux_source_directory(${PROJECT_SOURCE_DIR}/draw/src draw)
aux_source_directory(${PROJECT_SOURCE_DIR}/control/src control)
aux_source_directory(${PROJECT_SOURCE_DIR}/game/src game)
aux_source_directory(${PROJECT_SOURCE_DIR}/tetromino/src tetromino)
aux_source_directory(${PROJECT_SOURCE_DIR}/piece/src piece)
aux_source_directory(${PROJECT_SOURCE_DIR}/window/src window)
set(SRC ${EXTERNAL_SRC}
        ${SRC} 
        ${terminal} 
        ${utils} 
        ${draw} 
        ${control} 
        ${game} 
        ${tetromino} 
        ${piece}
        ${window}
        )

include_directories(
        ${PROJECT_SOURCE_DIR}/terminal/inc 
        ${PROJECT_SOURCE_DIR}/utils/inc 
        ${PROJECT_SOURCE_DIR}/draw/inc 
        ${PROJECT_SOURCE_DIR}/control/inc 
        ${PROJECT_SOURCE_DIR}/game/inc 
        ${PROJECT_SOURCE_DIR}/tetromino/inc 
        ${PROJECT_SOURCE_DIR}/piece/inc 
        ${PROJECT_SOURCE_DIR}/window/inc 
        ${PROJECT_SOURCE_DIR})

if(MSVC)
        # 添加json源文件路径
        aux_source_directory(${PROJECT_SOURCE_DIR}/external/src/json EXTERNAL_SRC)

        # 添加json头文件路径
        include_directories(${PROJECT_SOURCE_DIR}/external/include)

        # 添加json库文件路径
        link_directories(${PROJECT_SOURCE_DIR}/external/lib)
endif()

# configure_file(${PROJECT_SOURCE_DIR}/tetriz.map ${PROJECT_BINARY_DIR})
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tetriz.map DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)

add_executable(tetriz ${SRC})

if(MSVC)
        target_link_libraries(tetriz jsoncpp)

        target_compile_options(tetriz PRIVATE "/utf-8")
        set_property(TARGET tetriz PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif(MINGW)
        target_compile_options(tetriz PRIVATE "-fexec-charset=utf-8")
endif()