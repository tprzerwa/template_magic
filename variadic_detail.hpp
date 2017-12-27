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



template <bool B, template<typename...> class Predicate, typename... Ts>
struct all_of_impl;

template <template<typename...> class Predicate>
struct all_of_impl<true, Predicate> : std::true_type {};

template <template<typename...> class Predicate, typename T, typename... Ts>
struct all_of_impl<true, Predicate, T, Ts...> : all_of_impl<Predicate<T>::value, Predicate, Ts...> {};

template <template<typename...> class Predicate, typename... Ts>
struct all_of_impl<false, Predicate, Ts...> : std::false_type {};



template <bool B, template<typename...> class Predicate, typename... Ts>
struct any_of_impl;

template <template<typename...> class Predicate>
struct any_of_impl<false, Predicate> : std::false_type {};

template <template<typename...> class Predicate, typename T, typename... Ts>
struct any_of_impl<false, Predicate, T, Ts...> : any_of_impl<Predicate<T>::value, Predicate, Ts...> {};

template <template<typename...> class Predicate, typename... Ts>
struct any_of_impl<true, Predicate, Ts...> : std::true_type {};





}  // namespace detail
}  // namespace tplm

#endif  // TPLM_VARIADIC_DETAIL_HPP_
