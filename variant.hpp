#ifndef TPLM_VARIANT_HPP_
#define TPLM_VARIANT_HPP_

#if __cplusplus <= 201402L
  #include <boost/variant.hpp>
#else
  #include <variant>
#endif


namespace tplm
{

#if __cplusplus <= 201402L  //  std <= C++14 

    template <typename... Ts>
    struct variant
    {
        boost::variant<Ts...> value_;

        template <typename Arg>
        variant(Arg && arg) : value_(std::forward<Arg>(arg)) {}

        template <typename Arg>
        variant& operator= (Arg && arg)
        {
            value_ = std::forward<Arg>(arg);
            return *this; 
        }

        constexpr std::size_t index() const noexcept
        {
            return value_.which();
        }

        boost::variant<Ts...>& boost_cast()
        {
            return static_cast<boost::variant<Ts...>&>(*this);
        }
    };

    template <typename Visitor, typename Variant>
    auto visit(Visitor && vis, Variant& var)
        -> decltype(boost::apply_visitor(std::forward<Visitor>(vis), var.value_))
    {
        return boost::apply_visitor(std::forward<Visitor>(vis), var.value_);
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
struct overloaded<T> : public T
{
    overloaded(T && t)
        : T{ std::forward<T>(t) }
    {
    }

    using T::operator();
};

template <typename T, typename... Ts>
struct overloaded<T, Ts...> : public T, public overloaded<Ts...>
{
    overloaded(T && t, Ts && ... ts)
        : T{ std::forward<T>(t) }
        , overloaded<Ts...>{ std::forward<Ts>(ts)... }
    {
    }

    using T::operator();
    using overloaded<Ts...>::operator();
};


template <typename... Ts>
overloaded<Ts...> make_overloaded(Ts && ... ts)
{
    return overloaded<Ts...>( std::forward<Ts>(ts)... );
}

}  // namespace tplm

#endif  // TPLM_VARIANT_HPP_
