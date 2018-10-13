install(FILES
    assert.h
    cons.h
    error.h
    eval.h
    lexenv.h
    list.h
    memory.h
    object.h
    optional.h
    prin1.h
    read.h
    serial.h
    symbol.h
    typedef.h
    DESTINATION include/lisp
    )

add_executable(lisp
    cons.c
    eval.c
    lexenv.c
    list.c
    main.cc
    memory.c
    object.c
    prin1.c
    read.c
    serial.cc
    symbol.c
    )
target_compile_options(lisp PRIVATE -O2 -save-temps)

if(NOT DISABLE_TEST)
    set(srcs
        cons_test.cc
        eval_test.cc
        lexenv_test.cc
        list_test.cc
        memory_test.cc
        object_test.cc
        prin1_test.cc
        read_test.cc
        serial_test.cc
        symbol_test.cc
        test_util.cc
        )
    add_executable(lisp_test ${srcs})

    target_link_libraries(lisp_test
        gtest_main)
    target_compile_options(lisp_test PRIVATE -save-temps)

    add_test(NAME lisp_test COMMAND lisp_test)
endif()
