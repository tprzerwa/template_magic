#ifndef TPLM_STATE_MACHINE_DETAIL_HPP_
#define TPLM_STATE_MACHINE_DETAIL_HPP_


#include <exception>
#include <type_traits>

#include "common.hpp"


namespace tplm
{

struct invalid_transition : std::exception {};

namespace detail
{

template <typename StateMachine, typename Event, bool B = std::is_move_constructible<Event>::value>
struct transition_handler;

template <typename StateMachine, typename Event>
struct transition_handler<StateMachine, Event, true>
{
    using result_type = void;
    StateMachine *machine_;
    Event event_;

    transition_handler(StateMachine *machine, Event&& event)
        : machine_{machine}, event_(std::forward<Event>(event)) {}

    ~transition_handler() = default;

    template <typename State>
    auto operator() (State&& state) const noexcept
        -> decltype(state.handle(event_), void())
    {
        machine_->state_ = state.handle(event_);
    }
};

template <typename StateMachine, typename Event>
struct transition_handler<StateMachine, Event, false>
{
    using result_type = void;
    StateMachine *machine_;
    const Event& event_;

    transition_handler(StateMachine *machine, const Event& event)
        : machine_{machine}, event_(event) {}

    ~transition_handler() = default;

    template <typename State>
    auto operator() (State&& state) const noexcept
        -> decltype(state.handle(event_), void())
    {
        machine_->state_ = state.handle(event_);
    }
};


template <bool B>
struct undefined_transition_handler;

template<>
struct undefined_transition_handler<true>
{
    using result_type = void;

    template <typename... Args>
    void operator() (Args && ... args) const noexcept
    {
        swallow(std::forward<Args...>(args)...);
    }
};

template<>
struct undefined_transition_handler<false>
{
    using result_type = void;

    template <typename... Args>
    void operator() (Args && ... args) const
    {
        swallow(std::forward<Args...>(args)...);
        throw invalid_transition{};
    }
};



template <bool B>
struct name_handler;

template<>
struct name_handler<true>
{
    using result_type = std::string;

    template <typename State>
    auto operator() (const State& state) const noexcept
        -> decltype(state.name(), std::string())
    {
        return state.name();
    }
};

template<>
struct name_handler<false>
{
    using result_type = std::string;

    template <typename State>
    auto operator() (const State& state) const
        ->  decltype(state.name(), std::string())
    {
        return state.name();
    }

    template <typename... Args>
    std::string operator() (Args && ... args) const
    {
        swallow(std::forward<Args...>(args)...);
        throw no_such_member{};
    }
};


}  // namespace detail
}  // namespace tplm

#endif  // TPLM_STATE_MACHINE_DETAIL_HPP_
