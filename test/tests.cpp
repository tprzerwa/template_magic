#define CATCH_CONFIG_MAIN


#include "catch.hpp"

#include <string>
#include <type_traits>

#include "../sfinae.hpp"
#include "../variadic.hpp"


namespace unittest
{

template <typename T> struct AlwaysTrue : std::true_type {};

template <typename T> struct AlwaysFalse : std::false_type {};

template <typename T> struct IsInt : std::is_same<T, int> {};

template <typename T> struct IsFloat : std::is_same<T, float> {};

template <typename T> struct IsDouble : std::is_same<T, float> {};

template <typename T> struct IsBool : std::is_same<T, bool> {};

template <typename T> struct IsString : std::is_same<T, std::string> {};

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

TEST_CASE("TEST find_if")
{
    REQUIRE( find_if_v<AlwaysTrue, float, int, int, double, bool> == 0ul );
    REQUIRE( std::is_same<find_if_t<AlwaysTrue, float, int, int, double, bool>, float>::value );

    REQUIRE( find_if_v<AlwaysFalse, float, int, int, double, bool> == 5ul );
    REQUIRE( std::is_same<find_if_t<AlwaysFalse, float, int, int, double, bool>, none>::value );

    REQUIRE( find_if_v<IsInt, float, int, int, double, bool> == 1ul );
    REQUIRE( std::is_same<find_if_t<IsInt, float, int, int, double, bool>, int>::value );

    REQUIRE( find_if_v<IsFloat, float, int, int, double, bool> == 0ul );
    REQUIRE( std::is_same<find_if_t<IsFloat, float, int, int, double, bool>, float>::value );

    REQUIRE( find_if_v<IsDouble, float, int, int, double, bool> == 3ul );
    REQUIRE( std::is_same<find_if_t<IsDouble, float, int, int, double, bool>, double>::value );

    REQUIRE( find_if_v<IsBool, float, int, int, double, bool> == 4ul );
    REQUIRE( std::is_same<find_if_t<IsBool, float, int, int, double, bool>, bool>::value );

    REQUIRE( find_if_v<IsString, float, int, int, double, bool> == 5ul );
    REQUIRE( std::is_same<find_if_t<IsString, float, int, int, double, bool>, none>::value );
}

TEST_CASE("TEST all_of")
{
    REQUIRE( all_of_v<AlwaysTrue, int> );
    REQUIRE( all_of_v<AlwaysTrue, int, float> );
    REQUIRE( all_of_v<AlwaysTrue, int, float, bool> );

    REQUIRE( !all_of_v<AlwaysFalse, int> );
    REQUIRE( !all_of_v<AlwaysFalse, int, float> );
    REQUIRE( !all_of_v<AlwaysFalse, int, float, bool> );

    REQUIRE( all_of_v<IsInt, int> );
    REQUIRE( !all_of_v<IsInt, int, float> );
    REQUIRE( !all_of_v<IsInt, int, float, bool> );

    REQUIRE( !all_of_v<IsFloat, int> );
    REQUIRE( !all_of_v<IsFloat, int, float> );
    REQUIRE( !all_of_v<IsFloat, int, float, bool> );

    REQUIRE( !all_of_v<IsString, int> );
    REQUIRE( !all_of_v<IsString, int, float> );
    REQUIRE( !all_of_v<IsString, int, float, bool> );
}

TEST_CASE("TEST any_of")
{
    REQUIRE( any_of_v<AlwaysTrue, int> );
    REQUIRE( any_of_v<AlwaysTrue, int, float> );
    REQUIRE( any_of_v<AlwaysTrue, int, float, bool> );

    REQUIRE( !any_of_v<AlwaysFalse, int> );
    REQUIRE( !any_of_v<AlwaysFalse, int, float> );
    REQUIRE( !any_of_v<AlwaysFalse, int, float, bool> );

    REQUIRE( any_of_v<IsInt, int> );
    REQUIRE( any_of_v<IsInt, int, float> );
    REQUIRE( any_of_v<IsInt, int, float, bool> );

    REQUIRE( !any_of_v<IsFloat, int> );
    REQUIRE( any_of_v<IsFloat, int, float> );
    REQUIRE( any_of_v<IsFloat, int, float, bool> );

    REQUIRE( !any_of_v<IsString, int> );
    REQUIRE( !any_of_v<IsString, int, float> );
    REQUIRE( !any_of_v<IsString, int, float, bool> );
}

TEST_CASE("TEST none_of")
{
    REQUIRE( !none_of_v<AlwaysTrue, int> );
    REQUIRE( !none_of_v<AlwaysTrue, int, float> );
    REQUIRE( !none_of_v<AlwaysTrue, int, float, bool> );

    REQUIRE( none_of_v<AlwaysFalse, int> );
    REQUIRE( none_of_v<AlwaysFalse, int, float> );
    REQUIRE( none_of_v<AlwaysFalse, int, float, bool> );

    REQUIRE( !none_of_v<IsInt, int> );
    REQUIRE( !none_of_v<IsInt, int, float> );
    REQUIRE( !none_of_v<IsInt, int, float, bool> );

    REQUIRE( none_of_v<IsFloat, int> );
    REQUIRE( !none_of_v<IsFloat, int, float> );
    REQUIRE( !none_of_v<IsFloat, int, float, bool> );

    REQUIRE( none_of_v<IsString, int> );
    REQUIRE( none_of_v<IsString, int, float> );
    REQUIRE( none_of_v<IsString, int, float, bool> );
}

TEST_CASE("TEST has_method_name")
{
    REQUIRE( has_method_name<Named>::value );
    REQUIRE( !has_method_name<UnNamed>::value );
    REQUIRE( !has_method_name<FakeIntNamed>::value );
    REQUIRE( !has_method_name<FakeVoidNamed>::value );
}

