install(FILES
    assert.h
    error.h
    memory.h
    object.h
    symbol.h
    typedef.h
    DESTINATION include/lisp
    )

add_executable(lisp
    main.cc
    memory.cc
    object.cc
    symbol.cc
    )
target_compile_options(lisp PRIVATE -O2 -save-temps)

if(NOT DISABLE_TEST)
    set(srcs
        object.cc
        object_test.cc
        memory.cc
        memory_test.cc
        symbol.cc
        symbol_test.cc
        )
    add_executable(lisp_test ${srcs})

    target_link_libraries(lisp_test
        gtest_main)
    target_compile_options(lisp_test PRIVATE -save-temps)

    add_test(NAME lisp_test COMMAND lisp_test)
endif()
