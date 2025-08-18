#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "cxx17" )
{
    REQUIRE( linq::from_to( 1, 10, 1 ).sum().value() == 55 );
}
