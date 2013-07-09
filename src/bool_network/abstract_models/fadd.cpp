#include "bool_network/abstract_models/fadd.h"

namespace bn
{
    namespace abstract_models
    {
        std::ostream & operator<<(std::ostream & out, abstract_models::fadd const & m)
        {
            out << m.get_TNF()
                << m.get_FAS()
                << m.get_RIP1()
                << m.get_NFkB()
                << m.get_C8()
                << m.get_cIAP()
                << m.get_ATP()
                << m.get_C3()
                << m.get_ROS()
                << m.get_MOMP()
                << m.get_MPT();
            return out;
        }
    }
}
