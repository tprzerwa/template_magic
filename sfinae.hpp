#ifndef TPLM_SFINAE_HPP_
#define TPLM_SFINAE_HPP_


#include <exception>
#include <utility>


namespace tplm
{


template <typename T, typename = std::string>
struct has_method_name
{
    constexpr static bool value = false;
};


template <typename T>
struct has_method_name<T, decltype(std::declval<T>().name())>
{
    constexpr static bool value = true;
};



}  // namespace tplm

#endif  // STM_DETAIL_HPP_
