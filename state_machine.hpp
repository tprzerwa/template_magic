#ifndef TPLM_STATE_MACHINE_HPP_
#define TPLM_STATE_MACHINE_HPP_

#include <exception>
#include <string>

#include "sfinae.hpp"
#include "state_machine_detail.hpp"
#include "variadic.hpp"
#include "variant.hpp"


namespace tplm
{

struct silent_on_bad_transition
{
    constexpr static const bool safe = true;
};

struct throw_on_bad_transition
{
    constexpr static const bool safe = false;
};


struct invalid_transition;



template <typename TransitionPolicy, typename... States>
class state_machine
{
constexpr static bool silent_transition = TransitionPolicy::safe;
constexpr static bool states_printable = all_of<has_method_name, States...>::value;
constexpr static bool any_printable = any_of<has_method_name, States...>::value;

template <typename Event>
using transition_handler = detail::transition_handler<state_machine, Event>;
using undefined_handler = detail::undefined_transition_handler<silent_transition>;
using name_handler = detail::name_handler<states_printable>;

public:

    state_machine(variant<States...> state)
        : state_{ std::move(state) }
        , undefined_handler_{}
        , name_handler_{}
    {
    }

    // state_machine() = default;
    // state_machine(const state_machine&) = delete;
    // state_machine(state_machine&&) = delete;
    // state_machine& operator= (const state_machine&) = delete;
    // state_machine& operator= (state_machine&&) = delete;
    // ~state_machine() = default;


    template <typename State>
    bool in_state() const noexcept
    {
        return state_.index() == tplm::find<State, States...>::value;
    }

    template <typename Event>
    void handle(Event&& event) noexcept(silent_transition)
    {
        visit(
            make_overloaded(
                transition_handler<Event>(this, std::forward<Event>(event)),
                undefined_handler_),
            state_);
    }

    /* created only if any state has method name() */
    template <typename = typename std::enable_if<any_printable>::type>
    std::string state_name() const noexcept(states_printable)
    {
        return visit(name_handler_, state_);
    }

private:
    template <typename StateMachine, typename Event, bool>
    friend struct detail::transition_handler;


    variant<States...> state_;
    undefined_handler undefined_handler_;
    name_handler name_handler_;
};


}  // namespace tplm

#endif  // TPLM_STATE_MACHINE_HPP_
