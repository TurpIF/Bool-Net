/*!
 * \file bool_network/simulation/converge.h
 * \author Turpin Pierre
 * \brief Definition of a class to simule a state machine with the trace of the passage
 */
#ifndef __BOOL_NETWORK_SIMULATION_CONVERGE_H__
#define __BOOL_NETWORK_SIMULATION_CONVERGE_H__

#include <map>
#include <cstddef>

#include "bool_network/simulation/basic.h"

namespace bn
{
    namespace simulation
    {
        /*!
         * \class converge
         * \brief Simulation of state machine with keeping a trace of the passage
         * \tparam Machine Type of the machine used for the simulation
         * \tparam Model Type of the model used
         *
         * The machine waits the model as a template argument.
         * For each simulation, one new machine is created and the current
         * model is injected into. The whole memory is so stored in the model.
         * This assures that the machine is only a functional machine
         * which doesn't stock any data.
         */
        template <template <typename M> class Machine, typename Model>
            class converge : public basic<Machine, Model>
        {
            public:
                /*!
                 * \typedef visited_type
                 * \brief Type of the container of visited states.
                 *
                 * The visited states are stored with their corresponding model
                 * allowing the user to used the model's interface.
                 */
                typedef std::map<Model, std::size_t> visited_type;

                /*!
                 * \brief Constructor of a simulator
                 * \param m The model to use for the simulation
                 *
                 * Stock the given model and initialize the list of
                 * converged states.
                 */
                converge(Model const & m = Model()):
                    basic<Machine, Model>(m),
                    _visited()
            {
            }

                /*!
                 * \brief Advance the simulation by a given number of steps.
                 * \param nbr_step Number of steps the simulation has to advance.
                 * \return Model after the simulation
                 *
                 * Creates a new machine and injects a copy of the current model in.
                 * Then advance the machine nbr_step times and store the current state
                 * in the visited list.
                 * Copy the machine's model in the simulation model and return this one.
                 */
                virtual Model const & advance(std::size_t nbr_step = 1)
                {
                    Model const & m = basic<Machine, Model>::advance(nbr_step);

                    bool find = false;
                    for(typename visited_type::iterator it = _visited.begin() ;
                            it != _visited.end() ; it++)
                    {
                        if(it->first.get_state() == m.get_state())
                        {
                            find = true;
                            it->second++;
                            break;
                        }
                    }
                    if(!find)
                    {
                        _visited.insert(std::pair<Model, std::size_t>(m, 1));
                    }

                    return m;
                }

                /*!
                 * \brief Get the list of visited states.
                 * \return Return the list of visited states.
                 */
                visited_type const & get_visited() const
                {
                    return _visited;
                }

            protected:
                /*!
                 * \var _visited
                 * \brief The list of visited states during the simulation.
                 */
                visited_type _visited;
        };
    }
}

#endif
