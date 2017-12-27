#ifndef STATES_HPP_
#define STATES_HPP_

#include <ostream>
#include <string>


struct Start {};
struct Stop {};


struct State
{
    virtual std::string name() const = 0;
    virtual ~State() = default;
};


struct Started;

struct Stopped : public State
{
    std::string name() const override;
    auto handle(Start) const;
};

struct Started : public State
{
    std::string name() const override;
    auto handle(Stop) const;
};

auto Started::handle(Stop) const
{
    return Stopped{};
}

auto Stopped::handle(Start) const
{
    return Started{};
}

std::string Started::name() const
{
    return "Started";
}

std::string Stopped::name() const
{
    return "Stopped";
}


std::ostream& operator<<(std::ostream& os, const State& state)
{
    return os << state.name();
}

#endif  // STATES_HPP_