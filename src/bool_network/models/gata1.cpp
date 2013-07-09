#include "bool_network/models/gata1.h"

namespace bn
{
    namespace models
    {
        gata1::gata1(std::time_t const & td,
                state_type const & s):
            dynamic::matrix_model<Size, dynamic::timed_coef>({
                    0.0f, 0, 0, // Epo
                    0.0f, dynamic::timed_coef(1, td), 0 // GATA1
                    }, 1, s),
            _td(td)
            {
            }

        std::time_t gata1::get_min_time() const
        {
            return _td;
        }

        bool gata1::get_Epo() const   { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[0]; }
        bool gata1::get_GATA1() const { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[1]; }

        void gata1::set_Epo(bool a)   { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[0] = a; }
        void gata1::set_GATA1(bool a) { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[1] = a; }
    }
}
