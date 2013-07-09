/*!
 * \file bool_network/dynamic/matrix_model.h
 * \author Turpin Pierre
 * \brief Definition of a class representing a model of boolean network with the rule contained in a matrix
 */
#ifndef __BOOL_NETWORK_DYNAMIC_MATRIX_MODEL_H__
#define __BOOL_NETWORK_DYNAMIC_MATRIX_MODEL_H__

#include <cstddef>
#include <cstdlib>

#include "bool_network/dynamic/abstract_model.h"

namespace bn
{
    namespace dynamic
    {
        /*!
         * \class matrix_model
         * \tparam Size Size of the boolean network
         * \tparam Coef Type of coefficient contained by the matrix
         * \brief Model of a boolean network based on a matrix of transition
         *
         * The transition rules are stored in a matrix like
         * a Markov chain.
         * A node can be connected to another node is a coefficient.
         * If one node is updated, we do the sum of all the
         * coefficient of the active node connected to it.
         * If the sum is greater than a threshold, the node is activated,
         * if it's lower, it is deactivated and if it's null,
         * the node doesn't change.
         */
        template <std::size_t Size, typename Coef = float>
            class matrix_model : public abstract_model<Size>
        {
            public:
                /*!
                 * \var size
                 * \brief Size of the boolean network
                 */
                static std::size_t const size = abstract_model<Size>::size;

                /*!
                 * \typedef state_type
                 * \brief Type of a state of the machine
                 */
                typedef typename abstract_model<Size>::state_type state_type;

                /*!
                 * \typedef coef_type
                 * \brief Type contained by the matrix of transition
                 */
                typedef Coef coef_type;

                /*!
                 * \typedef matrix_type
                 * \brief Type of a matrix of transition.
                 *
                 * It's the type of the matrix. The size is (size +1) * size
                 * because there is a line for the threashold information.
                 */
                typedef coef_type matrix_type[(size + 1) * size];

                /*!
                 * \enum update
                 * \brief Enumeration of the possible modification on one node's machine
                 */
                typedef enum {activation, stase, deactivation} update;

                /*!
                 * \brief Constructor of the model
                 * \param m Matrix of transition used
                 * \param nbr_updated_node Number of node updated each step
                 * \param s Initial state of the model
                 *
                 * It's possible to have two kinds of different models.
                 * Each step, it may have more than one node to modify.
                 * So there is some different way to update the model.
                 * The first, is to choose all the modification. Each time
                 * every node are modified (if there is a modification).
                 * It's called a synchronous update.
                 * Another model can describe the same network but with a different
                 * method for choosing a node. If only one node is chosen randomly,
                 * then from one state, there are many other states. This kind of model is
                 * also non-deterministic and it's called asynchronous.
                 * It's possible to get a middle of async and sync by updating
                 * a certain amount of node. If this amount is greater than
                 * the network size, so the model is sync and deterministic.
                 */
                matrix_model(matrix_type const & m,
                        std::size_t nbr_updated_node,
                        state_type const & s = state_type()):
                    abstract_model<Size>(s),
                    _matrix(),
                    _nbr_updated_node(nbr_updated_node)
            {
                std::copy(m, m + (size + 1) * size, _matrix);
            }

                /*!
                 * \brief Return the amount of time a machine can stay static before looping.
                 * \return Minimum time the network has to stay static.
                 */
                virtual std::time_t get_min_time() const
                {
                    return 0;
                }

                /*!
                 * \brief Update the model once.
                 *
                 * Uses the sum rule on each node to determine the potential future state.
                 * Then picks some modification from the potential future state and include
                 * them in the current state to get the new.
                 */
                virtual void step()
                {
                    std::size_t list_modified[size] = {0};
                    std::size_t size_modified = 0;

                    // Copy of the current state
                    state_type s(abstract_model<Size>::_state);

                    for(std::size_t i = 0 ; i < size ; i++)
                    {
                        // Determines the life of the node
                        update u = rule(i);
                        if(u == activation)
                            s.set(i, true);
                        else if(u == deactivation)
                            s.set(i, false);

                        // If there is a move, we store it
                        if(s.test(i) != abstract_model<Size>::_state.test(i))
                        {
                            list_modified[size_modified] = i;
                            size_modified++;
                        }
                    }

                    // Pick some modification from the copy of the state
                    pick_modification(s, list_modified, size_modified);
                }

                /*!
                 * \brief Pick some modification of the potential future state to the current state
                 * \param s Potential future state containing all the modification
                 * \param list_modified List of th index of all the modification done
                 * \param size_modified Size of the list
                 *
                 * Get _nbr_updated_node times modification in the potential future state to set it
                 * in the current state to get the new one.
                 * The choice is random, so if the number of modification taken is lower than the
                 * number of nodes, the result is not deterministic.
                 *
                 * \see _nbr_updated_node
                 *
                 * \warning The current random generator is std::rand from cstdlib.
                 */
                virtual void pick_modification(state_type const & s,
                        std::size_t list_modified[size],
                        std::size_t size_modified)
                {
                    // Get the number of modified node
                    std::size_t nbr_modif =
                        std::min(_nbr_updated_node, size_modified);
                    std::size_t min = nbr_modif;
                    while(nbr_modif > 0)
                    {
                        // Pick one modification randomly
                        std::size_t picked = std::rand() % (size_modified - (min - nbr_modif));

                        abstract_model<Size>::_state.set(list_modified[picked],
                                s.test(list_modified[picked]));

                        // Remove the chosen modification from the list to avoid
                        // the same modification is done twice
                        std::copy(list_modified + picked + 1, list_modified + size, list_modified + picked);

                        nbr_modif--;
                    }
                }

            protected:
                /*!
                 * \brief Get the modification of the given node
                 * \return Type of modification
                 *
                 * Do the sum of all coefficient of active node attached to
                 * those given. If the result is strictly positive, it's an
                 * activation, if it's strictly negative, it's a deactivation.
                 * Else the node stays the same.
                 */
                virtual update rule(std::size_t n)
                {
                    coef_type sum = 0;
                    for(std::size_t i = 0 ; i < size ; i++)
                    {
                        if(abstract_model<Size>::_state.test(i))
                            sum += _matrix[n * (size + 1) + i + 1];
                    }

                    if(sum > _matrix[n * (size + 1)])
                        return activation;
                    if(sum < _matrix[n * (size + 1)])
                        return deactivation;
                    return stase;
                }

            protected:
                /*!
                 * \var _matrix
                 * \brief Matrix of transition.
                 */
                matrix_type _matrix;

                /*!
                 * \var _nbr_updated_node
                 * \brief Amount of node updated each step.
                 */
                std::size_t _nbr_updated_node;
        };
    }
}

#endif
