/*!
 * \file bool_network/dynamic/abstract_model.h
 * \author Turpin Pierre
 * \brief Definition of a class representing an abstract model of boolean network
 */
#ifndef __BOOL_NETWORK_DYNAMIC_ABSTRACT_MODEL_H__
#define __BOOL_NETWORK_DYNAMIC_ABSTRACT_MODEL_H__

#include <cstddef>
#include <bitset>
#include <ctime>

namespace bn
{
    namespace dynamic
    {
        /*!
         * \class abstract_model
         * \tparam Size Number of nodes there is in the boolean network
         * \brief Abstract model of a boolean network
         */
        template <std::size_t Size>
            class abstract_model
            {
                public:
                    /*!
                     * \var size
                     * \brief Size of the boolean network
                     */
                    static std::size_t const size = Size;

                    /*!
                     * \typedef state_type
                     * \brief Type of container used to store the state of the network.
                     */
                    typedef std::bitset<size> state_type;

                    /*!
                     * \brief Constructor of the model
                     * \param s Initial state of the model
                     */
                    abstract_model(state_type const & s = state_type()):
                        _state(s)
                {
                }

                    /*!
                     * \brief Return the current state of the network
                     * \return Current state
                     */
                    state_type const & get_state() const
                    {
                        return _state;
                    }

                    /*!
                     * \brief Return the amount of time a machine can stay static before looping.
                     * \return Minimum time the network has to stay static.
                     */
                    virtual std::time_t get_min_time() const = 0;

                    /*!
                     * \brief Change the current state
                     * \param s New state of the model
                     */
                    void set_state(state_type const & s)
                    {
                        _state = s;
                    }

                    /*!
                     * \brief Update the model once
                     *
                     * It's the function used by the machine to update.
                     * This function updates a part of the boolean network
                     * by following some rules.
                     * Each step, the state of the model is calculated again by doing
                     * new_state = rule(old_state) where the rule is the transition function.
                     */
                    virtual void step() = 0;

                    /*!
                     * \brief Comparison between two states of model
                     *
                     * Useful if we want to store our model in a BST (binary search tree)
                     */
                    bool operator<(abstract_model const & other) const
                    {
                        return _state.to_ulong() < other._state.to_ulong();
                    }

                protected:
                    /*!
                     * \var _state
                     * \brief Current state of the model.
                     */
                    state_type _state;
            };
    }
}

#endif
