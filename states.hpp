#ifndef STATES_HPP_
#define STATES_HPP_

#include <ostream>
#include <string>


struct Start {};
struct Stop {};



struct Started;

struct Stopped
{
    std::string name() const;
    auto handle(const Start&) const;
};

struct Started
{
    // std::string name() const;
    auto handle(const Stop&) const;
};

auto Started::handle(const Stop&) const
{
    return Stopped{};
}

auto Stopped::handle(const Start&) const
{
    return Started{};
}

// std::string Started::name() const
// {
//     return "Started";
// }

std::string Stopped::name() const
{
    return "Stopped";
}


// std::ostream& operator<<(std::ostream& os, const State& state)
// {
//     return os << state.name();
// }

#endif  // STATES_HPP_