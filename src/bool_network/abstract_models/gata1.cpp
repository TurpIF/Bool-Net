#include "bool_network/abstract_models/gata1.h"

namespace bn
{
    namespace abstract_models
    {
        std::ostream & operator<<(std::ostream & out, abstract_models::gata1 const & m)
        {
            out << m.get_Epo()
                << m.get_GATA1();
            return out;
        }
    }
}
