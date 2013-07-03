#undef NDEBUG
#include <cassert>

#include "dynamic/matrix_model.h"
#include "dynamic/state_machine.h"

int main()
{
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        dynamic::matrix_model<1> model({0.0, 0}, 1);

        dynamic::state_machine<dynamic::matrix_model<1> > machine(model);

        // The node is initialized to 0 and could stay to 0
        machine.get_model().set_state(0);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 0);

        // The node is initialized to 1 and could stay to 1
        machine.get_model().set_state(1);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        dynamic::matrix_model<1> model({1.0, 0}, 1);

        dynamic::state_machine<dynamic::matrix_model<1> > machine(model);

        // The node is initialized to 0 and could stay to 0
        machine.get_model().set_state(0);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 0);

        // The node is initialized to 1 and have to turn off
        machine.get_model().set_state(1);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 0);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn on
        dynamic::matrix_model<1> model({-1.0, 0}, 1);

        dynamic::state_machine<dynamic::matrix_model<1> > machine(model);

        // The node is initialized to 0 and have to turn on
        machine.get_model().set_state(0);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 1);

        // The node is initialized to 1 and have to stay to 1
        machine.get_model().set_state(1);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        // The node give an positive effect on himself only if he is activate
        dynamic::matrix_model<1> model({0.0, 1}, 1);

        dynamic::state_machine<dynamic::matrix_model<1> > machine(model);

        // The node is initialized to 0 and have to stay off
        machine.get_model().set_state(0);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 0);

        // The node is initialized to 1 and have to stay to 1
        machine.get_model().set_state(1);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        // Once the node is activated, he give to himself a negative effect.
        dynamic::matrix_model<1> model({0.0, -1}, 1);

        dynamic::state_machine<dynamic::matrix_model<1> > machine(model);

        // The node is initialized to 0 and have to stay off
        machine.get_model().set_state(0);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 0);

        // The node is initialized to 1 and have to turn off
        machine.get_model().set_state(1);
        machine.step();
        assert(machine.get_model().get_state().to_ulong() == 0);
    }

    return 0;
}
