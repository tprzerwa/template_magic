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
public:

    state_machine(std::variant<States...> state)
        : state_{ std::move(state) }
    {
    }

    template <typename State>
    bool in_state() const noexcept
    {
        return state_.index() == tplm::find_v<State, States...>;
    }

    template <typename Event>
    void handle(Event&& event) noexcept(TransitionPolicy::safe)
    {
        std::visit(
            tplm::make_overloaded(
                [&](auto&& state) noexcept
                    -> decltype(state.handle(std::forward<Event>(event)), void())
                    {
                        state_ = state.handle(std::forward<Event>(event));
                    },
                [](auto&&... args)
                    {
                        handle_undefined_transition(args...);
                    }),
            state_);
    }

    auto state_name() const
        -> decltype(all_of_v<has_method_name, States...>, std::string())
    {
        return std::visit(
            make_overloaded(
                [&](auto&& state) -> decltype(state.name(), std::string())
                    {
                        return state.name();
                    },
                [](auto&&... args)
                    {
                        swallow(args...);
                        throw no_such_member{};
                    }),
            state_);
    }

private:

    template <typename... Args>
    constexpr static void handle_undefined_transition(Args && ... args) noexcept(TransitionPolicy::safe)
    {
        if constexpr(!TransitionPolicy::safe)
        { 
            throw invalid_transition{};
        }
        swallow(args...);
    }

    std::variant<States...> state_;
};


}  // namespace tplm

#endif  // TPLM_STATE_MACHINE_HPP_
