#include <cstddef>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

#include <bool_network/dynamic/state_machine.h>
#include <bool_network/simulation/converge.h>
#include <bool_network/models/yeast.h>

int main(int, char **)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    bn::simulation::converge<bn::dynamic::state_machine, bn::models::yeast> simulation(
            bn::models::yeast(std::numeric_limits<std::size_t>::max(), 1, -1, 0));
    static const std::size_t N = static_cast<std::size_t>(std::pow(2, bn::models::yeast::size));
    for(std::size_t i = 0 ; i < N ; i += 2)
    {
        simulation.advance_from(typename bn::models::yeast::state_type(i), 1000);
    }

    for(typename bn::simulation::converge<bn::dynamic::state_machine, bn::models::yeast>::visited_type::const_iterator
            it = simulation.get_visited().begin() ;
            it != simulation.get_visited().end() ; it++)
    {
        const bn::models::yeast & m = it->first;
        std::cout << std::setw(10) << it->second << " " << m << std::endl;
    }

    return 0;
}
