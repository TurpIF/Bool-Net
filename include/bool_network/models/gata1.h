#ifndef __BOOL_NETWORK_MODELS_GATA1_H__
#define __BOOL_NETWORK_MODELS_GATA1_H__

#include <ctime>
#include <cstddef>

#include "bool_network/dynamic/timed_matrix_model.h"
#include "bool_network/abstract_models/gata1.h"

namespace bn
{
    namespace models
    {
        class gata1 : public dynamic::matrix_model<2, dynamic::timed_coef>, public abstract_models::gata1
        {
            public:
                static std::size_t const Size = 2;
                static std::size_t const size = dynamic::matrix_model<Size>::size;

                typedef typename dynamic::matrix_model<Size, dynamic::timed_coef>::state_type state_type;
                typedef typename dynamic::matrix_model<Size, dynamic::timed_coef>::matrix_type matrix_type;
                typedef typename dynamic::matrix_model<Size, dynamic::timed_coef>::coef_type coef_type;

                gata1(std::time_t const & td,
                        state_type const & s = state_type());

                virtual std::time_t get_min_time() const;

                virtual bool get_Epo() const;
                virtual bool get_GATA1() const;

                virtual void set_Epo(bool a);
                virtual void set_GATA1(bool a);

            protected:
                std::time_t _td;
        };
    }
}

#endif
