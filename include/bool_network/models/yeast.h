#ifndef __BOOL_NETWORK_MODELS_YEAST_H__
#define __BOOL_NETWORK_MODELS_YEAST_H__

#include <ctime>
#include <cstddef>

#include "bool_network/dynamic/timed_matrix_model.h"
#include "bool_network/abstract_models/yeast.h"

namespace bn
{
    namespace models
    {
        class yeast : public dynamic::matrix_model<12, dynamic::timed_coef>, public abstract_models::yeast
        {
            public:
                static std::size_t const Size = 12;
                static std::size_t const size = dynamic::matrix_model<Size>::size;

                typedef typename dynamic::matrix_model<Size, dynamic::timed_coef>::state_type state_type;
                typedef typename dynamic::matrix_model<Size, dynamic::timed_coef>::matrix_type matrix_type;
                typedef typename dynamic::matrix_model<Size, dynamic::timed_coef>::coef_type coef_type;

                yeast(std::size_t nbr_updated_node,
                        coef_type const & ag,
                        coef_type const & ar,
                        std::time_t const & td,
                        state_type const & s = state_type());

                virtual std::time_t get_min_time() const;

                virtual bool get_Cell_size() const;
                virtual bool get_Cln3() const;
                virtual bool get_SBF() const;
                virtual bool get_Cln1_2() const;
                virtual bool get_Cdh1() const;
                virtual bool get_Cdc20_Cdc14() const;
                virtual bool get_Swi5() const;
                virtual bool get_Mcm1_SFF() const;
                virtual bool get_Clb5_6() const;
                virtual bool get_MBF() const;
                virtual bool get_Sic1() const;
                virtual bool get_Clb1_2() const;

                virtual void set_Cell_size(bool a);
                virtual void set_Cln3(bool a);
                virtual void set_SBF(bool a);
                virtual void set_Cln1_2(bool a);
                virtual void set_Cdh1(bool a);
                virtual void set_Cdc20_Cdc14(bool a);
                virtual void set_Swi5(bool a);
                virtual void set_Mcm1_SFF(bool a);
                virtual void set_Clb5_6(bool a);
                virtual void set_MBF(bool a);
                virtual void set_Sic1(bool a);
                virtual void set_Clb1_2(bool a);

            protected:
                std::time_t _td;
        };
    }
}

#endif
