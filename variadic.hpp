#ifndef TPLM_VARIADIC_HPP_
#define TPLM_VARIADIC_HPP_

#include <cstddef>
#include <type_traits>

#include "common.hpp"
#include "variadic_detail.hpp"

namespace tplm
{


template <std::size_t N, typename... Ts>
struct get;

template <>
struct get<0ul>
{
    using type = none;
};

template <typename T, typename... Ts>
struct get<0ul, T, Ts...>
{
    using type = T;
};

template <std::size_t N, typename T, typename... Ts>
struct get<N, T, Ts...> : get<N-1, Ts...> {};

template <std::size_t N, typename... Ts>
using get_t = typename get<N, Ts...>::type;



template <typename T, typename... Ts>
struct find : std::integral_constant<std::size_t, detail::find<T, Ts...>::value>
{
    constexpr static std::size_t value = detail::find<T, Ts...>::value;
    using type = get_t<value, Ts...>;
};

template <typename T, typename... Ts>
constexpr static std::size_t find_v = find<T, Ts...>::value;

template <typename T, typename... Ts>
using find_t = typename find<T, Ts...>::type;



template <template<typename> class Predicate, typename T, typename... Ts>
struct find_if  : std::integral_constant<std::size_t, detail::find_if<Predicate, T, Ts...>::value>
{
    constexpr static std::size_t value = detail::find_if<Predicate, T, Ts...>::value;
    using type = get_t<value, T, Ts...>;
};

template <template<typename> class Predicate, typename T, typename... Ts>
constexpr static std::size_t find_if_v = find_if<Predicate, T, Ts...>::value;

template <template<typename> class Predicate, typename T, typename... Ts>
using find_if_t = typename find_if<Predicate, T, Ts...>::type;




template <template<typename...> class Predicate, typename... Ts>
struct all_of
	: std::bool_constant< detail::all_of<Predicate, Ts...>::value > {};

template <template<typename...> class Predicate, typename... Ts>
constexpr static bool all_of_v = all_of<Predicate, Ts...>::value;



template <template<typename> class Predicate, typename... Ts>
struct any_of : std::bool_constant< detail::any_of<Predicate, Ts...>::value > {};

template <template<typename> class Predicate, typename... Ts>
constexpr static bool any_of_v = any_of<Predicate, Ts...>::value;



template <template<typename> class Predicate, typename... Ts>
struct none_of : std::bool_constant< !detail::any_of<Predicate, Ts...>::value > {};

template <template<typename> class Predicate, typename... Ts>
constexpr static bool none_of_v = none_of<Predicate, Ts...>::value;


}  // namespace tplm

#endif  // TPLM_VARIADIC_HPP_
