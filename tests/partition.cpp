#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "skip" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4, 5, 6 };
    const auto result  = linq::from( &numbers ).skip( 3 ).to_vector();

    REQUIRE( result.size() == 3 );
    REQUIRE( result == std::vector{ 4, 5, 6 } );
}

TEST_CASE( "skip_while" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4, 5, 6 };
    const auto result  = linq::from( &numbers )
                            .skip_while( []( const int i ) {
                                return i < 5;
                            } )
                            .to_vector();

    REQUIRE( result.size() == 2 );
    REQUIRE( result == std::vector{ 5, 6 } );
}


TEST_CASE( "take" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4, 5, 6 };
    const auto result  = linq::from( &numbers ).take( 3 ).to_vector();

    REQUIRE( result.size() == 3 );
    REQUIRE( result == std::vector{ 1, 2, 3 } );
}

TEST_CASE( "take_while" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4, 5, 6 };
    const auto result  = linq::from( &numbers )
                            .take_while( []( const int i ) {
                                return i < 5;
                            } )
                            .to_vector();

    REQUIRE( result.size() == 4 );
    REQUIRE( result == std::vector{ 1, 2, 3, 4 } );
}
