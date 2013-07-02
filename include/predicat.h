#ifndef __PREDICAT_H__
#define __PREDICAT_H__

#include "network_traits.h"

template<typename Traits>
struct node_is_active
{
    node_is_active(std::size_t num_node):
        _num_node(num_node)
    {
    }

    inline bool operator()(typename Traits::state_type const & s)
    {
        return Traits::node(s, _num_node);
    }

    private:
    std::size_t _num_node;
};

#endif
