cmake_minimum_required(VERSION 3.18)

project(
    linq
    DESCRIPTION "linq, a header-only LINQ library for C++."
    VERSION 0.9.0
    HOMEPAGE_URL "https://dervis.de/linq"
    LANGUAGES CXX
)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(isMasterProject ON)
endif ()

option(LINQ_ENABLE_TESTS "Enable LINQ testing" OFF)
option(LINQ_ENABLE_ADDRESS_SANITIZER "Enable ASan" OFF)
option(LINQ_ENABLE_CLANG_TIDY "Enable clang-tidy checks" OFF)

if (LINQ_ENABLE_ADDRESS_SANITIZER AND NOT MSVC)
    message(STATUS "[linq] Enabling address sanitizer")

    set(CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER ON)
    set(CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER_USE_AFTER_RETURN ON)

    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif ()

function(EnableCompilerFlags targetName)
    if (MSVC)
        # Warning level 4, warnings as errors etc.
        target_compile_options(${targetName} INTERFACE /W4 /WX /MP /utf-8)

        # Ignore warnings about sprintf etc.
        target_compile_definitions(${targetName} INTERFACE -D_CRT_SECURE_NO_WARNINGS)
    else ()
        target_compile_options(${targetName} INTERFACE -Wall -Wextra -Wpedantic -Werror)

        # Disable some of the warnings
        target_compile_options(${targetName} INTERFACE -Wno-nonnull)
    endif ()
endfunction()

function(EnableClangTidyChecks targetName)
    if (LINQ_ENABLE_CLANG_TIDY)
        if (NOT MSVC AND NOT APPLE)
            find_program(clangTidyExe NAMES "clang-tidy")
            if (clangTidyExe)
                set(clangTidyCommand "${clangTidyExe}"
                    "-p" "${CMAKE_CURRENT_BINARY_DIR}"
                    "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
                )

                set_target_properties(${targetName} PROPERTIES CXX_CLANG_TIDY "${clangTidyCommand}")
            else ()
                message(WARNING "[linq] clang-tidy executable not found; ignoring")
            endif ()
        endif ()
    endif ()
endfunction()

add_library(linq INTERFACE)
target_include_directories(linq INTERFACE include)
target_compile_features(linq INTERFACE cxx_std_17)

if (NOT isMasterProject)
    EnableCompilerFlags(linq)
endif ()

EnableClangTidyChecks(linq)

if (LINQ_ENABLE_TESTS)
    add_subdirectory(tests)
endif ()
