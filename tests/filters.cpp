#include "datatypes.hpp"
#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

static const std::vector<person> general_people{
    { .name = "P1", .age = 20 },
    { .name = "P2", .age = 21 },
    { .name = "P3", .age = 22 },
    { .name = "P4", .age = 10 },
    { .name = "P5", .age = -10 },
    { .name = "P6", .age = 391 },
};

TEST_CASE( "where" ) {
    SECTION( "simple" ) {
        const auto query = linq::from( &general_people ).where( []( const person& p ) {
            return p.age > 20;
        } );

        auto lines = std::vector<std::string>();

        for ( const auto& [name, age] : query ) {
            lines.push_back( name + ": " + std::to_string( age ) );
        }

        REQUIRE( lines.size() == 3 );
        REQUIRE( lines.at( 0 ) == "P2: 21" );
        REQUIRE( lines.at( 1 ) == "P3: 22" );
        REQUIRE( lines.at( 2 ) == "P6: 391" );
    }

    SECTION( "compound" ) {
        const auto query = linq::from( &general_people ).where( []( const person& p ) {
            return ( p.age > 20 && p.age < 391 ) || p.name == "P5";
        } );

        auto lines = std::vector<std::string>();

        for ( const auto& [name, age] : query ) {
            lines.push_back( name + ": " + std::to_string( age ) );
        }

        REQUIRE( lines.size() == 3 );
        REQUIRE( lines.at( 0 ) == "P2: 21" );
        REQUIRE( lines.at( 1 ) == "P3: 22" );
        REQUIRE( lines.at( 2 ) == "P5: -10" );
    }
}
