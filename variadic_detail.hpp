#ifndef TPLM_VARIADIC_DETAIL_HPP_
#define TPLM_VARIADIC_DETAIL_HPP_

#include <cstddef>
#include <type_traits>


namespace tplm
{
namespace detail
{


template <std::size_t I, typename T, typename... Us>
struct find_impl;

template <std::size_t I, typename T>
struct find_impl<I, T> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, typename T, typename... Us>
struct find_impl<I, T, T, Us...> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, typename T, typename U, typename... Us>
struct find_impl<I, T, U, Us...> : find_impl<I+1, T, Us...> {};

template <typename T, typename... Us>
using find = find_impl<0ul, T, Us...>;



template <bool B, std::size_t I, template<typename...> class Predicate, typename... Us>
struct find_if_impl;

template <std::size_t I, template<typename...> class Predicate>
struct find_if_impl<true, I, Predicate> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, template<typename...> class Predicate>
struct find_if_impl<false, I, Predicate> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, template<typename...> class Predicate, typename... Us>
struct find_if_impl<true, I, Predicate, Us...> : std::integral_constant<std::size_t, I> {};

template <std::size_t I, template<typename...> class Predicate, typename U, typename... Us>
struct find_if_impl<false, I, Predicate, U, Us...>
    : find_if_impl<Predicate<U>::value, I+1, Predicate, Us...> {};

template <template<typename...> class Predicate, typename U, typename... Us>
using find_if = find_if_impl<Predicate<U>::value, 0ul, Predicate, U, Us...>;



template <bool B, template<typename...> class Predicate, typename... Ts>
struct all_of_impl;

template <template<typename...> class Predicate>
struct all_of_impl<true, Predicate> : std::true_type {};

template <template<typename...> class Predicate, typename T, typename... Ts>
struct all_of_impl<true, Predicate, T, Ts...> : all_of_impl<Predicate<T>::value, Predicate, Ts...> {};

template <template<typename...> class Predicate, typename... Ts>
struct all_of_impl<false, Predicate, Ts...> : std::false_type {};

template <template<typename...> class Predicate, typename... Ts>
using all_of = all_of_impl<true, Predicate, Ts...>;



template <bool B, template<typename...> class Predicate, typename... Ts>
struct any_of_impl;

template <template<typename...> class Predicate>
struct any_of_impl<false, Predicate> : std::false_type {};

template <template<typename...> class Predicate, typename T, typename... Ts>
struct any_of_impl<false, Predicate, T, Ts...> : any_of_impl<Predicate<T>::value, Predicate, Ts...> {};

template <template<typename...> class Predicate, typename... Ts>
struct any_of_impl<true, Predicate, Ts...> : std::true_type {};

template <template<typename...> class Predicate, typename... Ts>
using any_of = any_of_impl<false, Predicate, Ts...>;





}  // namespace detail
}  // namespace tplm

#endif  // TPLM_VARIADIC_DETAIL_HPP_
