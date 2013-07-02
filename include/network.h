#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "network_traits.h"

template <std::size_t N, typename traits = network_traits<bool, N> >
class network
{
    public:
        typedef typename traits::state_type state_type;

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

        // The state machine contains every time a state.
        // After one step, it's possible for a machine to have
        // to chose between differente futur states.
        // This function choose the futur state of the machine
        // by the list of the different ways to update.
        // Return the graph transformed by the modification chose.
        // More than one modification can be chose.

        // The update rule of the state machine
        virtual void update() = 0;

    private:
        state_type _state;
};

#endif
