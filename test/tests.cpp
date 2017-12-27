#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include "../sfinae.hpp"
#include "../variadic.hpp"

#include <type_traits>


namespace unittest
{

template <typename T> struct AlwaysTrue : std::true_type {};

template <typename T> struct AlwaysFalse : std::false_type {};

template <typename T> struct IsInt : std::is_same<T, int> {};

struct Named { std::string name() const noexcept { return "Name"; } };

struct FakeIntNamed { int name() const noexcept { return 0; } };

struct FakeVoidNamed { void name() const noexcept {} };

struct UnNamed {};


}  // namespace test


using namespace unittest;
using namespace tplm;


TEST_CASE("TEST get")
{
    REQUIRE( std::is_same<get_t<0ul, float, int, int, double, bool>, float>::value );

    REQUIRE( std::is_same<get_t<1ul, float, int, int, double, bool>, int>::value );

    REQUIRE( std::is_same<get_t<3ul, float, int, int, double, bool>, double>::value );

    REQUIRE( std::is_same<get_t<4ul, float, int, int, double, bool>, bool>::value );

    REQUIRE( std::is_same<get_t<5ul, float, int, int, double, bool>, none>::value );
}

TEST_CASE("TEST find")
{
    REQUIRE( find_v<float, float, int, int, double, bool> == 0ul );
    REQUIRE( std::is_same<find_t<float, float, int, int, double, bool>, float>::value );

    REQUIRE( find_v<int, float, int, int, double, bool> == 1ul );
    REQUIRE( std::is_same<find_t<int, float, int, int, double, bool>, int>::value );

    REQUIRE( find_v<double, float, int, int, double, bool> == 3ul );
    REQUIRE( std::is_same<find_t<double, float, int, int, double, bool>, double>::value );

    REQUIRE( find_v<bool, float, int, int, double, bool> == 4ul );
    REQUIRE( std::is_same<find_t<bool, float, int, int, double, bool>, bool>::value );

    REQUIRE( find_v<unsigned, float, int, int, double, bool> == 5ul );
    REQUIRE( std::is_same<find_t<unsigned, float, int, int, double, bool>, none>::value );
}

TEST_CASE("TEST all_of")
{
    REQUIRE( all_of<AlwaysTrue, int>::value );
    REQUIRE( all_of<AlwaysTrue, int, float>::value );
    REQUIRE( all_of<AlwaysTrue, int, float, bool>::value );

    REQUIRE( !all_of<AlwaysFalse, int>::value );
    REQUIRE( !all_of<AlwaysFalse, int, float>::value );
    REQUIRE( !all_of<AlwaysFalse, int, float, bool>::value );

    REQUIRE( all_of<IsInt, int>::value );
    REQUIRE( !all_of<IsInt, int, float>::value );
    REQUIRE( !all_of<IsInt, int, float, bool>::value );
}

TEST_CASE("TEST any_of")
{
    REQUIRE( all_of<AlwaysTrue, int>::value );
    REQUIRE( all_of<AlwaysTrue, int, float>::value );
    REQUIRE( all_of<AlwaysTrue, int, float, bool>::value );

    REQUIRE( !all_of<AlwaysFalse, int>::value );
    REQUIRE( !all_of<AlwaysFalse, int, float>::value );
    REQUIRE( !all_of<AlwaysFalse, int, float, bool>::value );

    REQUIRE( all_of<IsInt, int>::value );
    REQUIRE( all_of<IsInt, int, float>::value );
    REQUIRE( all_of<IsInt, int, float, bool>::value );
}

TEST_CASE("TEST none_of")
{
    REQUIRE( !all_of<AlwaysTrue, int>::value );
    REQUIRE( !all_of<AlwaysTrue, int, float>::value );
    REQUIRE( !all_of<AlwaysTrue, int, float, bool>::value );

    REQUIRE( all_of<AlwaysFalse, int>::value );
    REQUIRE( all_of<AlwaysFalse, int, float>::value );
    REQUIRE( all_of<AlwaysFalse, int, float, bool>::value );

    REQUIRE( !all_of<IsInt, int>::value );
    REQUIRE( !all_of<IsInt, int, float>::value );
    REQUIRE( !all_of<IsInt, int, float, bool>::value );
}

TEST_CASE("TEST has_method_name")
{
    REQUIRE( has_method_name<Named>::value );
    REQUIRE( !has_method_name<UnNamed>::value );
    REQUIRE( !has_method_name<FakeIntNamed>::value );
    REQUIRE( !has_method_name<FakeVoidNamed>::value );
}

