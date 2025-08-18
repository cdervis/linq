#include <catch2/catch_test_macros.hpp>
#include <linq.hpp>

TEST_CASE( "append" ) {
    SECTION( "simple append of two ranges" ) {
        auto nums1 = std::vector{ 1, 2, 3, 4 };
        auto nums2 = std::vector{ 5, 6, 7, 8 };

        auto query1 = linq::from( &nums1 );
        auto query2 = linq::from( &nums2 );
        auto query3 = query1.append( query2 );

        auto all_nums = query3.to_vector();

        REQUIRE( all_nums.size() == 8 );
        REQUIRE( all_nums.at( 0 ) == 1 );
        REQUIRE( all_nums.at( 1 ) == 2 );
        REQUIRE( all_nums.at( 2 ) == 3 );
        REQUIRE( all_nums.at( 3 ) == 4 );
        REQUIRE( all_nums.at( 4 ) == 5 );
        REQUIRE( all_nums.at( 5 ) == 6 );
        REQUIRE( all_nums.at( 6 ) == 7 );
        REQUIRE( all_nums.at( 7 ) == 8 );

        nums1.push_back( 9 );
        nums2.push_back( 10 );

        all_nums = query3.to_vector();

        REQUIRE( all_nums.size() == 10 );
        REQUIRE( all_nums.at( 0 ) == 1 );
        REQUIRE( all_nums.at( 1 ) == 2 );
        REQUIRE( all_nums.at( 2 ) == 3 );
        REQUIRE( all_nums.at( 3 ) == 4 );
        REQUIRE( all_nums.at( 4 ) == 9 );
        REQUIRE( all_nums.at( 5 ) == 5 );
        REQUIRE( all_nums.at( 6 ) == 6 );
        REQUIRE( all_nums.at( 7 ) == 7 );
        REQUIRE( all_nums.at( 8 ) == 8 );
        REQUIRE( all_nums.at( 9 ) == 10 );
    }
}
