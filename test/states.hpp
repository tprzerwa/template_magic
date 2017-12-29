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
	Stop(Stop&&) = default;
};


// Both StartedPrintableState and StoppedPrintableState have method name().

struct StartedPrintableState;

struct StoppedPrintableState
{
	StoppedPrintableState() = default;
	StoppedPrintableState(const StoppedPrintableState&) = default;
	// StoppedPrintableState(StoppedPrintableState&&) = default;
    std::string name() const;
    StartedPrintableState handle(const Start&) const;
};

struct StartedPrintableState
{
	StartedPrintableState() = default;
	StartedPrintableState(const StartedPrintableState&) = default;
	// StartedPrintableState(StartedPrintableState&&) = default;
	std::string name() const;
    StoppedPrintableState handle(const Stop&) const;
};

StoppedPrintableState StartedPrintableState::handle(const Stop&) const
{
    return StoppedPrintableState{};
}

StartedPrintableState StoppedPrintableState::handle(const Start&) const
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

struct StartedNotPrintableState;

struct StoppedNotPrintableState
{
    std::string name() const;
    StartedNotPrintableState handle(const Start&) const;
};

struct StartedNotPrintableState
{
    StoppedNotPrintableState handle(const Stop&) const;
};

StoppedNotPrintableState StartedNotPrintableState::handle(const Stop&) const
{
    return StoppedNotPrintableState{};
}

StartedNotPrintableState StoppedNotPrintableState::handle(const Start&) const
{
    return StartedNotPrintableState{};
}

std::string StoppedNotPrintableState::name() const
{
    return "StoppedNotPrintableState";
}


}  // namespace unittest

#endif  // STATES_HPP_