install(FILES
    assert.h
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

    add_test(NAME lisp_test COMMAND lisp_test)
endif()
