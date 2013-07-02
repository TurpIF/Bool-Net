#include "cellBOOL.h"
#include "model.h"

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

// Simulation of the model Model
template<typename Model>
void simule(bool tnf, bool fas)
{
    // Initialisation of number of A/N/S/Naive
    std::size_t apoptosis = 0;
    std::size_t necrosis = 0;
    std::size_t survival = 0;
    std::size_t naive = 0;

    // Definition of the initial state
    double initial_state[Model::node_number] = {
        tnf ? 1 : 0, // TNF
        fas ? 1 : 0, // FAS
        0, // RIP1
        0, // NFkB
        0, // C8
        1, // cIAP
        1, // ATP
        0, // C3
        0, // ROS
        0, // MOMP
        0  // MPT
    };

    // Loop generating the random cell
    static const std::size_t N = 10000;
    for(std::size_t i = 0 ; i < N ; i++)
    {
        // Creation of the cell and update
        cellBOOL<Model> c(initial_state);
        c.internal_update();

        // Getting the model and checking if it's A/N/S or Naive end
        const model_wild_type & m = c.model();
        if(m.C3() && !(!m.ATP() || m.NFkB()))
            apoptosis++;
        else if(!m.ATP() && !(m.C3() || m.NFkB()))
            necrosis++;
        else if(m.NFkB() && !(m.C3() || !m.ATP()))
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
        if(std::strcmp(argv[0], "tnf") != 0)
            tnf = true;
        if(std::strcmp(argv[0], "fas") != 0)
            fas = true;
        if(argc > 2)
        {
            if(std::strcmp(argv[0], "tnf") != 0)
                tnf = true;
            if(std::strcmp(argv[0], "fas") != 0)
                fas = true;
        }
    }

    std::cout << "wild type,";                      simule<model_wild_type>(tnf, fas);
    std::cout << "anti oxidant,";                   simule<model_anti_oxidant>(tnf, fas);
    std::cout << "APAF1 deletion,";                 simule<model_APAF1_deletion>(tnf, fas);
    std::cout << "BAX deletion,";                   simule<model_BAX_deletion>(tnf, fas);
    std::cout << "BCL2 over expression,";           simule<model_BCL2_over_expression>(tnf, fas);
    std::cout << "CASP8 deletion,";                 simule<model_CASP8_deletion>(tnf, fas);
    std::cout << "constitutively activated CASP8,"; simule<model_constitutively_activated_CASP8>(tnf, fas);
    std::cout << "cFLIP deletetion,";               simule<model_cFLIP_deletion>(tnf, fas);
    std::cout << "cIAP deletetion,";                simule<model_cIAP_deletion>(tnf, fas);
    std::cout << "FADD deletetion,";                simule<model_FADD_deletion>(tnf, fas);
    std::cout << "NFkB deletetion,";                simule<model_NFkB_deletion>(tnf, fas);
    std::cout << "constitutively activated NFkB,";  simule<model_constitutively_activated_NFkB>(tnf, fas);
    std::cout << "RIP1 deletetion,";                simule<model_RIP1_deletetion>(tnf, fas);
    std::cout << "XIAP deletetion,";                simule<model_XIAP_deletetion>(tnf, fas);
    std::cout << "z VAD,";                          simule<model_z_VAD>(tnf, fas);
    std::cout << "z VAD et RIP1 deletion,";           simule<model_z_VAD_RIP1_deletion>(tnf, fas);

    return 0;
}
