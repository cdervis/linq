#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

using namespace std::string_literals;

TEST_CASE( "select" ) {
    const auto words  = std::vector{ "some"s, "example"s, "words"s };
    const auto result = linq::from( &words )
                            .select( []( const std::string& word ) {
                                return word.at( 0 );
                            } )
                            .to_vector();

    REQUIRE( result.size() == 3 );
    REQUIRE( result == std::vector{ 's', 'e', 'w' } );
}

TEST_CASE( "select_to_string" ) {
    const auto numbers = std::vector{ 1, 2, 3 };
    const auto result  = linq::from( &numbers ).select_to_string().to_vector();

    REQUIRE( result.size() == 3 );
    REQUIRE( result == std::vector{ "1"s, "2"s, "3"s } );
}

TEST_CASE( "select_many" ) {
    struct value_type {
        std::vector<int> favorite_numbers;
    };

    const auto values = std::vector<value_type>{
        { .favorite_numbers = { 1, 2, 3, 4 } },
        { .favorite_numbers = { 5, 6, 7, 8 } },
        { .favorite_numbers = { 9, 10, 11, 12 } },
    };

    const auto result = linq::from( &values )
                            .select_many( []( const value_type& p ) {
                                return linq::from( &p.favorite_numbers );
                            } )
                            .to_vector();

    REQUIRE( result.size() == 12 );
    REQUIRE( result == std::vector{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 } );
}
