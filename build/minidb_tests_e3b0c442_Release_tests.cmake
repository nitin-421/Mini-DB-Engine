add_test([=[Parser.ParsesCreate]=]  D:/SDE/MERN/Mini-DB-Engine/build/Release/minidb_tests.exe [==[--gtest_filter=Parser.ParsesCreate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Parser.ParsesCreate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[D:\SDE\MERN\Mini-DB-Engine\tests\ParserTest.cpp:3]==]
    WORKING_DIRECTORY [==[D:/SDE/MERN/Mini-DB-Engine/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Parser.ParsesCrudAndWhere]=]  D:/SDE/MERN/Mini-DB-Engine/build/Release/minidb_tests.exe [==[--gtest_filter=Parser.ParsesCrudAndWhere]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Parser.ParsesCrudAndWhere]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[D:\SDE\MERN\Mini-DB-Engine\tests\ParserTest.cpp:4]==]
    WORKING_DIRECTORY [==[D:/SDE/MERN/Mini-DB-Engine/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Parser.RejectsInvalidSql]=]  D:/SDE/MERN/Mini-DB-Engine/build/Release/minidb_tests.exe [==[--gtest_filter=Parser.RejectsInvalidSql]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Parser.RejectsInvalidSql]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[D:\SDE\MERN\Mini-DB-Engine\tests\ParserTest.cpp:5]==]
    WORKING_DIRECTORY [==[D:/SDE/MERN/Mini-DB-Engine/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Storage.SavesAndLoads]=]  D:/SDE/MERN/Mini-DB-Engine/build/Release/minidb_tests.exe [==[--gtest_filter=Storage.SavesAndLoads]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Storage.SavesAndLoads]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[D:\SDE\MERN\Mini-DB-Engine\tests\StorageTest.cpp:4]==]
    WORKING_DIRECTORY [==[D:/SDE/MERN/Mini-DB-Engine/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Database.Crud]=]  D:/SDE/MERN/Mini-DB-Engine/build/Release/minidb_tests.exe [==[--gtest_filter=Database.Crud]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Database.Crud]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[D:\SDE\MERN\Mini-DB-Engine\tests\DatabaseTest.cpp:4]==]
    WORKING_DIRECTORY [==[D:/SDE/MERN/Mini-DB-Engine/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(minidb_tests_TESTS [==[Parser.ParsesCreate]==] [==[Parser.ParsesCrudAndWhere]==] [==[Parser.RejectsInvalidSql]==] [==[Storage.SavesAndLoads]==] [==[Database.Crud]==])
