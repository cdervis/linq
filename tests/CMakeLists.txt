if (NOT TARGET Catch2)
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.0
    )

    FetchContent_MakeAvailable(Catch2)
endif ()

add_executable(tests
    aggregation.cpp
    basics.cpp
    concatenation.cpp
    cxx17.cpp
    custom_string_type.cpp
    element_access.cpp
    filters.cpp
    generation.cpp
    join.cpp
    no_stl_containers.cpp
    partition.cpp
    projection.cpp
    quantifiers.cpp
    set.cpp
    sorting.cpp
    datatypes.hpp
)

target_compile_features(tests PRIVATE cxx_std_20)

set_source_files_properties(cxx17.cpp
    CXX_STANDARD 17
)

EnableClangTidyChecks(tests)

target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
    linq
)
