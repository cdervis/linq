#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

using namespace std::string_literals;

TEST_CASE( "order_by" ) {
    const auto words = std::vector{ "hello"s, "world"s, "here"s, "are"s, "some"s, "sorted"s, "words"s };

    const auto result = linq::from( &words )
                            .order_by(
                                []( const std::string& word ) {
                                    return word.size();
                                },
                                linq::sort_direction::ascending )
                            .to_vector();

    REQUIRE( result.size() == 7 );
    REQUIRE( result.at( 0 ) == "are" );
    REQUIRE( result.at( 1 ) == "here" );
    REQUIRE( result.at( 2 ) == "some" );
    REQUIRE( result.at( 3 ) == "hello" );
    REQUIRE( result.at( 4 ) == "world" );
    REQUIRE( result.at( 5 ) == "words" );
    REQUIRE( result.at( 6 ) == "sorted" );
}

TEST_CASE( "order_by_ascending" ) {
    const auto words = std::vector{ "hello"s, "world"s, "here"s, "are"s, "some"s, "sorted"s, "words"s };

    const auto result = linq::from( &words )
                            .order_by_ascending( []( const std::string& word ) {
                                return word.size();
                            } )
                            .to_vector();

    REQUIRE( result.size() == 7 );
    REQUIRE( result.at( 0 ) == "are" );
    REQUIRE( result.at( 1 ) == "here" );
    REQUIRE( result.at( 2 ) == "some" );
    REQUIRE( result.at( 3 ) == "hello" );
    REQUIRE( result.at( 4 ) == "world" );
    REQUIRE( result.at( 5 ) == "words" );
    REQUIRE( result.at( 6 ) == "sorted" );
}

TEST_CASE( "order_by_descending" ) {
    const auto words = std::vector{ "hello"s, "world"s, "here"s, "are"s, "some"s, "sorted"s, "words"s };

    const auto result = linq::from( &words )
                            .order_by_descending( []( const std::string& word ) {
                                return word.size();
                            } )
                            .to_vector();

    REQUIRE( result.size() == 7 );
    REQUIRE( result.at( 0 ) == "sorted" );
    REQUIRE( result.at( 1 ) == "hello" );
    REQUIRE( result.at( 2 ) == "world" );
    REQUIRE( result.at( 3 ) == "words" );
    REQUIRE( result.at( 4 ) == "here" );
    REQUIRE( result.at( 5 ) == "some" );
    REQUIRE( result.at( 6 ) == "are" );
}

TEST_CASE( "then_by" ) {
    const auto words = std::vector{ "hello"s, "world"s, "here"s, "are"s, "some"s, "sorted"s, "words"s };

    const auto result = linq::from( &words )
                            .order_by_ascending( []( const std::string& word ) {
                                return word.size();
                            } )
                            .then_by(
                                []( const std::string& word ) {
                                    return word;
                                },
                                linq::sort_direction::ascending )
                            .to_vector();

    REQUIRE( result.size() == 7 );
    REQUIRE( result == std::vector{ "are"s, "here"s, "some"s, "hello"s, "words"s, "world"s, "sorted"s } );
}

TEST_CASE( "then_by_ascending" ) {
    const auto words = std::vector{ "hello"s, "world"s, "here"s, "are"s, "some"s, "sorted"s, "words"s };

    const auto result = linq::from( &words )
                            .order_by_ascending( []( const std::string& word ) {
                                return word.size();
                            } )
                            .then_by_ascending( []( const std::string& word ) {
                                return word;
                            } )
                            .to_vector();

    REQUIRE( result.size() == 7 );
    REQUIRE( result == std::vector{ "are"s, "here"s, "some"s, "hello"s, "words"s, "world"s, "sorted"s } );
}

TEST_CASE( "then_by_descending" ) {
    const auto words = std::vector{ "hello"s, "world"s, "here"s, "are"s, "some"s, "sorted"s, "words"s };

    const auto result = linq::from( &words )
                            .order_by_ascending( []( const std::string& word ) {
                                return word.size();
                            } )
                            .then_by_descending( []( const std::string& word ) {
                                return word;
                            } )
                            .to_vector();

    REQUIRE( result.size() == 7 );
    REQUIRE( result == std::vector{ "are"s, "some"s, "here"s, "world"s, "words"s, "hello"s, "sorted"s } );
}

TEST_CASE( "reverse" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4 };
    const auto result  = linq::from( &numbers ).reverse().to_vector();

    REQUIRE( result.size() == 4 );
    REQUIRE( result == std::vector{ 4, 3, 2, 1 } );
}
