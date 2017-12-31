#ifndef TPLM_VARIANT_HPP_
#define TPLM_VARIANT_HPP_


#include <type_traits>

#include "compatibility.hpp"


#if BOOST_NEEDED
  #include <boost/variant.hpp>
#else
  #include <variant>
#endif


namespace tplm
{

#if BOOST_NEEDED

    template <typename... Ts>
    struct variant
    {
        boost::variant<Ts...> value_;

        template <typename... Args>
        variant(Args && ... args) : value_(std::forward<Args...>(args)...) {}

        template <typename Arg>
        variant& operator= (Arg && arg)
        {
            value_ = std::forward<Arg>(arg);
            return *this;
        }

        template <typename Arg>
        bool operator== (Arg && arg) const
        {
            return value_ == std::forward<Arg>(arg);
        }

        constexpr std::size_t index() const noexcept
        {
            return value_.which();
        }
    };

    template <typename Visitor, typename Visitable>
    auto visit(Visitor& visitor, Visitable& visitable)
        -> decltype(boost::apply_visitor(visitor, visitable.value_))
    {
        return boost::apply_visitor(visitor, visitable.value_);
    }

#else  // __cplusplus > 201402L  // std == C++17

    template <typename... Ts>
    using variant = std::variant<Ts...>;

    template <typename... Args>
    auto visit(Args && ... args)
        -> decltype(std::visit(std::forward<Args...>(args)...))
    {
        return std::visit(std::forward<Args...>(args)...);
    }

#endif



template <typename... Ts>
struct overloaded;

template <typename T>
struct overloaded<T> : public std::remove_reference<T>::type
{
    using U = typename std::remove_reference<T>::type;

    #if BOOST_NEEDED
    using result_type = typename U::result_type;
    #endif

    overloaded(T && t)
        : U{ std::forward<T>(t) }
    {
    }

    using U::operator();
};

template <typename T, typename... Ts>
struct overloaded<T, Ts...> : public std::remove_reference<T>::type, public overloaded<Ts...>
{
    using U = typename std::remove_reference<T>::type;

    #if BOOST_NEEDED && C_PLUS_PLUS_11
    using result_type = typename overloaded<Ts...>::result_type;
    #endif

    overloaded(T && t, Ts && ... ts)
        : U{ std::forward<T>(t) }
        , overloaded<Ts...>{ std::forward<Ts>(ts)... }
    {
    }

    using U::operator();
    using overloaded<Ts...>::operator();
};


template <typename... Ts>
overloaded<Ts...> make_overloaded(Ts && ... ts)
{
    return overloaded<Ts...>( std::forward<Ts>(ts)... );
}

}  // namespace tplm

#endif  // TPLM_VARIANT_HPP_
