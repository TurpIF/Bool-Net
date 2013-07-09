#include <cstddef>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

#include <bool_network/dynamic/state_machine.h>
#include <bool_network/simulation/basic.h>
#include <bool_network/models/gata1.h>

void simule(bn::models::gata1 const & model, std::size_t n)
{
    bn::simulation::basic<bn::dynamic::state_machine, bn::models::gata1> simulation(model);
    simulation.set_state(typename bn::models::gata1::state_type(1));
    for(std::size_t i = 0 ; i < n ; i++)
    {
        std::cout << simulation.advance() << std::endl;
    }
    simulation.get_model().set_Epo(false);
    std::cout << simulation.advance() << std::endl;
    std::cout << simulation.advance() << std::endl;
    std::cout << simulation.advance() << std::endl;
}

int main(int argc, char ** argv)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::size_t n = 0;
    std::size_t td = 1;
    if(argc > 1)
    {
        std::istringstream iss(argv[1]);
        iss >> n;
    }
    if(argc > 2)
    {
        std::istringstream iss(argv[2]);
        iss >> td;
    }

    std::cout << "Epo active during " << n << " time" << std::endl;
    std::cout << "GATA1 need Epo during " << td << " time" << std::endl;
    simule(bn::models::gata1(td), n);

    return 0;
}
