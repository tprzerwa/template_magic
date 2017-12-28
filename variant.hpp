#ifndef TPLM_VARIANT_HPP_
#define TPLM_VARIANT_HPP_


namespace tplm
{

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
