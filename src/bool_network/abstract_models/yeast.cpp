#include "bool_network/abstract_models/yeast.h"

namespace bn
{
    namespace abstract_models
    {
        std::ostream & operator<<(std::ostream & out, abstract_models::yeast const & m)
        {
            out << m.get_Cln3()
                << m.get_MBF()
                << m.get_SBF()
                << m.get_Cln1_2()
                << m.get_Cdh1()
                << m.get_Swi5()
                << m.get_Cdc20_Cdc14()
                << m.get_Clb5_6()
                << m.get_Sic1()
                << m.get_Clb1_2()
                << m.get_Mcm1_SFF();
            return out;
        }
    }
}
