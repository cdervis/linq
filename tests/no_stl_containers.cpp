#include <catch2/catch_test_macros.hpp>

#define LINQ_NO_STL_CONTAINERS
#include <linq.hpp>

TEST_CASE( "no_stl_containers" )
{
    STATIC_REQUIRE( linq::from_to( 1, 10, 1 ).sum().value() == 55 );
}
