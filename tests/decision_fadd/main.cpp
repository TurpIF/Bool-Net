#include <cstddef>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

#include "dynamic/state_machine.h"
#include "simulation/basic.h"
#include "tests/fadd.h"

void simule(tests::fadd const & model, bool tnf = false, bool fas = false)
{
    simulation::basic<dynamic::state_machine, tests::fadd> simulation(model);
    static const std::size_t N = 10000;

    // Initialisation of number of A/N/S/Naive
    std::size_t apoptosis = 0;
    std::size_t necrosis = 0;
    std::size_t survival = 0;
    std::size_t naive = 0;

    for(std::size_t i = 0 ; i < N ; i++)
    {
        // Getting the model and checking if it's A/N/S or Naive end
        const tests::fadd & m = simulation.advance_from(typename tests::fadd::state_type(
                    ((tnf ? 1 : 0) << 0) | ((fas ? 1 : 0) << 1) | (1 << 5) | (1 << 6)), 1000);
        if(m.get_C3() && !(!m.get_ATP() || m.get_NFkB()))
            apoptosis++;
        else if(!m.get_ATP() && !(m.get_C3() || m.get_NFkB()))
            necrosis++;
        else if(m.get_NFkB() && !(m.get_C3() || !m.get_ATP()))
            survival++;
        else
            naive++;
    }

    // Show the result on the default output
    std::size_t sum = apoptosis + necrosis + survival + naive;
    std::cout << /* std::setw(5) << */ static_cast<int>(static_cast<float>(apoptosis) / static_cast<float>(sum) * 100) << ","// << "%A "
        /* << std::setw(5) */ << static_cast<int>(static_cast<float>(necrosis) / static_cast<float>(sum) * 100) << ","// << "%N "
        /* << std::setw(5) */ << static_cast<int>(static_cast<float>(survival) / static_cast<float>(sum) * 100) << ","// << "%S "
        /* << std::setw(5) */ << static_cast<int>(static_cast<float>(naive) / static_cast<float>(sum) * 100)// << "% "
        << std::endl;

    //for(typename simulation::converge<dynamic::state_machine, tests::fadd>::visited_type::const_iterator
    //        it = simulation.get_visited().begin() ;
    //        it != simulation.get_visited().end() ; it++)
    //{
    //    const tests::fadd & m = it->first;
    //    std::cout << std::setw(10) << it->second << " " << m << std::endl;
    //}
}

int main(int argc, char ** argv)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    bool tnf = false;
    bool fas = false;
    if(argc > 1)
    {
        if(std::strcmp(argv[1], "tnf") == 0)
            tnf = true;
        if(std::strcmp(argv[1], "fas") == 0)
            fas = true;

        if(argc > 2)
        {
            if(std::strcmp(argv[2], "tnf") == 0)
                tnf = true;
            if(std::strcmp(argv[2], "fas") == 0)
                fas = true;
        }
    }

    std::cout << "TNF is " << (tnf ? "" : "not ") << "activated ; ";
    std::cout << "FAS is " << (fas ? "" : "not ") << "activated" << std::endl;
    std::cout << "wild type,"; simule(tests::fadd::wild_type(1), tnf, fas);
    std::cout << "anti oxidant,"; simule(tests::fadd::anti_oxidant(1), tnf, fas);
    std::cout << "APAF1 deletion,"; simule(tests::fadd::APAF1_del(1), tnf, fas);
    std::cout << "BAX deleteion,"; simule(tests::fadd::BAX_del(1), tnf, fas);
    std::cout << "BCL2 over expression,"; simule(tests::fadd::BCL2_expr(1), tnf, fas);
    std::cout << "CASP8 deleteion,"; simule(tests::fadd::C8_del(1), tnf, fas);
    std::cout << "constituvely activated CASP8,"; simule(tests::fadd::C8_expr(1), tnf, fas);
    std::cout << "cFlip deletion,"; simule(tests::fadd::cFlip_del(1), tnf, fas);
    std::cout << "cIAP deletion,"; simule(tests::fadd::cIAP_del(1), tnf, fas);
    std::cout << "FADD deletion,"; simule(tests::fadd::FADD_del(1), tnf, fas);
    std::cout << "NFkB deletion,"; simule(tests::fadd::NFkB_del(1), tnf, fas);
    std::cout << "constituvely activated NFkB,"; simule(tests::fadd::NFkB_expr(1), tnf, fas);
    std::cout << "RIP1 deletion,"; simule(tests::fadd::RIP1_del(1), tnf, fas);
    std::cout << "XIAP deletion,"; simule(tests::fadd::XIAP_del(1), tnf, fas);
    std::cout << "z VAD,"; simule(tests::fadd::z_VAD(1), tnf, fas);
    std::cout << "z VAD et RIP1 deletion,"; simule(tests::fadd::z_VAD_RIP1_del(1), tnf, fas);

    return 0;
}


