#ifndef TPLM_VARIADIC_DETAIL_HPP_
#define TPLM_VARIADIC_DETAIL_HPP_

#include <cstddef>
#include <type_traits>


namespace tplm
{
namespace detail
{


template <std::size_t I, typename T, typename... Us>
struct Index;

template <std::size_t I, typename T>
struct Index<I, T> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, typename T, typename... Us>
struct Index<I, T, T, Us...> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, typename T, typename U, typename... Us>
struct Index<I, T, U, Us...> : Index<I+1, T, Us...> {};




template<bool B, template<typename...> class Predicate>
struct Initial;

template <template<typename...> class Predicate>
struct Initial<false, Predicate>
{
    template <typename...>
    struct And : std::false_type {};

    template <typename... Us>
    struct Or;

    template <typename U>
    struct Or<U> : std::integral_constant<bool, Predicate<U>::value> {};

    template <typename U, typename... Us>
    struct Or<U, Us...>
        : Initial< Predicate<U>::value, Predicate >::template Or<Us...> {};
};

template <template<typename...> class Predicate>
struct Initial<true, Predicate>
{
    template <typename... Us>
    struct And;

    template <typename U>
    struct And<U> : std::integral_constant<bool, Predicate<U>::value> {};

    template <typename U, typename... Us>
    struct And<U, Us...>
        : Initial< Predicate<U>::value, Predicate >::template And<Us...> {};

    template<typename...>
    struct Or : std::true_type {};
};


}  // namespace detail
}  // namespace tplm

#endif  // TPLM_VARIADIC_DETAIL_HPP_
