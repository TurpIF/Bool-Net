#include "bool_network/models/yeast.h"

namespace bn
{
    namespace models
    {
        typedef dynamic::timed_coef tc;

        yeast::yeast(std::size_t nbr_updated_node,
                coef_type const & ag,
                coef_type const & ar,
                std::time_t const & td,
                state_type const & s):
            dynamic::matrix_model<Size, dynamic::timed_coef>({
                    0.0f, ar,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Cell size
                    0.0f, ag,  tc(-1, td),  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Cln3
                    0.0f, 0, ag,  0,  0,  0,  0,  0,  0,  0,  0,  0, ar, // SBF
                    0.0f, 0,  0, ag,  tc(-1, td),  0,  0,  0,  0,  0,  0,  0,  0, // Cln1,2
                    0.0f, 0,  0,  0, ar,  0, ag,  0,  0, ar,  0,  0, ar, // Cdh1
                    0.0f, 0,  0,  0,  0,  0,  tc(-1, td),  0, ag,  0,  0,  0, ag, // Cdc20&Cdc14
                    0.0f, 0,  0,  0,  0,  0, ag,  tc(-1, td), ag,  0,  0,  0, ar, // Swi5
                    0.0f, 0,  0,  0,  0,  0,  0,  0,  tc(-1, td), ag,  0,  0, ag, // Mcm1/SFF
                    0.0f, 0,  0,  0,  0,  0, ar,  0,  0,  0, ag, ar,  0, // Clb5,6
                    0.0f, 0, ag,  0,  0,  0,  0,  0,  0,  0,  0,  0, ar, // MBF
                    0.0f, 0,  0,  0, ar,  0, ag, ag,  0, ar,  0,  0, ar, // Sic1
                    0.0f, 0,  0,  0,  0, ar, ar,  0, ag, ag,  0, ar,  0, // Clb1,2
                    }, nbr_updated_node, s),
            _td(td)
            {
            }

        std::time_t yeast::get_min_time() const
        {
            return _td;
        }

        bool yeast::get_Cell_size() const   { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[0]; }
        bool yeast::get_Cln3() const        { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[1]; }
        bool yeast::get_SBF() const         { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[2]; }
        bool yeast::get_Cln1_2() const      { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[3]; }
        bool yeast::get_Cdh1() const        { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[4]; }
        bool yeast::get_Cdc20_Cdc14() const { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[5]; }
        bool yeast::get_Swi5() const        { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[6]; }
        bool yeast::get_Mcm1_SFF() const    { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[7]; }
        bool yeast::get_Clb5_6() const      { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[8]; }
        bool yeast::get_MBF() const         { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[9]; }
        bool yeast::get_Sic1() const        { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[10]; }
        bool yeast::get_Clb1_2() const      { return dynamic::matrix_model<Size, dynamic::timed_coef>::_state[11]; }

        void yeast::set_Cell_size(bool a)    { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[0] = a; }
        void yeast::set_Cln3(bool a)         { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[1] = a; }
        void yeast::set_SBF(bool a)          { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[2] = a; }
        void yeast::set_Cln1_2(bool a)       { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[3] = a; }
        void yeast::set_Cdh1(bool a)         { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[4] = a; }
        void yeast::set_Cdc20_Cdc14(bool a)  { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[5] = a; }
        void yeast::set_Swi5(bool a)         { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[6] = a; }
        void yeast::set_Mcm1_SFF(bool a)     { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[7] = a; }
        void yeast::set_Clb5_6(bool a)       { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[8] = a; }
        void yeast::set_MBF(bool a)          { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[9] = a; }
        void yeast::set_Sic1(bool a)         { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[10] = a; }
        void yeast::set_Clb1_2(bool a)       { dynamic::matrix_model<Size, dynamic::timed_coef>::_state[11] = a; }
    }
}
