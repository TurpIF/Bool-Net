#include <cstdlib>
#include <iostream>

#define SHOW_SUCCESS
//#undef SHOW_SUCCESS

#include <bool_network/dynamic/timed_matrix_model.h>
#include <bool_network/dynamic/state_machine.h>

static const std::size_t N = 1000;
static const std::size_t T = 15;
static std::size_t num_test = 0;

template<typename Model>
void test(Model const & model,
        typename Model::state_type const & init,
        unsigned long int val_expected,
        std::size_t nbr_step = N,
        char const * file = "\0",
        std::size_t line = 0)
{
    num_test++;

    bn::dynamic::state_machine<Model> machine(model);
    machine.get_model().set_state(init);
    machine.step(nbr_step);

    if(machine.get_model().get_state().to_ulong() != val_expected)
    {
        std::cerr << file << ":" << line
            << ": Test n°" << num_test
            << " failed: "
            << val_expected << " expected but " << machine.get_model().get_state().to_ulong() << " find"
            << std::endl;
        std::abort();
    }
#ifdef SHOW_SUCCESS
    else
    {
        std::cout << file << ":" << line
            << ": Test n°" << num_test
            << " valid"
            << std::endl;
    }
#endif
}

#define TEST(model, init, val_expected) test(model, init, val_expected, N, __FILE__, __LINE__)
#define TEST_N(model, init, val_expected, nbr_step) test(model, init, val_expected, nbr_step, __FILE__, __LINE__)

