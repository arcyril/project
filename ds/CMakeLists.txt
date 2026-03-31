add_executable(ds-main)

target_sources(ds-main PRIVATE main.cpp)

target_link_libraries(ds-main PRIVATE ds)

set_target_properties(ds-main PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
