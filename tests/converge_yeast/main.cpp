#include <cstddef>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "dynamic/state_machine.h"
#include "simulation/converge.h"
#include "tests/yeast.h"

int main(int, char **)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    simulation::converge<dynamic::state_machine, tests::yeast> simulation(
            tests::yeast(std::numeric_limits<std::size_t>::max(), 1, -1, 0));
    static const std::size_t N = static_cast<std::size_t>(std::pow(2, tests::yeast::size));
    for(std::size_t i = 0 ; i < N ; i += 2)
    {
        simulation.advance_from(typename tests::yeast::state_type(i), 1000);
    }

    for(typename simulation::converge<dynamic::state_machine, tests::yeast>::visited_type::const_iterator
            it = simulation.get_visited().begin() ;
            it != simulation.get_visited().end() ; it++)
    {
        const tests::yeast & m = it->first;
        std::cout << std::setw(10) << it->second << " " << m << std::endl;
    }

    return 0;
}
