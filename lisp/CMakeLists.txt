install(FILES
    assert.h
    cons.h
    error.h
    eval.h
    lexenv.h
    list.h
    memory.h
    object.h
    read.h
    symbol.h
    typedef.h
    DESTINATION include/lisp
    )

add_executable(lisp
    cons.cc
    eval.cc
    lexenv.cc
    list.cc
    main.cc
    memory.cc
    object.cc
    read.cc
    symbol.cc
    )
target_compile_options(lisp PRIVATE -O2 -save-temps)

if(NOT DISABLE_TEST)
    set(srcs
        cons_test.cc
        eval_test.cc
        lexenv_test.cc
        list_test.cc
        memory.cc
        memory_test.cc
        object_test.cc
        read_test.cc
        symbol.cc
        symbol_test.cc
        )
    add_executable(lisp_test ${srcs})

    target_link_libraries(lisp_test
        gtest_main)
    target_compile_options(lisp_test PRIVATE -save-temps)

    add_test(NAME lisp_test COMMAND lisp_test)
endif()
