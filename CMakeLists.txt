cmake_minimum_required(VERSION 3.10)

project(SLR_Parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(FLEX REQUIRED)

FLEX_TARGET(LexerScanner 
            src/lexer.l 
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)


add_executable(SLR 
    main.cpp
    src/LexicalAnalysis.cpp
    src/SyntaxAnalysis.cpp 
    ${FLEX_LexerScanner_OUTPUTS}
)

target_include_directories(SLR PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SLR ${FLEX_LIBRARIES})

enable_testing()
add_subdirectory(tests)