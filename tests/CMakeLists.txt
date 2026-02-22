find_package(GTest REQUIRED)

add_executable(run_tests
    lexer_test.cpp
    parser_test.cpp
    ../src/LexicalAnalysis.cpp
    ../src/SyntaxAnalysis.cpp
    ${FLEX_LexerScanner_OUTPUTS}
)

target_include_directories(run_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_BINARY_DIR}/.. 
)


target_link_libraries(run_tests 
    GTest::gtest 
    GTest::Main
    pthread
)

add_test(NAME AllTests COMMAND run_tests)