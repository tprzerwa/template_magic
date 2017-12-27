#ifndef TPLM_COMMON_HPP_
#define TPLM_COMMON_HPP_


#include <type_traits>


namespace tplm
{


struct some {};


struct none {};



struct swallow
{
    template <typename... Ts> swallow (Ts && ...) {}
};



struct no_such_member : public std::exception {};



template <bool B, typename T, typename U>
struct if_expr;

template <typename T, typename U>
struct if_expr<true, T, U> : std::true_type
{
    using type = T;
};

template <typename T, typename U>
struct if_expr<false, T, U> : std::false_type
{
    using type = U;
};

template <bool B, typename T, typename U>
using if_expr_t = typename if_expr<B, T, U>::type;


#if __cplusplus >= 201402L

template <bool B, typename T, typename U>
constexpr static bool if_expr_v = if_expr<B, T, U>::value;

#endif



}  // namespace tplm

#endif  // TPLM_COMMON_HPP_
