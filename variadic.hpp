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
struct find : std::integral_constant<std::size_t, detail::find_impl<0ul, T, Ts...>::value>
{
    constexpr static std::size_t value = detail::find_impl<0ul, T, Ts...>::value;
    using type = get_t<value, Ts...>;
};

template <typename T, typename... Ts>
constexpr static std::size_t find_v = find<T, Ts...>::value;

template <typename T, typename... Ts>
using find_t = typename find<T, Ts...>::type;



// template <template<typename> class Predicate, typename... Ts>
// struct find_if
// {
//     constexpr static std::size_t value = detail::IndexIf<Predicate, Ts..., none>::value;
//     using type = if_type_t<(value == sizeof(Ts...)), none, get_t<value, Ts...>>;
// };




template <template<typename...> class Predicate, typename... Ts>
struct all_of
	: std::bool_constant< detail::all_of_impl<true, Predicate, Ts...>::value > {};

template <template<typename...> class Predicate, typename... Ts>
constexpr static bool all_of_v = all_of<Predicate, Ts...>::value;



template <template<typename> class Predicate, typename... Ts>
struct any_of
	: std::bool_constant< detail::any_of_impl<false, Predicate, Ts...>::value > {};

template <template<typename> class Predicate, typename... Ts>
constexpr static bool any_of_v = any_of<Predicate, Ts...>::value;



template <template<typename> class Predicate, typename... Ts>
struct none_of : std::bool_constant< !any_of_v<Predicate, Ts...> > {};

template <template<typename> class Predicate, typename... Ts>
constexpr static bool anone_of_v = none_of<Predicate, Ts...>::value;


}  // namespace tplm

#endif  // TPLM_VARIADIC_HPP_
