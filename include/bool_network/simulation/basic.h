/*!
 * \file bool_network/simulation/basic.h
 * \author Turpin Pierre
 * \brief Definition of a class to simply simule a state machine
 */
#ifndef __BOOL_NETWORK_SIMULATION_BASIC_H__
#define __BOOL_NETWORK_SIMULATION_BASIC_H__

#include <map>
#include <cstddef>

namespace bn
{
    namespace simulation
    {
        /*!
         * \class basic
         * \brief Basic simulation of state machine
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
            class basic
            {
                public:
                    /*!
                     * \brief Constructor of a simulator
                     * \param m The model to use for the simulation
                     */
                    basic(Model const & m = Model()):
                        _model(m)
                {
                }

                    /*!
                     * \brief Setter to modify the state of the model.
                     * \param state The state to put in the model.
                     */
                    void set_state(typename Model::state_type const & state)
                    {
                        _model.set_state(state);
                    }

                    /*!
                     * \brief Get the current model. (const version)
                     */
                    Model const & get_model() const
                    {
                        return _model;
                    }

                    /*!
                     * \brief Get the current model. (non-const version)
                     */
                    Model & get_model()
                    {
                        return _model;
                    }

                    /*!
                     * \brief Advance the simulation from the given state.
                     * \param state The state to start the simulation from.
                     * \param nbr_step The number of step the simulation has to advance.
                     * \return Return the model after the simulation
                     *
                     * Set the state and use the advance function.
                     *
                     * \see advance
                     */
                    virtual Model const & advance_from(
                            typename Model::state_type const & state,
                            std::size_t nbr_step = 1)
                    {
                        _model.set_state(state);
                        return advance(nbr_step);
                    }

                    /*!
                     * \brief Advance the simulation by a given number of steps.
                     * \param nbr_step Number of steps the simulation has to advance.
                     * \return Model after the simulation
                     *
                     * Creates a new machine and injects a copy of the current model in.
                     * Then advance the machine nbr_step times.
                     * Copy the machine's model in the simulation model and return this one.
                     */
                    virtual Model const & advance(std::size_t nbr_step = 1)
                    {
                        // Creation of the cell and update
                        Machine<Model> machine(_model);
                        machine.step(nbr_step);
                        _model = machine.get_model();
                        return machine.get_model();
                    }

                protected:
                    /*!
                     * \var _model
                     * \brief The model used by the simulation.
                     */
                    Model _model;
            };
    }
}

#endif
