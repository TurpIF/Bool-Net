#include <cstddef>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

#include <bool_network/dynamic/state_machine.h>
#include <bool_network/simulation/basic.h>
#include <bool_network/models/fadd.h>

void simule(bn::models::fadd const & model, bool tnf = false, bool fas = false)
{
    bn::simulation::basic<bn::dynamic::state_machine, bn::models::fadd> simulation(model);
    static const std::size_t N = 10000;

    // Initialisation of number of A/N/S/Naive
    std::size_t apoptosis = 0;
    std::size_t necrosis = 0;
    std::size_t survival = 0;
    std::size_t naive = 0;

    for(std::size_t i = 0 ; i < N ; i++)
    {
        // Getting the model and checking if it's A/N/S or Naive end
        const bn::models::fadd & m = simulation.advance_from(typename bn::models::fadd::state_type(
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
    std::cout << "wild type,"; simule(bn::models::fadd::wild_type(1), tnf, fas);
    std::cout << "anti oxidant,"; simule(bn::models::fadd::anti_oxidant(1), tnf, fas);
    std::cout << "APAF1 deletion,"; simule(bn::models::fadd::APAF1_del(1), tnf, fas);
    std::cout << "BAX deleteion,"; simule(bn::models::fadd::BAX_del(1), tnf, fas);
    std::cout << "BCL2 over expression,"; simule(bn::models::fadd::BCL2_expr(1), tnf, fas);
    std::cout << "CASP8 deleteion,"; simule(bn::models::fadd::C8_del(1), tnf, fas);
    std::cout << "constituvely activated CASP8,"; simule(bn::models::fadd::C8_expr(1), tnf, fas);
    std::cout << "cFlip deletion,"; simule(bn::models::fadd::cFlip_del(1), tnf, fas);
    std::cout << "cIAP deletion,"; simule(bn::models::fadd::cIAP_del(1), tnf, fas);
    std::cout << "FADD deletion,"; simule(bn::models::fadd::FADD_del(1), tnf, fas);
    std::cout << "NFkB deletion,"; simule(bn::models::fadd::NFkB_del(1), tnf, fas);
    std::cout << "constituvely activated NFkB,"; simule(bn::models::fadd::NFkB_expr(1), tnf, fas);
    std::cout << "RIP1 deletion,"; simule(bn::models::fadd::RIP1_del(1), tnf, fas);
    std::cout << "XIAP deletion,"; simule(bn::models::fadd::XIAP_del(1), tnf, fas);
    std::cout << "z VAD,"; simule(bn::models::fadd::z_VAD(1), tnf, fas);
    std::cout << "z VAD et RIP1 deletion,"; simule(bn::models::fadd::z_VAD_RIP1_del(1), tnf, fas);

    return 0;
}


