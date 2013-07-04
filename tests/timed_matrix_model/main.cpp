#undef NDEBUG
#include <cassert>

#define SHOW
//#undef SHOW

#ifdef SHOW
#include <iostream>
#endif

#include "dynamic/timed_matrix_model.h"
#include "dynamic/state_machine.h"

static const std::size_t N = 1000;
static const std::size_t T = 15;

template<typename Model>
void test(Model const & model, typename Model::state_type const & init, unsigned long int val_expected, std::size_t nbr_step = N)
{
    static std::size_t num = 0;
    num++;

    dynamic::state_machine<Model> machine(model);
    machine.get_model().set_state(init);
    machine.step(nbr_step);
#ifdef SHOW
    std::cout << num << " : " << init << " => " << machine.get_model().get_state() << std::endl;
#endif
    assert(machine.get_model().get_state().to_ulong() == val_expected);
}

int main()
{
    typedef dynamic::timed_coef tc;

    // Basic tests without time effect
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        dynamic::timed_matrix_model<1>::type model({0.0, 0}, 1);

        // The node is initialized to 0 and could stay to 0
        test(model, 0, 0);

        // The node is initialized to 1 and could stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        dynamic::timed_matrix_model<1>::type model({1.0, 0}, 1);

        // The node is initialized to 0 and could stay to 0
        test(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        test(model, 1, 0);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn on
        dynamic::timed_matrix_model<1>::type model({-1.0, 0}, 1);

        // The node is initialized to 0 and have to turn on
        test(model, 0, 1);

        // The node is initialized to 1 and have to stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        // The node give an positive effect on himself only if he is activate
        dynamic::timed_matrix_model<1>::type model({0.0, 1}, 1);

        // The node is initialized to 0 and have to stay off
        test(model, 0, 0);

        // The node is initialized to 1 and have to stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        // Once the node is activated, he give to himself a negative effect.
        dynamic::timed_matrix_model<1>::type model({0.0, -1}, 1);

        // The node is initialized to 0 and have to stay off
        test(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        test(model, 1, 0);
    }
    {
        // Same case than before but with 2 nodes
        // They doesn't have to change
        dynamic::timed_matrix_model<2>::type model({
                0.0, 0, 0,
                0.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position.
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to became off
        dynamic::timed_matrix_model<2>::type model({
                1.0, 0, 0,
                1.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to turn off (0)
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Nodes have to became on
        dynamic::timed_matrix_model<2>::type model({
                -1.0, 0, 0,
                -1.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to turn on (3)
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 3);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to the same pos
        dynamic::timed_matrix_model<2>::type model({
                0.0, 1, 0,
                0.0, 0, 1}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to turn off
        dynamic::timed_matrix_model<2>::type model({
                0.0, -1,  0,
                0.0,  0, -1}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to turn off
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Each node interact positively with the other
        // If one node is on, the second turn on. If no-one is on,
        // the system stay off
        dynamic::timed_matrix_model<2>::type model({
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
        dynamic::timed_matrix_model<2>::type model({
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
        dynamic::timed_matrix_model<2>::type model({
                0.0,  0, -1,
                0.0,  1,  0}, 2);

        test(model, 0, 0);
        test(model, 1, 2);
        test(model, 2, 2);
        test(model, 3, 2);
    }
    {
        // Model with 2 nodes and a cycling model
        // The two nodes have a positive effect on each other
        // and a negative effect on themself. So the system blink.
        // For an odd number of step, with 10 or 01, the system is the
        // opposite (01 and 10). Else it's the same position.
        // If the state is 11, the system is at equilibrium.
        dynamic::timed_matrix_model<2>::type model({
                0.0, -1,  1,
                0.0,  1, -1}, 2);

        test(model, 0, 0);
        test(model, 1, 2, 2 * N + 1); // To be sure, the number of step is odd
        test(model, 2, 1, 2 * N + 1); // To be sure, the number of step is odd
        test(model, 1, 1, 2 * N); // To be sure, the number of step is even
        test(model, 2, 2, 2 * N); // To be sure, the number of step is even
        test(model, 3, 3);
    }
    {
        // Model with 4 nodes and a cycling model
        dynamic::timed_matrix_model<4>::type model({
                0.0, -1,  1,  0,  0,
                0.0,  0, -1,  1,  0,
                0.0,  0,  0, -1,  1,
                0.0,  1,  0,  0, -1}, 4);

        test(model, 0, 0);
        test(model, 1, 1, 4 * N); // Number of step = 0 modulo 4
        test(model, 2, 2, 4 * N); // Number of step = 0 modulo 4
        test(model, 4, 4, 4 * N); // Number of step = 0 modulo 4
        test(model, 8, 8, 4 * N); // Number of step = 0 modulo 4
        test(model, 1, 8, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 2, 1, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 4, 2, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 8, 4, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 1, 4, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 2, 8, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 4, 1, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 8, 2, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 1, 2, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 2, 4, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 4, 8, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 8, 1, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 15, 15);

        // Some additional test with more than 1 activated node.
        test(model, 5, 5, 4 * N); // Number of step = 0 modulo 4
        test(model, 5, 10, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 5, 5, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 5, 10, 4 * N + 3); // Number of step = 3 modulo 4

        test(model, 3, 3, 4 * N); // Number of step = 0 modulo 4
        test(model, 3, 9, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 3, 12, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 3, 6, 4 * N + 3); // Number of step = 3 modulo 4
    }

    // Tests withtime effect
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        // The node give an positive effect on himself only if he is activate
        dynamic::timed_matrix_model<1>::type model({0.0, tc(1, T)}, 1);

        // The node is initialized to 0 and have to stay off
        test(model, 0, 0);

        // The node is initialized to 1 and have to stay to 1
        test(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        // Once the node is activated, he give to himself a negative effect.
        dynamic::timed_matrix_model<1>::type model({0.0, tc(-1, T)}, 1);

        // The node is initialized to 0 and have to stay off
        test(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        test(model, 1, 0);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to the same pos
        dynamic::timed_matrix_model<2>::type model({
                0.0, tc(1, T), 0,
                0.0, 0, tc(1, T)}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to turn off
        dynamic::timed_matrix_model<2>::type model({
                0.0, tc(-1, T),  0,
                0.0,  0, tc(-1, T)}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to turn off
        for(std::size_t i = 0 ; i < 4 ; i++)
            test(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Each node interact positively with the other
        // If one node is on, the second turn on. If no-one is on,
        // the system stay off
        dynamic::timed_matrix_model<2>::type model({
                0.0,  0,  tc(1, T),
                0.0,  tc(1, T),  0}, 2);

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
        dynamic::timed_matrix_model<2>::type model({
                0.0,  0, tc(-1, T),
                0.0, tc(-1, T),  0}, 2);

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
        dynamic::timed_matrix_model<2>::type model({
                0.0,  0, tc(-1, T),
                0.0,  tc(1, T),  0}, 2);

        test(model, 0, 0);
        test(model, 1, 2);
        test(model, 2, 2);
        test(model, 3, 2);
    }
    {
        // Model with 2 nodes and a cycling model
        // The two nodes have a positive effect on each other
        // and a negative effect on themself. So the system blink.
        // For an odd number of step, with 10 or 01, the system is the
        // opposite (01 and 10). Else it's the same position.
        // If the state is 11, the system is at equilibrium.
        dynamic::timed_matrix_model<2>::type model({
                0.0, tc(-1, T),  tc(1, T),
                0.0,  tc(1, T), tc(-1, T)}, 2);

        test(model, 0, 0);
        test(model, 1, 2, 2 * N + 1); // To be sure, the number of step is odd
        test(model, 2, 1, 2 * N + 1); // To be sure, the number of step is odd
        test(model, 1, 1, 2 * N); // To be sure, the number of step is even
        test(model, 2, 2, 2 * N); // To be sure, the number of step is even
        test(model, 3, 3);
    }
    {
        // Model with 4 nodes and a cycling model
        dynamic::timed_matrix_model<4>::type model({
                0.0, tc(-1, T),  tc(1, T),  0,  0,
                0.0,  0, tc(-1, T),  tc(1, T),  0,
                0.0,  0,  0, tc(-1, T),  tc(1, T),
                0.0,  tc(1, T),  0,  0,  tc(-1, T)}, 4);

        test(model, 0, 0);
        test(model, 1, 1, 4 * N); // Number of step = 0 modulo 4
        test(model, 2, 2, 4 * N); // Number of step = 0 modulo 4
        test(model, 4, 4, 4 * N); // Number of step = 0 modulo 4
        test(model, 8, 8, 4 * N); // Number of step = 0 modulo 4
        test(model, 1, 8, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 2, 1, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 4, 2, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 8, 4, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 1, 4, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 2, 8, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 4, 1, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 8, 2, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 1, 2, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 2, 4, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 4, 8, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 8, 1, 4 * N + 3); // Number of step = 3 modulo 4
        test(model, 15, 15);

        // Some additional test with more than 1 activated node.
        test(model, 5, 5, 4 * N); // Number of step = 0 modulo 4
        test(model, 5, 10, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 5, 5, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 5, 10, 4 * N + 3); // Number of step = 3 modulo 4

        test(model, 3, 3, 4 * N); // Number of step = 0 modulo 4
        test(model, 3, 9, 4 * N + 1); // Number of step = 1 modulo 4
        test(model, 3, 12, 4 * N + 2); // Number of step = 2 modulo 4
        test(model, 3, 6, 4 * N + 3); // Number of step = 3 modulo 4
    }
    return 0;
}

