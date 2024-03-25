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
set(SRC ${SRC} 
        ${terminal} 
        ${utils} 
        ${draw} 
        ${control} 
        ${game} 
        ${tetromino} 
        ${piece}
        )

include_directories(${PROJECT_SOURCE_DIR}/terminal/inc 
                    ${PROJECT_SOURCE_DIR}/utils/inc 
                    ${PROJECT_SOURCE_DIR}/draw/inc 
                    ${PROJECT_SOURCE_DIR}/control/inc 
                    ${PROJECT_SOURCE_DIR}/game/inc 
                    ${PROJECT_SOURCE_DIR}/tetromino/inc 
                    ${PROJECT_SOURCE_DIR}/piece/inc 
                    ${PROJECT_SOURCE_DIR})

configure_file(${PROJECT_SOURCE_DIR}/tetriz.map ${PROJECT_BINARY_DIR})
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tetriz.map DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)

add_executable(tetriz ${SRC})
