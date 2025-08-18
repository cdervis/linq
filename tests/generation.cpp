#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "from_to" ) {
    SECTION( "0 to 10 with default step" ) {
        constexpr auto range = linq::from_to( 0, 10 );
        REQUIRE( range.count() == 11 );

        const auto list = range.to_vector();
        REQUIRE( list.size() == 11 );
        REQUIRE( list == std::vector{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } );
    }

    SECTION( "0 to 10 with step 2" ) {
        constexpr auto range = linq::from_to( 0, 10, 2 );
        REQUIRE( range.count() == 6 );

        const std::vector list = range.to_vector();
        REQUIRE( list.size() == 6 );
        REQUIRE( list == std::vector{ 0, 2, 4, 6, 8, 10 } );
    }

    SECTION( "0 to 10 with step 3" ) {
        constexpr auto range = linq::from_to( 0, 10, 3 );
        REQUIRE( range.count() == 4 );

        const std::vector list = range.to_vector();
        REQUIRE( list.size() == 4 );
        REQUIRE( list == std::vector{ 0, 3, 6, 9 } );
    }

    struct custom_addable {
        double value = 0.0;

        explicit custom_addable( const double value )
            : value( value ) {
        }

        bool operator==( const custom_addable& ) const = default;
        bool operator!=( const custom_addable& ) const = default;

        custom_addable& operator+=( const custom_addable& other ) {
            value += other.value;
            return *this;
        }

        bool operator<( const custom_addable& other ) const {
            return value < other.value;
        }
    };

    SECTION( "custom addable" ) {
        const auto range = linq::from_to( custom_addable{ 0 }, custom_addable{ 10 } );
        REQUIRE( range.count() == 11 );

        const auto list = range.to_vector();
        REQUIRE( list.size() == 11 );
        REQUIRE(
            list == std::vector{
                        custom_addable{ 0 },
                        custom_addable{ 1 },
                        custom_addable{ 2 },
                        custom_addable{ 3 },
                        custom_addable{ 4 },
                        custom_addable{ 5 },
                        custom_addable{ 6 },
                        custom_addable{ 7 },
                        custom_addable{ 8 },
                        custom_addable{ 9 },
                        custom_addable{ 10 } } );
    }
}

TEST_CASE( "repeat" ) {
    SECTION( "never repeat" ) {
        const auto numbers = linq::from_to( 0, 5 ).repeat( 0 ).to_vector();

        REQUIRE( numbers.size() == 6 );
        REQUIRE( numbers == std::vector{ 0, 1, 2, 3, 4, 5 } );
    }

    SECTION( "repeat once" ) {
        const auto numbers = linq::from_to( 0, 5 ).repeat( 1 ).to_vector();

        REQUIRE( numbers.size() == 12 );
        REQUIRE( numbers == std::vector{ 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5 } );
    }
}

TEST_CASE( "generate" ) {
    constexpr auto range = linq::generate( []( const size_t iteration ) {
        if ( iteration < 10 ) {
            return linq::generate_return( iteration * 2 );
        }

        return linq::generate_finish<size_t>();
    } );

    STATIC_REQUIRE( range.count() == 10 );

    const auto list = range.to_vector();

    REQUIRE( list.size() == 10 );
    REQUIRE( list == std::vector<size_t>{ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } );
}
