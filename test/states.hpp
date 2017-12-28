#ifndef STATES_HPP_
#define STATES_HPP_

#include <ostream>
#include <string>


namespace unittest
{

// Events: Start is movable, Stop is not. Both must be copyable.

struct Start
{
	Start() = default;
	Start(const Start&) = default; 
	Start(Start&&) = default;
};

struct Stop
{
	Stop() = default;
	Stop(const Stop&) = default;
	Stop(Stop&&) = delete;
};


// Both StartedPrintableState and StoppedPrintableState have method name().

struct StoppedPrintableState
{
    std::string name() const;
    auto handle(const Start&) const;
};

struct StartedPrintableState
{
	std::string name() const;
    auto handle(const Stop&) const;
};

auto StartedPrintableState::handle(const Stop&) const
{
    return StoppedPrintableState{};
}

auto StoppedPrintableState::handle(const Start&) const
{
    return StartedPrintableState{};
}

std::string StartedPrintableState::name() const
{
    return "StartedPrintableState";
}

std::string StoppedPrintableState::name() const
{
    return "StoppedPrintableState";
}



// Only StoppedPrintableState has method name().

struct StoppedNotPrintableState
{
    std::string name() const;
    auto handle(const Start&) const;
};

struct StartedNotPrintableState
{
    auto handle(const Stop&) const;
};

auto StartedNotPrintableState::handle(const Stop&) const
{
    return StoppedNotPrintableState{};
}

auto StoppedNotPrintableState::handle(const Start&) const
{
    return StartedNotPrintableState{};
}

std::string StoppedNotPrintableState::name() const
{
    return "StoppedNotPrintableState";
}


}  // namespace unittest

#endif  // STATES_HPP_