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




template<bool B>
struct Initial;

template<>
struct Initial<false>
{
    template<template<typename> class Predicate, typename...>
    struct And : std::false_type {};

    template<template<typename> class Predicate, typename... Us>
    struct Or;

    template<template<typename> class Predicate, typename U>
    struct Or<Predicate, U> : std::integral_constant<bool, Predicate<U>::value> {};

    template<template<typename> class Predicate, typename U, typename... Us>
    struct Or<Predicate, U, Us...>
        : Initial< Predicate<U>::value >::template Or<Predicate, Us...> {};
};

template<>
struct Initial<true>
{
    template<template<typename> class Predicate, typename... Us>
    struct And;

    template<template<typename> class Predicate, typename U>
    struct And<Predicate, U> : std::integral_constant<bool, Predicate<U>::value> {};

    template<template<typename> class Predicate, typename U, typename... Us>
    struct And<Predicate, U, Us...>
        : Initial< Predicate<U>::value >::template And<Predicate, Us...> {};

    template<template<typename> class Predicate, typename...>
    struct Or : std::true_type {};
};


}  // namespace detail
}  // namespace tplm

#endif  // TPLM_VARIADIC_DETAIL_HPP_
