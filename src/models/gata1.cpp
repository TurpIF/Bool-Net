#include "models/gata1.h"

namespace models
{
    std::ostream & operator<<(std::ostream & out, models::gata1 const & m)
    {
        out << m.get_Epo()
            << m.get_GATA1();
        return out;
    }
}
