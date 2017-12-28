#ifndef TPLM_STATE_MACHINE_HPP_
#define TPLM_STATE_MACHINE_HPP_

#include <exception>
#include <string>
#include <variant>

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

public:

    state_machine(std::variant<States...> state)
        : state_{ std::move(state) }
    {
    }

    template <typename State>
    bool in_state() const noexcept
    {
        return state_.index() == tplm::find<State, States...>::value;
    }

    template <typename Event>
    void handle(Event&& event) noexcept(silent_transition)
    {
        std::visit(
            make_overloaded(
                detail::transition_handler<state_machine, Event>(this, std::forward<Event>(event)),
                detail::undefined_transition_handler<silent_transition>{}),
            state_);
    }

    std::string state_name() const noexcept(states_printable)
    {
        return std::visit(detail::name_handler<states_printable>{}, state_);
    }

private:
    template <typename StateMachine, typename Event>
    friend struct detail::transition_handler;

    std::variant<States...> state_;
};


}  // namespace tplm

#endif  // TPLM_STATE_MACHINE_HPP_
