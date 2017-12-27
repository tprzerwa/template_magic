#define CATCH_CONFIG_MAIN


#include "catch.hpp"

#include <string>
#include <type_traits>

#include "../common.hpp"
#include "../sfinae.hpp"
#include "../variadic.hpp"


namespace unittest
{

template <typename T> struct AlwaysTrue : std::true_type {};

template <typename T> struct AlwaysFalse : std::false_type {};

template <typename T> struct IsInt : std::is_same<T, int> {};

template <typename T> struct IsFloat : std::is_same<T, float> {};

template <typename T> struct IsDouble : std::is_same<T, double> {};

template <typename T> struct IsBool : std::is_same<T, bool> {};

template <typename T> struct IsString : std::is_same<T, std::string> {};

struct Named { std::string name() const noexcept { return "Name"; } };

struct FakeIntNamed { int name() const noexcept { return 0; } };

struct FakeVoidNamed { void name() const noexcept {} };

struct UnNamed {};

}  // namespace test


using namespace unittest;
using namespace tplm;


TEST_CASE("TEST if_expr")
{
    REQUIRE( std::is_same<if_expr_t<true, int, double>, int>::value );
    REQUIRE( !std::is_same<if_expr_t<true, int, double>, double>::value );
    REQUIRE( std::is_same<if_expr_t<false, int, double>, double>::value );

    REQUIRE( if_expr<true, int, double>::value );
    REQUIRE( !if_expr<false, int, double>::value );
}


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
    REQUIRE( find<float, float, int, int, double, bool>::value == 0ul );
    REQUIRE( std::is_same<find_t<float, float, int, int, double, bool>, float>::value );

    REQUIRE( find<int, float, int, int, double, bool>::value == 1ul );
    REQUIRE( std::is_same<find_t<int, float, int, int, double, bool>, int>::value );

    REQUIRE( find<double, float, int, int, double, bool>::value == 3ul );
    REQUIRE( std::is_same<find_t<double, float, int, int, double, bool>, double>::value );

    REQUIRE( find<bool, float, int, int, double, bool>::value == 4ul );
    REQUIRE( std::is_same<find_t<bool, float, int, int, double, bool>, bool>::value );

    REQUIRE( find<unsigned, float, int, int, double, bool>::value == 5ul );
    REQUIRE( std::is_same<find_t<unsigned, float, int, int, double, bool>, none>::value );
}

TEST_CASE("TEST find_if")
{
    REQUIRE( find_if<AlwaysTrue, float, int, int, double, bool>::value == 0ul );
    REQUIRE( std::is_same<find_if_t<AlwaysTrue, float, int, int, double, bool>, float>::value );

    REQUIRE( find_if<AlwaysFalse, float, int, int, double, bool>::value == 5ul );
    REQUIRE( std::is_same<find_if_t<AlwaysFalse, float, int, int, double, bool>, none>::value );

    REQUIRE( find_if<IsInt, float, int, int, double, bool>::value == 1ul );
    REQUIRE( std::is_same<find_if_t<IsInt, float, int, int, double, bool>, int>::value );

    REQUIRE( find_if<IsFloat, float, int, int, double, bool>::value == 0ul );
    REQUIRE( std::is_same<find_if_t<IsFloat, float, int, int, double, bool>, float>::value );

    REQUIRE( find_if<IsDouble, float, int, int, double, bool>::value == 3ul );
    REQUIRE( std::is_same<find_if_t<IsDouble, float, int, int, double, bool>, double>::value );

    REQUIRE( find_if<IsBool, float, int, int, double, bool>::value == 4ul );
    REQUIRE( std::is_same<find_if_t<IsBool, float, int, int, double, bool>, bool>::value );

    REQUIRE( find_if<IsString, float, int, int, double, bool>::value == 5ul );
    REQUIRE( std::is_same<find_if_t<IsString, float, int, int, double, bool>, none>::value );
}

TEST_CASE("TEST all_of")
{
    REQUIRE( all_of<AlwaysTrue, int>::value );
    REQUIRE( all_of<AlwaysTrue, int, float>::value );
    REQUIRE( all_of<AlwaysTrue, int, float, bool>::value );

    REQUIRE( !all_of<AlwaysFalse, int>::value );
    REQUIRE( !all_of<AlwaysFalse, int, float>::value );
    REQUIRE( !all_of<AlwaysFalse, int, float, bool>::value );

    REQUIRE( all_of<IsInt, int>::value);
    REQUIRE( !all_of<IsInt, int, float>::value );
    REQUIRE( !all_of<IsInt, int, float, bool>::value );

    REQUIRE( !all_of<IsFloat, int>::value );
    REQUIRE( !all_of<IsFloat, int, float>::value );
    REQUIRE( !all_of<IsFloat, int, float, bool>::value );

    REQUIRE( !all_of<IsString, int>::value );
    REQUIRE( !all_of<IsString, int, float>::value );
    REQUIRE( !all_of<IsString, int, float, bool>::value );
}

TEST_CASE("TEST any_of")
{
    REQUIRE( any_of<AlwaysTrue, int>::value );
    REQUIRE( any_of<AlwaysTrue, int, float>::value );
    REQUIRE( any_of<AlwaysTrue, int, float, bool>::value );

    REQUIRE( !any_of<AlwaysFalse, int>::value );
    REQUIRE( !any_of<AlwaysFalse, int, float>::value );
    REQUIRE( !any_of<AlwaysFalse, int, float, bool>::value );

    REQUIRE( any_of<IsInt, int>::value );
    REQUIRE( any_of<IsInt, int, float>::value );
    REQUIRE( any_of<IsInt, int, float, bool>::value );

    REQUIRE( !any_of<IsFloat, int>::value );
    REQUIRE( any_of<IsFloat, int, float>::value );
    REQUIRE( any_of<IsFloat, int, float, bool>::value );

    REQUIRE( !any_of<IsString, int>::value );
    REQUIRE( !any_of<IsString, int, float>::value );
    REQUIRE( !any_of<IsString, int, float, bool>::value );
}

TEST_CASE("TEST none_of")
{
    REQUIRE( !none_of<AlwaysTrue, int>::value );
    REQUIRE( !none_of<AlwaysTrue, int, float>::value );
    REQUIRE( !none_of<AlwaysTrue, int, float, bool>::value );

    REQUIRE( none_of<AlwaysFalse, int>::value );
    REQUIRE( none_of<AlwaysFalse, int, float>::value );
    REQUIRE( none_of<AlwaysFalse, int, float, bool>::value );

    REQUIRE( !none_of<IsInt, int>::value );
    REQUIRE( !none_of<IsInt, int, float>::value );
    REQUIRE( !none_of<IsInt, int, float, bool>::value );

    REQUIRE( none_of<IsFloat, int>::value );
    REQUIRE( !none_of<IsFloat, int, float>::value );
    REQUIRE( !none_of<IsFloat, int, float, bool>::value );

    REQUIRE( none_of<IsString, int>::value );
    REQUIRE( none_of<IsString, int, float>::value );
    REQUIRE( none_of<IsString, int, float, bool>::value );
}

TEST_CASE("TEST has_method_name")
{
    REQUIRE( has_method_name<Named>::value );
    REQUIRE( !has_method_name<UnNamed>::value );
    REQUIRE( !has_method_name<FakeIntNamed>::value );
    REQUIRE( !has_method_name<FakeVoidNamed>::value );
}

