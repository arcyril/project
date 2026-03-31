add_executable(complexities)

target_sources(complexities PRIVATE
    complexity_analyzer.cpp
    list_analyzer.cpp
    main.cpp
)

target_compile_options(complexities PRIVATE -Wall -Wextra -Wpedantic)

set_target_properties(complexities PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
