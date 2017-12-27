#ifndef TPLM_STATE_MACHINE_DETAIL_HPP_
#define TPLM_STATE_MACHINE_DETAIL_HPP_


#include <exception>

#include "common.hpp"


namespace tplm
{

struct invalid_transition : std::exception {};


template <bool B>
struct undefined_transition_handler;

template<>
struct undefined_transition_handler<true>
{
    template <typename Arg>
    static void handle(Arg && arg) noexcept
    {
        swallow(std::forward<Arg>(arg));
    }
};

template<>
struct undefined_transition_handler<false>
{
    template <typename Arg>
    static void handle(Arg && arg)
    {
        swallow(std::forward<Arg>(arg));
        throw invalid_transition{};
    }
};

}  // namespace tplm

#endif  // TPLM_STATE_MACHINE_DETAIL_HPP_
