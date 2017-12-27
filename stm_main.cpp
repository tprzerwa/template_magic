#include <iostream>
#include <string>
#include <type_traits>
#include <variant>

#include "states.hpp"
#include "state_machine.hpp"

struct A
{
    std::string name() { return "A"; }
};

struct B
{
    std::string name() { return "B"; }
};


int main()
{
    auto sm = tplm::state_machine<tplm::silent_on_bad_transition, Started, Stopped>(Stopped{});
    std::cout << sm.state_name() << std::endl;
    sm.handle(Start{});
    std::cout << sm.state_name() << std::endl;
    sm.handle(Stop{});
    std::cout << sm.state_name() << std::endl;
    std::cout << tplm::has_method_name<A>::value << std::endl;
    std::cout << tplm::has_method_name<B>::value << std::endl;

    return 0;
}