int main()
{
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        bn::dynamic::matrix_model<1> model({0.0, 0}, 1);

        // The node is initialized to 0 and could stay to 0
        TEST(model, 0, 0);

        // The node is initialized to 1 and could stay to 1
        TEST(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        bn::dynamic::matrix_model<1> model({1.0, 0}, 1);

        // The node is initialized to 0 and could stay to 0
        TEST(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        TEST(model, 1, 0);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn on
        bn::dynamic::matrix_model<1> model({-1.0, 0}, 1);

        // The node is initialized to 0 and have to turn on
        TEST(model, 0, 1);

        // The node is initialized to 1 and have to stay to 1
        TEST(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to stay to the same position
        // The node give an positive effect on himself only if he is activate
        bn::dynamic::matrix_model<1> model({0.0, 1}, 1);

        // The node is initialized to 0 and have to stay off
        TEST(model, 0, 0);

        // The node is initialized to 1 and have to stay to 1
        TEST(model, 1, 1);
    }
    {
        // Simple case with only one node interacting with himself
        // The node have to turn off
        // Once the node is activated, he give to himself a negative effect.
        bn::dynamic::matrix_model<1> model({0.0, -1}, 1);

        // The node is initialized to 0 and have to stay off
        TEST(model, 0, 0);

        // The node is initialized to 1 and have to turn off
        TEST(model, 1, 0);
    }
    {
        // Same case than before but with 2 nodes
        // They doesn't have to change
        bn::dynamic::matrix_model<2> model({
                0.0, 0, 0,
                0.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position.
        for(std::size_t i = 0 ; i < 4 ; i++)
            TEST(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to became off
        bn::dynamic::matrix_model<2> model({
                1.0, 0, 0,
                1.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to turn off (0)
        for(std::size_t i = 0 ; i < 4 ; i++)
            TEST(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Nodes have to became on
        bn::dynamic::matrix_model<2> model({
                -1.0, 0, 0,
                -1.0, 0, 0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to turn on (3)
        for(std::size_t i = 0 ; i < 4 ; i++)
            TEST(model, i, 3);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to the same pos
        bn::dynamic::matrix_model<2> model({
                0.0, 1, 0,
                0.0, 0, 1}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to the same position
        for(std::size_t i = 0 ; i < 4 ; i++)
            TEST(model, i, i);
    }
    {
        // Model with 2 nodes
        // Nodes have to stay to turn off
        bn::dynamic::matrix_model<2> model({
                0.0, -1,  0,
                0.0,  0, -1}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have to stay to turn off
        for(std::size_t i = 0 ; i < 4 ; i++)
            TEST(model, i, 0);
    }
    {
        // Model with 2 nodes
        // Each node interact positively with the other
        // If one node is on, the second turn on. If no-one is on,
        // the system stay off
        bn::dynamic::matrix_model<2> model({
                0.0,  0,  1,
                0.0,  1,  0}, 2);

        // The nodes are initialized to 0, 1, 2 or 3 and have stay off if init at off
        // or have to be on (3) if one node is on (1, 2, or 3)
        TEST(model, 0, 0);
        TEST(model, 1, 3);
        TEST(model, 2, 3);
        TEST(model, 3, 3);
    }
    {
        // Model with 2 nodes
        // Each node interact negatively with the other
        // Only one can stay on. If both are on, they turn then off
        bn::dynamic::matrix_model<2> model({
                0.0,  0, -1,
                0.0, -1,  0}, 2);

        TEST(model, 0, 0);
        TEST(model, 1, 1);
        TEST(model, 2, 2);
        TEST(model, 3, 0);
    }
    {
        // Model with 2 nodes
        // One have a positive effect on the other and the other have a
        // negative on the first.
        // If both are off, the system stay off.
        // If the first is on, the second is turned on and turn the first off.
        // So in all other case the first is off and the second on
        bn::dynamic::matrix_model<2> model({
                0.0,  0, -1,
                0.0,  1,  0}, 2);

        TEST(model, 0, 0);
        TEST(model, 1, 2);
        TEST(model, 2, 2);
        TEST(model, 3, 2);
    }
    {
        // Model with 2 nodes and a cycling model
        // The two nodes have a positive effect on each other
        // and a negative effect on themself. So the system blink.
        // For an odd number of step, with 10 or 01, the system is the
        // opposite (01 and 10). Else it's the same position.
        // If the state is 11, the system is at equilibrium.
        bn::dynamic::matrix_model<2> model({
                0.0, -1,  1,
                0.0,  1, -1}, 2);

        TEST(model, 0, 0);
        TEST_N(model, 1, 2, 2 * N + 1); // To be sure, the number of step is odd
        TEST_N(model, 2, 1, 2 * N + 1); // To be sure, the number of step is odd
        TEST_N(model, 1, 1, 2 * N); // To be sure, the number of step is even
        TEST_N(model, 2, 2, 2 * N); // To be sure, the number of step is even
        TEST(model, 3, 3);
    }
    {
        // Model with 4 nodes and a cycling model
        bn::dynamic::matrix_model<4> model({
                0.0, -1,  1,  0,  0,
                0.0,  0, -1,  1,  0,
                0.0,  0,  0, -1,  1,
                0.0,  1,  0,  0, -1}, 4);

        TEST(model, 0, 0);
        TEST_N(model, 1, 1, 4 * N); // Number of step = 0 modulo 4
        TEST_N(model, 2, 2, 4 * N); // Number of step = 0 modulo 4
        TEST_N(model, 4, 4, 4 * N); // Number of step = 0 modulo 4
        TEST_N(model, 8, 8, 4 * N); // Number of step = 0 modulo 4
        TEST_N(model, 1, 8, 4 * N + 1); // Number of step = 1 modulo 4
        TEST_N(model, 2, 1, 4 * N + 1); // Number of step = 1 modulo 4
        TEST_N(model, 4, 2, 4 * N + 1); // Number of step = 1 modulo 4
        TEST_N(model, 8, 4, 4 * N + 1); // Number of step = 1 modulo 4
        TEST_N(model, 1, 4, 4 * N + 2); // Number of step = 2 modulo 4
        TEST_N(model, 2, 8, 4 * N + 2); // Number of step = 2 modulo 4
        TEST_N(model, 4, 1, 4 * N + 2); // Number of step = 2 modulo 4
        TEST_N(model, 8, 2, 4 * N + 2); // Number of step = 2 modulo 4
        TEST_N(model, 1, 2, 4 * N + 3); // Number of step = 3 modulo 4
        TEST_N(model, 2, 4, 4 * N + 3); // Number of step = 3 modulo 4
        TEST_N(model, 4, 8, 4 * N + 3); // Number of step = 3 modulo 4
        TEST_N(model, 8, 1, 4 * N + 3); // Number of step = 3 modulo 4
        TEST(model, 15, 15);

        // Some additional test with more than 1 activated node.
        TEST_N(model, 5, 5, 4 * N); // Number of step = 0 modulo 4
        TEST_N(model, 5, 10, 4 * N + 1); // Number of step = 1 modulo 4
        TEST_N(model, 5, 5, 4 * N + 2); // Number of step = 2 modulo 4
        TEST_N(model, 5, 10, 4 * N + 3); // Number of step = 3 modulo 4

        TEST_N(model, 3, 3, 4 * N); // Number of step = 0 modulo 4
        TEST_N(model, 3, 9, 4 * N + 1); // Number of step = 1 modulo 4
        TEST_N(model, 3, 12, 4 * N + 2); // Number of step = 2 modulo 4
        TEST_N(model, 3, 6, 4 * N + 3); // Number of step = 3 modulo 4
    }

    return 0;
}
