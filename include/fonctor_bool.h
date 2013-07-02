#ifndef __FONCTOR_BOOL__
#define __FONCTOR_BOOL__

#include "network_traits.h"
#include "fonctor_generic.h"
#include "predicat.h"

template <std::size_t N>
struct fonctor_traits<bool, N>
{
    typedef network_traits<bool, N> net_traits;

    typedef typename net_traits::update_type return_type;
    typedef typename net_traits::state_type argument_type;

    static const return_type ReturnNothing = net_traits::DoNothing;
    static const return_type Active = net_traits::Active;
    static const return_type Desactive = net_traits::Desactive;
};

namespace fonctor_bool
{
    template <typename Traits>
        struct set_value
        {
            typedef Traits traits;
            typedef typename traits::return_type return_type;
            typedef typename traits::argument_type argument_type;

            set_value(bool value):
                _value(value)
            {
            }

            inline return_type operator()(argument_type const &s)
            {
                if(_value)
                    return traits::Active;
                return traits::Desactive;
            }

            private:
            bool _value;
        };

    template <typename Traits, typename Pred>
        struct set_value_if
        {
            typedef Traits traits;
            typedef typename traits::return_type return_type;
            typedef typename traits::argument_type argument_type;

            set_value_if(bool value, Pred const & p = Pred()):
                _predicat(p),
                _value(value)
            {
            }

            inline return_type operator()(argument_type const &s)
            {
                if(_predicat(s))
                {
                    if(_value)
                        return traits::Active;
                    return traits::Desactive;
                }
                return traits::ReturnNothing;
            }

            private:
            Pred _predicat;
            bool _value;
        };

    template<typename Traits>
        set_value<Traits> make_set_value(bool value)
        { return set_value<Traits>(value); }

    template<typename Traits, typename Pred>
        set_value_if<Traits, Pred> make_set_value_if(bool value, Pred const & p = Pred())
        { return set_value_if<Traits, Pred>(value, p); }

    template<typename Traits>
        set_value<Traits> make_activator()
        { return make_set_value<Traits>(true); }

    template<typename Traits>
        set_value<Traits> make_desactivator()
        { return make_set_value<Traits>(false); }

    template<typename Traits, typename Pred>
        set_value_if<Traits, Pred> make_activator_if(Pred const & p = Pred())
        { return make_set_value_if<Traits>(true, p); }

    template<typename Traits, typename Pred>
        set_value_if<Traits, Pred> make_desactivator_if(Pred const & p = Pred())
        { return make_set_value_if<Traits>(false, p); }

    template<typename Traits, typename Pred>
        set_value_if<Traits, node_is_active<typename Traits::net_traits> > make_activator_if_node(std::size_t num_node)
        { return make_activator_if<Traits>(node_is_active<typename Traits::net_traits>(num_node)); }

    template<typename Traits, typename Pred>
        set_value_if<Traits, node_is_active<typename Traits::net_traits> > make_desactivator_if_node(std::size_t num_node)
        { return make_desactivator_if<Traits>(node_is_active<typename Traits::net_traits>(num_node)); }

    //template <size_t N, typename Traits = fonctor_traits<bool, N> >
    //    struct activator
    //    { typedef typename set_value<N, true, Traits>::type type; };

    //template <size_t N, typename Pred, typename Traits = fonctor_traits<bool, N> >
    //    struct activator_if
    //    { typedef typename set_value_if<N, true, Pred, Traits>::type type; };

    //template <size_t N, std::size_t NumNode, typename Traits = fonctor_traits<bool, N> >
    //    struct activator_if_node
    //    { typedef typename activator_if<N, node_is_active<N, NumNode, typename Traits::net_traits>, Traits>::type type; };

    //template <size_t N, typename Traits = fonctor_traits<bool, N> >
    //    struct desactivator
    //    { typedef typename set_value<N, true, Traits>::type type; };

    //template <size_t N, typename Pred, typename Traits = fonctor_traits<bool, N> >
    //    struct desactivator_if
    //    { typedef typename set_value_if<N, true, Pred, Traits>::type type; };

    //template <size_t N, std::size_t NumNode, typename Traits = fonctor_traits<bool, N> >
    //    struct desactivator_if_node
    //    { typedef typename desactivator_if<N, node_is_active<N, NumNode, typename Traits::net_traits>, Traits>::type type; };
}

#endif
