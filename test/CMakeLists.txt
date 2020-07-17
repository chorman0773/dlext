
add_library(test-dlso SHARED dlso.c)

add_executable(fdlopen-test fdlopen-test.c)

target_link_libraries(fdlopen-test PRIVATE dl-ext)

add_test(NAME fdlopen-test
        COMMAND fdlopen-test $<TARGET_FILE:test-dlso>
        )