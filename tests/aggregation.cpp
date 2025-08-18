#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

using namespace std::string_literals;

TEST_CASE( "aggregate" ) {
    constexpr auto numbers = std::array{ 1, 2, 3, 4 };

    SECTION( "0 with summing lambda" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 0, []( int a, int b ) {
            return a + b;
        } );

        STATIC_REQUIRE( std::is_same_v<std::remove_cvref_t<decltype( result )>, int> );
        STATIC_REQUIRE( result == 10 );
    }

    SECTION( "4 with std::plus" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 4, std::plus() );
        STATIC_REQUIRE( result == 14 );
    }

    SECTION( "0 with no-op" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 0, []( int, int ) {
            return 0;
        } );
        STATIC_REQUIRE( result == 0 );
    }

    SECTION( "5 with zero-return" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 5, []( int, int ) {
            return 0;
        } );
        STATIC_REQUIRE( result == 0 );
    }

    SECTION( "5 with self-return" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 5, []( int, int ) {
            return 5;
        } );
        STATIC_REQUIRE( result == 5 );
    }

    SECTION( "0 with std::multiplies" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 0, std::multiplies() );
        STATIC_REQUIRE( result == 0 );
    }

    SECTION( "1 with std::multiplies" ) {
        constexpr auto result = linq::from( &numbers ).aggregate( 1, std::multiplies() );
        STATIC_REQUIRE( result == 24 );
    }
}

