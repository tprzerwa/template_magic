#ifndef TPLM_COMMON_HPP_
#define TPLM_COMMON_HPP_


namespace tplm
{


struct some {};


struct none {};



struct swallow
{
    template <typename... Ts> swallow (Ts && ...) {}
};



template <bool B, typename T, typename U>
struct if_expr;

template <typename T, typename U>
struct if_expr<true, T, U>
{
    constexpr static bool value = true;
    using type = T;
};

template <typename T, typename U>
struct if_expr<false, T, U>
{
    constexpr static bool value = true;
    using type = U;
};

template <bool B, typename T, typename U>
using if_expr_t = typename if_expr<B, T, U>::type;

template <bool B, typename T, typename U>
constexpr static bool if_expr_v = if_expr<B, T, U>::value;



struct no_such_member : public std::exception {};



}  // namespace tplm

#endif  // TPLM_COMMON_HPP_
