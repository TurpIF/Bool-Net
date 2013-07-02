#ifndef __FONCTOR_COEF_H__
#define __FONCTOR_COEF_H__

typedef signed int coef_type;

template <std::size_t N>
struct fonctor_traits<coef_type, N>
{
    typedef network_traits<bool, N> net_traits;

    typedef coef_type return_type;
    typedef typename net_traits::state_type argument_type;

    static const return_type ReturnNothing = net_traits::DoNothing;
};

template <typename Fonctor>
struct to_bool
{
    typedef fonctor_traits<bool, Fonctor::traits::net_traits::size> traits;
    typedef typename traits::return_type return_type;
    typedef typename traits::argument_type argument_type;

    to_bool(Fonctor const & f = Fonctor(), coef_type const & seuil = 0):
        _fonctor(f),
        _seuil(seuil)
    {
    }

    inline return_type operator()(argument_type const & s)
    {
        coef_type c = _fonctor(s);
        if(c > _seuil)
            return traits::Active;
        else if(c < _seuil)
            return traits::Desactive;
        return traits::ReturnNothing;
    }

    private:
    Fonctor _fonctor;
    const coef_type _seuil;
};

template<typename Fonctor>
to_bool<Fonctor> make_to_bool(Fonctor const & f = Fonctor(), coef_type seuil = 0)
{ return to_bool<Fonctor>(f, seuil); }

namespace fonctor_coef
{
    template <typename Traits>
        struct set_value
        {
            typedef Traits traits;
            typedef typename traits::return_type return_type;
            typedef typename traits::argument_type argument_type;

            set_value(coef_type const & value):
                _value(value)
            {
            }

            inline return_type operator()(argument_type const &)
            {
                return _value;
            }

            private:
            const coef_type _value;
        };

    template <typename Traits, typename Pred>
        struct set_value_if
        {
            typedef Traits traits;
            typedef typename traits::return_type return_type;
            typedef typename traits::argument_type argument_type;

            set_value_if(coef_type const & value, Pred const & p = Pred()):
                _predicat(p),
                _value(value)
            {
            }

            inline return_type operator()(argument_type const &s)
            {
                if(_predicat(s))
                {
                    return _value;
                }
                return traits::ReturnNothing;
            }

            private:
            Pred _predicat;
            coef_type _value;
        };

    template <typename Traits>
        set_value<Traits> make_set_value(coef_type const & value)
        { return set_value<Traits>(value); }

    template <typename Traits, typename Pred>
        set_value_if<Traits, Pred> make_set_value_if(coef_type const & value, Pred const & p = Pred())
        { return set_value_if<Traits, Pred>(value, p); }

    template <typename Traits>
        set_value_if<Traits, node_is_active<typename Traits::net_traits> > make_set_value_if_node(std::size_t num_node, coef_type const & value)
        { return make_set_value_if<Traits>(value, node_is_active<typename Traits::net_traits>(num_node)); }

    template <typename Traits>
        delay<set_value<Traits> > make_degradation(std::size_t time, coef_type const & value)
        {
            return make_delay(time, true, make_set_value<Traits>(value));
        }

    //template <size_t N, coef_type Value, std::size_t NumNode, typename Traits = fonctor_traits<coef_type, N> >
    //    struct set_value_if_node
    //    { typedef typename set_value_if<N, Value, node_is_active<N, NumNode, typename Traits::net_traits>, Traits>::type type; };

    //template <size_t N, coef_type Value, std::size_t Time, typename Traits = fonctor_traits<coef_type, N> >
    //    struct degradation
    //    { typedef typename delay<set_value<N, Value, Traits>, Time, true>::type type; };
}

#endif