TEST_CASE( "reduce" ) {
    constexpr auto numbers = std::array{ 1, 2, 3, 4 };

    SECTION( "with std::multiplies" ) {
        constexpr auto result = linq::from( &numbers ).reduce( std::multiplies() );
        STATIC_REQUIRE( result == 24 );
    }

    SECTION( "with std::plus" ) {
        constexpr auto result = linq::from( &numbers ).reduce( std::plus() );

        STATIC_REQUIRE( std::is_same_v<std::remove_cvref_t<decltype( result )>, int> );
        STATIC_REQUIRE( result == 10 );
    }

    SECTION( "with summing lambda" ) {
        constexpr auto result = linq::from( &numbers ).reduce( []( int a, int b ) {
            return a + b;
        } );

        STATIC_REQUIRE( std::is_same_v<std::remove_cvref_t<decltype( result )>, int> );
        STATIC_REQUIRE( result == 10 );
    }

    SECTION( "with zero-returning lambda" ) {
        constexpr auto result = linq::from( &numbers ).reduce( []( int, int ) {
            return 0;
        } );
        STATIC_REQUIRE( result == 0 );
    }

    SECTION( "string concatenation" ) {
        constexpr auto letters = std::array{ 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd' };

        const auto words = linq::from( &letters ).select_to_string().reduce( std::plus() );

        REQUIRE( words == "hello world" );
    }
}

TEST_CASE( "average" ) {
    constexpr auto ints = std::array{ 1, 2, 3, 4 };

    {
        constexpr auto avg = linq::from( &ints ).average().value();
        STATIC_REQUIRE( std::is_same_v<std::remove_const_t<decltype( avg )>, long double> );
        STATIC_REQUIRE( avg == ( 1.0 + 2.0 + 3.0 + 4.0 ) / 4.0 );
    }

    // Average with custom type
    struct value {
        int num{};

        constexpr value operator+( const value& other ) const {
            return { .num = num + other.num };
        }

        constexpr value operator/( const size_t other ) const {
            return { .num = static_cast<int>( num / other ) };
        }

        constexpr value& operator+=( const value& other ) {
            num += other.num;
            return *this;
        }

        constexpr bool operator==( const value& other ) const {
            return num == other.num;
        }
    };

    {
        constexpr auto vals = std::array{ value{ 1 }, value{ 2 }, value{ 3 }, value{ 4 } };
        constexpr auto avg  = linq::from( &vals ).average().value();
        STATIC_REQUIRE( avg == value{ 2 } );
    }
}

TEST_CASE( "count" ) {
    const auto str = "hello world!"s;

    const auto number_of_chars = linq::from( &str ).count();
    const auto number_of_ls    = linq::from( &str ).count( []( char ch ) {
        return ch == 'l';
    } );

    REQUIRE( number_of_chars == 12 );
    REQUIRE( number_of_ls == 3 );
}


TEST_CASE( "max" ) {
    constexpr auto ints = std::array{ 1, -2, 3, -4, 5, -6, 7, -8, 9 };

    STATIC_REQUIRE( linq::from( &ints ).max() == 9 );

    STATIC_REQUIRE(
        linq::from( &ints )
            .where( []( const int value ) {
                return value >= 3;
            } )
            .max() == 9 );

    STATIC_REQUIRE( !linq::from( &ints )
                         .where( []( const int value ) {
                             return value < -10;
                         } )
                         .max()
                         .has_value() );

    constexpr std::array floats{ -0.5f, 0.25f, 0.75f, 1.0f, 5.0f, -20.0f, 3.25f };

    STATIC_REQUIRE( linq::from( &floats ).max() == 5.0f );

    STATIC_REQUIRE( !linq::from( &floats )
                         .where( []( const float value ) {
                             return value > 10;
                         } )
                         .max()
                         .has_value() );

    STATIC_REQUIRE(
        linq::from( &floats )
            .where( []( const float value ) {
                return value < 8;
            } )
            .max() == 5.0f );

    constexpr auto doubles = std::array{ -0.5, 0.25, 0.75, 1.0, 5.0, -20.0, 3.25 };

    STATIC_REQUIRE( linq::from( &doubles ).max() == 5.0 );

    STATIC_REQUIRE( !linq::from( &doubles )
                         .where( []( const double value ) {
                             return value > 10;
                         } )
                         .max()
                         .has_value() );
    STATIC_REQUIRE(
        linq::from( &doubles )
            .where( []( const double value ) {
                return value < 8;
            } )
            .max() == 5.0 );
}

TEST_CASE( "min" ) {
    constexpr auto ints = std::array{ 1, -2, 3, -4, 5, -6, 7, -8, 9 };

    STATIC_REQUIRE( linq::from( &ints ).min() == -8 );
    STATIC_REQUIRE(
        linq::from( &ints )
            .where( []( const int value ) {
                return value >= 3;
            } )
            .min() == 3 );

    STATIC_REQUIRE( !linq::from( &ints )
                         .where( []( const int value ) {
                             return value < -10;
                         } )
                         .min()
                         .has_value() );

    constexpr auto floats = std::array{ -0.5f, 0.25f, 0.75f, 1.0f, 5.0f, -20.0f, 3.25f };

    STATIC_REQUIRE( linq::from( &floats ).min() == -20.0f );
    STATIC_REQUIRE( !linq::from( &floats )
                         .where( []( const float value ) {
                             return value > 10;
                         } )
                         .min()
                         .has_value() );
    STATIC_REQUIRE(
        linq::from( &floats )
            .where( []( const float value ) {
                return value > 1;
            } )
            .min() == 3.25f );

    constexpr auto doubles = std::array{ -0.5, 0.25, 0.75, 1.0, 5.0, -20.0, 3.25 };

    STATIC_REQUIRE( linq::from( &doubles ).min() == -20.0 );

    STATIC_REQUIRE( !linq::from( &doubles )
                         .where( []( const double value ) {
                             return value > 20;
                         } )
                         .min()
                         .has_value() );

    STATIC_REQUIRE(
        linq::from( &doubles )
            .where( []( const double value ) {
                return value > 1;
            } )
            .min() == 3.25 );
}

TEST_CASE( "sum" ) {
    const auto numbers = std::vector{ 1, 2, 3, 4 };
    const auto sum     = linq::from( &numbers ).sum();
    REQUIRE( sum.value() == 10 );
}
