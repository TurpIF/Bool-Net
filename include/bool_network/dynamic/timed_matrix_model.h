/*!
 * \file bool_network/dynamic/timed_matrix_model.h
 * \author Turpin Pierre
 * \brief Definition of a class representing a model of boolean network with the rule (using the time) contained in a matrix
 *
 * Definition of a specialization of the base class matrix_model.
 * This one let use a matrix to perform a model transformation
 * by using the time as a retard on the original effect attempted.
 */
#ifndef __BOOL_NETWORK_DYNAMIC_TIMED_MATRIX_MODEL_H__
#define __BOOL_NETWORK_DYNAMIC_TIMED_MATRIX_MODEL_H__

#include "bool_network/dynamic/matrix_model.h"

namespace bn
{
    namespace dynamic
    {
        /*!
         * \struct timed_coef
         * \brief Matrix's coefficient with a time retard on the effect.
         */
        struct timed_coef
        {
            /*!
             * \typedef float_type
             * \brief Used float for the time_coef
             */
            typedef float float_type;

            /*!
             * \brief Constructor of a timed coefficient
             * \param coef The coefficient
             * \param time_min The retard the effect has
             * \param reset_time Indicates if the model has to clear on not the timer after one effect done.
             */
            timed_coef(float_type coef = 0, std::time_t time_min = 0, bool reset_time = true):
                coef(coef),
                time(0),
                time_min(time_min),
                reset_time(reset_time)
            {
            }

            /*!
             * \var coef
             * \brief Coefficient
             */
            float_type coef;

            /*!
             * \var time
             * \brief Local time of the effect.
             */
            std::time_t time;

            /*!
             * \var time_min
             * \brief Restard's time of the effect.
             */
            std::time_t time_min;

            /*!
             * \var reset_time;
             * \brief Indicates is the model has to reset the time after an effect done.
             */
            bool reset_time;
        };

        template <std::size_t Size>
            class matrix_model<Size, timed_coef> : public abstract_model<Size>
            {
                public:
                    /*!
                     * \var size
                     * \brief The size of the boolean network
                     */
                    static std::size_t const size = abstract_model<Size>::size;

                    /*!
                     * \typedef state_type
                     * \brief The type of a state of the machine
                     */
                    typedef typename abstract_model<Size>::state_type state_type;

                    /*!
                     * \typedef coef_type
                     * \brief The type contained by the matrix of transition
                     */
                    typedef timed_coef coef_type;

                    /*!
                     * \typedef matrix_type
                     * \brief The type of a matrix of transition.
                     */
                    typedef coef_type matrix_type[(size + 1) * size];

                    /*!
                     * \enum update
                     * \brief Enumeration of the possible modification on one node's machine
                     */
                    typedef enum {activation, stase, deactivation} update;

                    /*!
                     * \brief Constructor of the model
                     * \param m The matrix of transition used
                     * \param nbr_updated_node The number of node updated each step
                     * \param s The initial state of the model
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

                        // Picks some modification from the copy of the state
                        pick_modification(s, list_modified, size_modified);
                    }

                    /*!
                     * \brief Pick some modification from the potential future state to the current state
                     * \param s The potential future state containing all the modification
                     * \param list_modified List of th index of all the modification done
                     * \param size_modified The size of the list
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
                        while(nbr_modif > 0)
                        {
                            // Pick one modification randomly
                            std::size_t picked = std::rand() % nbr_modif;
                            abstract_model<Size>::_state.set(list_modified[picked],
                                    s.test(list_modified[picked]));

                            // Remove the chosen modification from the list to avoid
                            // the same modification is done twice
                            std::copy(list_modified + picked + 1, list_modified + size, list_modified + picked);

                            nbr_modif--;
                        }
                    }

                    /*!
                     * \brief Returns the amount of time a machine can stay static before looping.
                     * \return The minimum time the network has to stay static.
                     */
                    virtual std::time_t get_min_time() const
                    {
                        std::time_t max = _matrix[1].time_min;
                        for(std::size_t i = 0 ; i < (size + 1) * size ; i++)
                        {
                            if(i % (size + 1) == 0)
                                continue;
                            if(_matrix[i].time_min > max)
                                max = _matrix[i].time_min;
                        }
                        return max;
                    }

                protected:
                    /*!
                     * \brief Get the modification of the given node
                     * \return Return the type of modification
                     *
                     * Do the sum of all coefficient of active node attached to
                     * those given. If the result is strictly positive, it's an
                     * activation, if it's strictly negative, it's a deactivation.
                     * Else the node stays the same.
                     */
                    virtual update rule(std::size_t n)
                    {
                        typename coef_type::float_type sum = 0;
                        for(std::size_t i = 0 ; i < size ; i++)
                        {
                            if(abstract_model<Size>::_state.test(i))
                            {
                                _matrix[n * (size + 1) + i + 1].time++;
                                if(_matrix[n * (size + 1) + i + 1].time
                                        >= _matrix[n * (size + 1) + i + 1].time_min)
                                {
                                    sum += _matrix[n * (size + 1) + i + 1].coef;
                                    if(_matrix[n * (size + 1) + i + 1].reset_time)
                                        _matrix[n * (size + 1) + i + 1].time = 0;
                                }
                            }
                        }

                        if(sum > _matrix[n * (size + 1)].coef)
                        {
                            for(std::size_t i = 0 ; i < size ; i++)
                            {
                                if(_matrix[n * (size + 1) + i + 1].reset_time)
                                    _matrix[n * (size + 1) + i + 1].time = 0;
                            }
                            return activation;
                        }
                        if(sum < _matrix[n * (size + 1)].coef)
                        {
                            for(std::size_t i = 0 ; i < size ; i++)
                            {
                                _matrix[n * (size + 1) + i + 1].time = 0;
                            }
                            return deactivation;
                        }
                        return stase;
                    }

                protected:
                    /*!
                     * \var _matrix
                     * \brief The matrix of transition.
                     */
                    matrix_type _matrix;

                    /*!
                     * \var _nbr_updated_node
                     * \brief The amount of node updated each step.
                     */
                    std::size_t _nbr_updated_node;
            };


        /*!
         * \struct timed_matrix_model
         * \tparam Size The size of the boolean network
         * \brief Timed model of a boolean network
         *
         * The transition rules are stored in a matrix like
         * a Markov chain.
         * A node can be connected to another node is a coefficient.
         * If one node is updated, we do the sum of all
         * coefficients of the active node connected to it.
         * If the sum is greater than 0, the node is activated,
         * if it's lower, it is deactivated and if it's null,
         * the node doesn't change.
         * A node is acting for another only if the time in the case
         * of the matrix is greater that the time minimum.
         */
        template <std::size_t Size>
            struct timed_matrix_model
            {
                /*!
                 * \typedef type
                 * \brief Shortcut for hide the struct timed_coef
                 *
                 * It's the type of a matrix_model class using the structure
                 * timed_coef as coefficient of the matrix
                 */
                typedef matrix_model<Size, timed_coef> type;
            };
    }
}

#endif
