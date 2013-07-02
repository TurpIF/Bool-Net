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

    std::cout << "digraph G {\n";
    std::cout << "splines=line;\n";
    std::cout << "overlap=false;\n";
    std::cout << "node [shape=box];\n";

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
        std::cout << std::setw(10) << it->second << " "
            << m.get_Cln3()
            << m.get_MBF()
            << m.get_SBF()
            << m.get_Cln1_2()
            << m.get_Cdh1()
            << m.get_Swi5()
            << m.get_Cdc20_Cdc14()
            << m.get_Clb5_6()
            << m.get_Sic1()
            << m.get_Clb1_2()
            << m.get_Mcm1_SFF()
            << std::endl;
    }
    std::cout << "}" << std::flush;
    return 0;
}
