/*!
 * \file bool_network/dynamic/state_machine.h
 * \author Turpin Pierre
 * \brief Definition of a class representing a state machine
 */
#ifndef __BOOL_NETWORK_DYNAMIC_STATE_MACHINE_H__
#define __BOOL_NETWORK_DYNAMIC_STATE_MACHINE_H__

#include <vector>
#include <iterator>
#include <algorithm>
#include <cstddef>
#include <ctime>

namespace bn
{
    namespace dynamic
    {
        /*!
         * \class state_machine
         * \tparam Model model used by the machine
         * \brief State machine
         *
         * It's the representation of a state machine defined by the model Model.
         * This machine manages loops in the state graph. In case of a loop, the final
         * step is automatically deduced without calculating those between.
         * All types of model which have a step function work with this network.
         *
         * The model has to give some information :
         * \li The type of one state which must have an equal operator.
         * \li The update of the model such as for each step there is new_state = update(old_state)
         * \li The amount of time the machine can stay in stase without considering it's looping or converging
         */
        template <typename Model>
            class state_machine
            {
                public:
                    typedef Model model_type;

                    /*!
                     * \typedef state_type
                     * \brief Represent one state of the machine.
                     * \warning The model has to give an equal operator for the state
                     *
                     * The model gives the type of the state. For preventing an infinite loop,
                     * all visited states are stored and for each step, the new state is,
                     * searched in the visited. This can be used only if there is an
                     * operator to check if two states are equal.
                     */
                    typedef typename model_type::state_type state_type;

                    /*!
                     * \typedef history_type
                     * \brief Container of the visited state of the machine.
                     *
                     * For each step, the current state is stored. This prevents
                     * for loop in the state graph.
                     */
                    typedef std::vector<state_type> history_type;

                    /*!
                     * \brief Constructor of the state machine
                     * \param m copy the model given.
                     *
                     * Constructs a state machine by copying the given model.
                     * The constructor set also the variables to prevent looping.
                     * The current state of the model is stored in the list of visited state.
                     */
                    state_machine(model_type const & m = model_type()):
                        _model(m),
                        _history(),
                        _in_cycle(false),
                        _begin_cycle(0),
                        _time(0)
                {
                    // Store the current state in the history
                    //_history.push_back(_model.get_state());
                }

                    /*!
                     * \brief Return the current model used.
                     * \return The current model
                     */
                    model_type const & get_model() const
                    {
                        return _model;
                    }

                    /*!
                     * \brief Return the current model used.
                     * \return The current model
                     *
                     * It's the non-const version.
                     */
                    model_type & get_model()
                    {
                        return _model;
                    }

                    /*!
                     * \brief Update the machine
                     * \param time the number of time the machine is updated
                     *
                     * Updates the machine and the model. Also detects if there is a loop.
                     * In this case, jump directly to the final state.
                     * A model can specify the time it can be static without deduce there
                     * is a convergence or a loop.
                     */
                    void step(std::time_t time = 1)
                    {
                        if(time <= 0)
                            return;

                        if(_in_cycle)
                        {
                            // In case of loop, jumps directly to the final state
                            _time += time;
                            std::ptrdiff_t d = (_history.size() - _model.get_min_time() - 1) - _begin_cycle;
                            _model.set_state(_history[_begin_cycle + (_time - _begin_cycle - 1) % d]);
                        }
                        else
                        {
                            // Calcul one step and recommence the process while time > 0
                            one_step();
                            step(time - 1);
                        }
                    }

                private:
                    /*!
                     * \brief Update only once time
                     *
                     * Updates the model and checks if the new state is stored in the history.
                     * If it's stored a certain amount of time defined by the model, the machine
                     * deduces the model is now in a loop.
                     */
                    void one_step()
                    {
                        // Delegate the update of the model
                        _model.step();

                        // Try to find if the current state was already visited
                        if(_history.size() > static_cast<typename history_type::size_type>(_model.get_min_time()))
                        {
                            typename history_type::iterator end = _history.end() - _model.get_min_time() - 1;
                            typename history_type::iterator it;
                            it = std::search(_history.begin(), end, end, _history.end());
                            if(it != end)
                            {
                                _begin_cycle = std::distance(_history.begin(), it);
                                _in_cycle = true;
                            }
                        }

                        if(!_in_cycle)
                        {
                            _history.push_back(_model.get_state());
                        }

                        //typename history_type::iterator it = _history.end();
                        //if(_time >= _model.get_min_time())

                        //std::cout << std::distance(it, _history.end() - _model.get_min_time()) << std::endl;

                        //if(it != _history.end() && it != (_history.end() - _model.get_min_time() - 1))
                        //{
                        //    // If true, the machine is in  a loop
                        //    _begin_cycle = std::distance(_history.begin(), it);
                        //    _in_cycle = true;
                        //}

                        _time += 1;
                    }

                protected:
                    /*!
                     * \var _model
                     * \brief Current model used.
                     */
                    model_type _model;

                    /*!
                     * \var _history
                     * \brief list of all visited states.
                     */
                    history_type _history;

                    /*!
                     * \var _in_cycle
                     * \brief Indicate if the machine is looping or not.
                     */
                    bool _in_cycle;

                    /*!
                     * \var _begin_cycle
                     * \brief The begin of the loop of the machine
                     * \warning If the machine is not in loop, the value may be invalid
                     */
                    std::size_t _begin_cycle;

                    /*!
                     * \var _time
                     * \brief Local time of the machine
                     */
                    std::time_t _time;
            };
    }
}

#endif
