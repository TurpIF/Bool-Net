#undef NDEBUG
#include <cassert>
#include <iostream>

#include "dynamic/matrix_model.h"
#include "dynamic/state_machine.h"

static const std::size_t N = 1000;

template<typename Model>
void test(Model const & model, typename Model::state_type const & init, unsigned long int val_expected, std::size_t nbr_step = N)
{
    static std::size_t num = 0;
    num++;

    dynamic::state_machine<Model> machine(model);
    machine.get_model().set_state(init);
    machine.step(nbr_step);
    std::cout << num << " : " << init << " => " << machine.get_model().get_state() << std::endl;
    assert(machine.get_model().get_state().to_ulong() == val_expected);
}

int main()
{
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        dynamic::matrix_model<1> model({0.0, 0}, 1);

        // The node is initialized to 0 and could stay to 0
        test(model, 0, 0);

        // The node is initialized to 1 and could stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        dynamic::matrix_model<1> model({1.0, 0}, 1);

        // The node is initialized to 0 and could stay to 0
        test(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        test(model, 1, 0);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn on
        dynamic::matrix_model<1> model({-1.0, 0}, 1);

        // The node is initialized to 0 and have to turn on
        test(model, 0, 1);

        // The node is initialized to 1 and have to stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        // The node give an positive effect on himself only if he is activate
        dynamic::matrix_model<1> model({0.0, 1}, 1);

        // The node is initialized to 0 and have to stay off
        test(model, 0, 0);

        // The node is initialized to 1 and have to stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        // Once the node is activated, he give to himself a negative effect.
        dynamic::matrix_model<1> model({0.0, -1}, 1);

        // The node is initialized to 0 and have to stay off
        test(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        test(model, 1, 0);
    }
    {
        // Same case than before but with 2 nodes
        // They doesn't have to change
        dynamic::matrix_model<2> model({
                0.0, 0, 0,
                0.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position.
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to became off
        dynamic::matrix_model<2> model({
                1.0, 0, 0,
                1.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to turn off (0)
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Nodes have to became on
        dynamic::matrix_model<2> model({
                -1.0, 0, 0,
                -1.0, 0, 0}, 2);
        dynamic::state_machine<dynamic::matrix_model<2> > machine(model);

        // The nodes are initialized to 0, 1, 2 or 3 and have to turn on (3)
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 3);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to the same pos
        dynamic::matrix_model<2> model({
                0.0, 1, 0,
                0.0, 0, 1}, 2);
        dynamic::state_machine<dynamic::matrix_model<2> > machine(model);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to turn off
        dynamic::matrix_model<2> model({
                0.0, -1,  0,
                0.0,  0, -1}, 2);
        dynamic::state_machine<dynamic::matrix_model<2> > machine(model);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to turn off
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Each node interact positively with the other
        // If one node is on, the second turn on. If no-one is on,
        // the system stay off
        dynamic::matrix_model<2> model({
                0.0,  0,  1,
                0.0,  1,  0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have stay off if init at off
        // or have to be on (3) if one node is on (1, 2, or 3)
        test(model, 0, 0);
        test(model, 1, 3);
        test(model, 2, 3);
        test(model, 3, 3);
    }
    {
        // Model with 2 nodes
        // Each node interact negatively with the other
        // Only one can stay on. If both are on, they turn then off
        dynamic::matrix_model<2> model({
                0.0,  0, -1,
                0.0, -1,  0}, 2);

        test(model, 0, 0);
        test(model, 1, 1);
        test(model, 2, 2);
        test(model, 3, 0);
    }
    {
        // Model with 2 nodes
        // One have a positive effect on the other and the other have a
        // negative on the first.
        // If both are off, the system stay off.
        // If the first is on, the second is turned on and turn the first off.
        // So in all other case the first is off and the second on
        dynamic::matrix_model<2> model({
                0.0,  0, -1,
                0.0,  1,  0}, 2);
        dynamic::state_machine<dynamic::matrix_model<2> > machine(model);

        test(model, 0, 0);
        test(model, 1, 2);
        test(model, 2, 2);
        test(model, 3, 2);
    }
    {
        // Model with 2 nodes
        dynamic::matrix_model<2> model({
                0.0, -1,  1,
                0.0,  1, -1}, 2);
        dynamic::state_machine<dynamic::matrix_model<2> > machine(model);

        test(model, 0, 0);
        test(model, 1, 2, 2 * N + 1); // To be sure, the number of step is odd
        test(model, 2, 1, 2 * N + 1); // To be sure, the number of step is even
        test(model, 3, 3);
    }

    return 0;
}
