add_executable(ds-tests)

target_sources(ds-tests PRIVATE
    amt/implicit_sequence.test.cpp
    amt/explicit_sequence.test.cpp

    mm/compact_memory_object_manager.test.cpp
    mm/compact_memory_trivial_manager.test.cpp
    mm/system_memory_manager.test.cpp

    other/utils.cpp

    main.cpp
)

target_compile_options(ds-tests PRIVATE -Wall -Wextra -Wpedantic)

set_target_properties(ds-tests PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(ds-tests PRIVATE ds stest)
