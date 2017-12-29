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

public:

    state_machine(variant<States...> state)
        : state_{ std::move(state) } {}

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
                detail::transition_handler<state_machine, Event>(this, std::forward<Event>(event)),
                detail::undefined_transition_handler<silent_transition>{}),
            state_);
    }

    /* created only if any state has method name() */
    template <typename = typename std::enable_if<any_printable>::type>
    std::string state_name() const noexcept(states_printable)
    {
        return visit(detail::name_handler<states_printable>{}, state_);
    }

private:
    template <typename StateMachine, typename Event, bool>
    friend struct detail::transition_handler;


    variant<States...> state_;
};


}  // namespace tplm

#endif  // TPLM_STATE_MACHINE_HPP_
