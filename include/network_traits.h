#ifndef __NETWORK_TRAITS_H__
#define __NETWORK_TRAITS_H__

#include <cstddef>
#include <bitset>

// Specification of the mode of the model.
// If the mode is async then, each node is updated one by one.
// It means that from a state of the network, if more than one node can be updated,
// then, as only one node changes, there is different path to take.
// In this case, we have to define a function to pick a path.
// Generally, this function is a random function with a uniform distribution.
// This mode with this type of function is non-determinist.
// If the node is sync then all node are updated at the same time.
// This mode is determinist.
//// static const bool async_mode = true / false;

// The function to pick a path in a list
// Return the picked path
// Needed only if the mode is async
//// static inline const graph_type & pick_path(const graph_type & graph, const std::vector<graph_type> & path_list);

// Basic structure of the different models' traits
// May contains all type and static constante useful for a network
// like the data type he contains or the kind of operation he does
// to genere the graph and the rules
// N is the number of node there is in the graph
template <typename networkT, std::size_t N>
struct network_traits
{
    // Definition of the size of the model.
    // It's the number of different node in the network.
    typedef std::size_t size_type;
    static const size_type size = N;

    // Definition of the node and set of nodes.
    typedef networkT node_type;
    typedef node_type state_type[size];
    typedef node_type & ref_node_type;

    // The method to get one node in a state
    // num_node must be greater or equal to 0 and lower to size
    static inline node_type node(const state_type & state, const size_type & num_node)
    { return state[num_node]; }

    // The method to get a reference to one node in a state
    // num_node must be greater or equal to 0 and lower to size
    static inline ref_node_type node(state_type & state, const size_type & num_node)
    { return state[num_node]; }
};

// Bool specification for boolean network
template <std::size_t N>
struct network_traits<bool, N>
{
    // Definition of the size of the model.
    // It's the number of different node in the network.
    typedef std::size_t size_type;
    static const size_type size = N;

    // Definition of the modification it can be done of a node.
    typedef enum {DoNothing, Active, Desactive} update_type;

    // Definition of the node and set of nodes.
    typedef std::bitset<size> state_type;
    typedef bool node_type;
    typedef typename state_type::reference ref_node_type;

    // The method to get one node in a state
    // num_node must be greater or equal to 0 and lower to size
    static inline node_type node(const state_type & state, const size_type & num_node)
    { return state[num_node]; }

    // The method to get a reference to one node in a state
    // num_node must be greater or equal to 0 and lower to size
    static inline ref_node_type node(state_type & state, const size_type & num_node)
    { return state[num_node]; }
};

#endif
