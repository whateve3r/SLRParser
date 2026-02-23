find_package(GTest REQUIRED)

add_executable(run_tests
    lexer_test.cpp
    parser_test.cpp
)

target_link_libraries(run_tests
    PRIVATE
    slr_core
    GTest::gtest 
    GTest::gtest_main
    pthread
)

add_test(NAME AllTests COMMAND run_tests)