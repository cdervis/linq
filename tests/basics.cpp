#include "datatypes.hpp"
#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

static const auto general_people = std::vector<person>{
    { .name = "P1", .age = 20 },
    { .name = "P2", .age = 21 },
    { .name = "P3", .age = 22 },
    { .name = "P4", .age = 10 },
    { .name = "P5", .age = -10 },
    { .name = "P6", .age = 391 },
};

TEST_CASE( "basic" ) {
    SECTION( "direct link" ) {
        auto lines = std::vector<std::string>();

        for ( const auto& [name, age] : linq::from( &general_people ) ) {
            lines.push_back( name + ": " + std::to_string( age ) );
        }

        REQUIRE( lines.size() == 6 );
        REQUIRE( lines.at( 0 ) == "P1: 20" );
        REQUIRE( lines.at( 1 ) == "P2: 21" );
        REQUIRE( lines.at( 2 ) == "P3: 22" );
        REQUIRE( lines.at( 3 ) == "P4: 10" );
        REQUIRE( lines.at( 4 ) == "P5: -10" );
        REQUIRE( lines.at( 5 ) == "P6: 391" );
    }
}

TEST_CASE( "begin() count" ) {
    {
        const auto nums = mock_vector{ 1, 2, 3, 4 };

        const auto query = linq::from( &nums );
        REQUIRE( nums.begin_call_count == 0 );

        for ( const auto& e : query ) {
            std::ignore = e;
        }

        REQUIRE( nums.begin_call_count == 1 );
    }

    {
        const auto nums = mock_vector{ 1, 2, 3, 4 };

        const auto query = linq::from( &nums ).where( []( const int num ) {
            return num > 0;
        } );

        REQUIRE( nums.begin_call_count == 0 );

        for ( const auto& e : query ) {
            std::ignore = e;
        }

        REQUIRE( nums.begin_call_count == 1 );
    }
}

TEST_CASE( "item mutability" ) {
    SECTION( "with const container, non-const query" ) {
        const auto nums  = std::vector{ 1, 2, 3, 4 };
        const auto query = linq::from( &nums );

        for ( auto&& item : query ) {
            std::ignore = item;
            static_assert(
                std::is_const_v<std::remove_reference_t<decltype( item )>>,
                "expected the item to be immutable" );
        }
    }

    SECTION( "with const container, const query" ) {
        const auto nums  = std::vector{ 1, 2, 3, 4 };
        const auto query = linq::from( &nums );

        for ( auto&& item : query ) {
            std::ignore = item;
            static_assert(
                std::is_const_v<std::remove_reference_t<decltype( item )>>,
                "expected the item to be immutable" );
        }
    }

    SECTION( "with non-const container, const query" ) {
        const auto nums  = std::vector{ 1, 2, 3, 4 };
        const auto query = linq::from( &nums );

        for ( auto&& item : query ) {
            std::ignore = item;
            static_assert(
                std::is_const_v<std::remove_reference_t<decltype( item )>>,
                "expected the item to be immutable" );
        }
    }

    SECTION( "with non-const container, non-const query" ) {
        const auto nums  = std::vector{ 1, 2, 3, 4 };
        const auto query = linq::from( &nums );

        for ( auto&& item : query ) {
            std::ignore = item;
            static_assert(
                std::is_const_v<std::remove_reference_t<decltype( item )>>,
                "expected the item to be immutable" );
        }
    }

    // now with linq::from_mutable()

    SECTION( "const query" ) {
        auto       nums  = std::vector{ 1, 2, 3, 4 };
        const auto query = linq::from_mutable( &nums );

        for ( auto&& item : query ) {
            std::ignore = item;
            static_assert(
                !std::is_const_v<std::remove_reference_t<decltype( item )>>,
                "expected the item to be mutable" );
        }
    }

    SECTION( "non-const query" ) {
        auto nums = std::vector{ 1, 2, 3, 4 };

        // ReSharper disable once CppLocalVariableMayBeConst
        // ReSharper disable once CppTooWideScopeInitStatement
        auto query = linq::from_mutable( &nums );

        for ( auto&& item : query ) {
            std::ignore = item;
            static_assert(
                !std::is_const_v<std::remove_reference_t<decltype( item )>>,
                "expected the item to be mutable" );
        }
    }
}

TEST_CASE( "query copying" ) {
    const auto nums = std::vector{ 1, 2, 3, 4 };

    auto query1 = linq::from( &nums );

    auto nums_ptrs = std::vector<const int*>();
    for ( const auto& num : query1 ) {
        nums_ptrs.push_back( std::addressof( num ) );
    }

    REQUIRE( nums_ptrs.size() == 4 );
    REQUIRE( nums_ptrs.at( 0 ) == std::addressof( nums.at( 0 ) ) );
    REQUIRE( nums_ptrs.at( 1 ) == std::addressof( nums.at( 1 ) ) );
    REQUIRE( nums_ptrs.at( 2 ) == std::addressof( nums.at( 2 ) ) );
    REQUIRE( nums_ptrs.at( 3 ) == std::addressof( nums.at( 3 ) ) );

    auto query2 = query1;

    REQUIRE( nums_ptrs.size() == 4 );
    REQUIRE( nums_ptrs.at( 0 ) == std::addressof( nums.at( 0 ) ) );
    REQUIRE( nums_ptrs.at( 1 ) == std::addressof( nums.at( 1 ) ) );
    REQUIRE( nums_ptrs.at( 2 ) == std::addressof( nums.at( 2 ) ) );
    REQUIRE( nums_ptrs.at( 3 ) == std::addressof( nums.at( 3 ) ) );

    for ( const auto& num : query2 ) {
        nums_ptrs.push_back( std::addressof( num ) );
    }

    REQUIRE( nums_ptrs.size() == 8 );
    REQUIRE( nums_ptrs.at( 0 ) == std::addressof( nums.at( 0 ) ) );
    REQUIRE( nums_ptrs.at( 1 ) == std::addressof( nums.at( 1 ) ) );
    REQUIRE( nums_ptrs.at( 2 ) == std::addressof( nums.at( 2 ) ) );
    REQUIRE( nums_ptrs.at( 3 ) == std::addressof( nums.at( 3 ) ) );
    REQUIRE( nums_ptrs.at( 4 ) == std::addressof( nums.at( 0 ) ) );
    REQUIRE( nums_ptrs.at( 5 ) == std::addressof( nums.at( 1 ) ) );
    REQUIRE( nums_ptrs.at( 6 ) == std::addressof( nums.at( 2 ) ) );
    REQUIRE( nums_ptrs.at( 7 ) == std::addressof( nums.at( 3 ) ) );
}

TEST_CASE( "from(initializer_list)" ) {
    auto lines = std::vector<std::string>();

    for ( auto num : linq::from( { 1, 2, 3 } ) ) {
        lines.push_back( std::to_string( num ) );
    }

    REQUIRE( lines.size() == 3 );
    REQUIRE( lines.at( 0 ) == "1" );
    REQUIRE( lines.at( 1 ) == "2" );
    REQUIRE( lines.at( 2 ) == "3" );

    // initializer_list query to std::vector
    lines = linq::from( { 1, 2, 3 } ).select_to_string().to_vector();

    REQUIRE( lines.size() == 3 );
    REQUIRE( lines.at( 0 ) == "1" );
    REQUIRE( lines.at( 1 ) == "2" );
    REQUIRE( lines.at( 2 ) == "3" );
}
