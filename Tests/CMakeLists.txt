include(GoogleTest)
enable_testing()

link_directories(/usr/local/lib)

INCLUDE_DIRECTORIES(..)


macro (make_test TEST_NAME MORE_FILES)

    add_executable(${TEST_NAME} "${TEST_NAME}.cpp" ${MORE_FILES})
    target_link_libraries(${TEST_NAME} gtest_main gtest)
    gtest_discover_tests(${TEST_NAME})


endmacro()

make_test (parserCombinatorsTests "")
make_test (basicParserCombinatorTests "")# "../MyLanguage/basicparsercombinators.cpp")
make_test (parserTests "../MyLanguage/parser.cpp")
