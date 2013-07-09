#ifndef __BOOL_NETWORK_MODELS_FADD_H__
#define __BOOL_NETWORK_MODELS_FADD_H__

#include <ctime>
#include <cstddef>

#include "bool_network/dynamic/matrix_model.h"
#include "bool_network/abstract_models/fadd.h"

namespace bn
{
    namespace models
    {
        class fadd : public dynamic::matrix_model<11>, public abstract_models::fadd
        {
            public:
                static std::size_t const Size = 11;
                static std::size_t const size = dynamic::matrix_model<Size>::size;

                typedef typename dynamic::matrix_model<Size>::state_type state_type;
                typedef typename dynamic::matrix_model<Size>::matrix_type matrix_type;
                typedef typename dynamic::matrix_model<Size>::coef_type coef_type;

                static fadd wild_type(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd anti_oxidant(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd APAF1_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd BAX_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd BCL2_expr(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd C8_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd C8_expr(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd cFlip_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd cIAP_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd FADD_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd NFkB_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd NFkB_expr(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd RIP1_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd XIAP_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd z_VAD(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                static fadd z_VAD_RIP1_del(std::size_t nbr_updated_node,
                        state_type const & s = state_type());

                virtual std::time_t get_min_time() const;

                virtual bool get_TNF() const;
                virtual bool get_FAS() const;
                virtual bool get_RIP1() const;
                virtual bool get_NFkB() const;
                virtual bool get_C8() const;
                virtual bool get_cIAP() const;
                virtual bool get_ATP() const;
                virtual bool get_C3() const;
                virtual bool get_ROS() const;
                virtual bool get_MOMP() const;
                virtual bool get_MPT() const;

                virtual void set_TNF(bool);
                virtual void set_FAS(bool);
                virtual void set_RIP1(bool);
                virtual void set_NFkB(bool);
                virtual void set_C8(bool);
                virtual void set_cIAP(bool);
                virtual void set_ATP(bool);
                virtual void set_C3(bool);
                virtual void set_ROS(bool);
                virtual void set_MOMP(bool);
                virtual void set_MPT(bool);

            protected:
                fadd(matrix_type const & m,
                        std::size_t nbr_updated_node,
                        state_type const & s = state_type());

        };
    }
}

#endif
