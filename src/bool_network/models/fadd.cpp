#include "bool_network/models/fadd.h"

namespace bn
{
    namespace models
    {
        fadd::fadd(matrix_type const & m,
                std::size_t nbr_updated_node,
                state_type const & s):
            dynamic::matrix_model<Size>(m, nbr_updated_node, s)
        {
        }

        fadd fadd::wild_type(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::anti_oxidant(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::APAF1_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                9.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::BAX_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::BCL2_expr(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, // MOMP
                9.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::C8_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                9.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::C8_expr(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                -9.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::cFlip_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                -0.1f,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::cIAP_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                9.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::FADD_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  0,  0,  0, -2,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  0,  0,  0, -2,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::NFkB_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                9.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::NFkB_expr(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                -9.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::RIP1_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                9.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                3.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::XIAP_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                1.1f,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::z_VAD(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                0.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                0.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                9.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }

        fadd fadd::z_VAD_RIP1_del(std::size_t nbr_updated_node,
                state_type const & s)
        {
            static matrix_type const mat = {
                //  Sueil  TNF FAS RIP1 NFkB C8 cIAP ATP C3 ROS MOMP MPT
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // TNF
                0.0f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // FAS
                9.1f,  1,  1,  0,  0, -3,  0,  0,  0,  0,  0,  0, // RIP1
                3.1f,  0,  0,  2,  0,  0,  2,  0, -2,  0,  0,  0, // NFkB
                9.1f,  1,  1,  0, -4,  0,  0,  0,  1,  0,  0,  0, // C8
                0.1f,  0,  0,  0,  1,  0,  1,  0,  0,  0, -3,  0, // cIAP
                -0.1f,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, // ATP
                9.1f,  0,  0,  0, -2,  0,  0,  2,  0,  0,  2,  0, // C3
                0.1f,  0,  0,  1, -3,  0,  0,  0,  0,  0,  0,  1, // ROS
                0.1f,  0,  0,  0, -2,  1,  0,  0,  0,  0,  0,  3, // MOMP
                0.1f,  0,  0,  0, -2,  0,  0,  0,  0,  1,  0,  0, // MPT
            };
            return fadd(mat, nbr_updated_node, s);
        }


        std::time_t fadd::get_min_time() const
        {
            return 0;
        }

        bool fadd::get_TNF() const  { return dynamic::matrix_model<Size>::_state[0]; }
        bool fadd::get_FAS() const  { return dynamic::matrix_model<Size>::_state[1]; }
        bool fadd::get_RIP1() const { return dynamic::matrix_model<Size>::_state[2]; }
        bool fadd::get_NFkB() const { return dynamic::matrix_model<Size>::_state[3]; }
        bool fadd::get_C8() const   { return dynamic::matrix_model<Size>::_state[4]; }
        bool fadd::get_cIAP() const { return dynamic::matrix_model<Size>::_state[5]; }
        bool fadd::get_ATP() const  { return dynamic::matrix_model<Size>::_state[6]; }
        bool fadd::get_C3() const   { return dynamic::matrix_model<Size>::_state[7]; }
        bool fadd::get_ROS() const  { return dynamic::matrix_model<Size>::_state[8]; }
        bool fadd::get_MOMP() const { return dynamic::matrix_model<Size>::_state[9]; }
        bool fadd::get_MPT() const  { return dynamic::matrix_model<Size>::_state[10]; }

        void fadd::set_TNF(bool a)  { dynamic::matrix_model<Size>::_state[0] = a; }
        void fadd::set_FAS(bool a)  { dynamic::matrix_model<Size>::_state[1] = a; }
        void fadd::set_RIP1(bool a) { dynamic::matrix_model<Size>::_state[2] = a; }
        void fadd::set_NFkB(bool a) { dynamic::matrix_model<Size>::_state[3] = a; }
        void fadd::set_C8(bool a)   { dynamic::matrix_model<Size>::_state[4] = a; }
        void fadd::set_cIAP(bool a) { dynamic::matrix_model<Size>::_state[5] = a; }
        void fadd::set_ATP(bool a)  { dynamic::matrix_model<Size>::_state[6] = a; }
        void fadd::set_C3(bool a)   { dynamic::matrix_model<Size>::_state[7] = a; }
        void fadd::set_ROS(bool a)  { dynamic::matrix_model<Size>::_state[8] = a; }
        void fadd::set_MOMP(bool a) { dynamic::matrix_model<Size>::_state[9] = a; }
        void fadd::set_MPT(bool a)  { dynamic::matrix_model<Size>::_state[10] = a; }
    }
}
