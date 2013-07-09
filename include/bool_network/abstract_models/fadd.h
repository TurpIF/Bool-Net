/*!
 * \file bool_network/abstract_models/fadd.h
 * \author Turpin Pierre
 * \brief Definition of an interface representing a model of FADD
 */
#ifndef __BOOL_NETWORK_ABSTRACT_MODELS_FADD_H__
#define __BOOL_NETWORK_ABSTRACT_MODELS_FADD_H__

#include <ostream>

namespace bn
{
    namespace abstract_models
    {
        /*!
         * \class fadd
         * \brief Model of FADD
         *
         * Lists all the possible interactions with a model
         * of the FADD (Fas-Associated protein with Death Domain)
         */
        class fadd
        {
            public:
                /*!
                 * \brief Get the TNF
                 */
                virtual bool get_TNF() const = 0;

                /*!
                 * \brief Get the FAS
                 */
                virtual bool get_FAS() const = 0;

                /*!
                 * \brief Get the RIP1
                 */
                virtual bool get_RIP1() const = 0;

                /*!
                 * \brief Get the NFkB
                 */
                virtual bool get_NFkB() const = 0;

                /*!
                 * \brief Get the CASP8
                 */
                virtual bool get_C8() const = 0;

                /*!
                 * \brief Get the cIAP
                 */
                virtual bool get_cIAP() const = 0;

                /*!
                 * \brief Get the ATP
                 */
                virtual bool get_ATP() const = 0;

                /*!
                 * \brief Get the CASP3
                 */
                virtual bool get_C3() const = 0;

                /*!
                 * \brief Get the ROS
                 */
                virtual bool get_ROS() const = 0;

                /*!
                 * \brief Get the MOMP
                 */
                virtual bool get_MOMP() const = 0;

                /*!
                 * \brief Get the MPT
                 */
                virtual bool get_MPT() const = 0;

                /*!
                 * \brief Set the TNF
                 */
                virtual void set_TNF(bool) = 0;

                /*!
                 * \brief Set the FAS
                 */
                virtual void set_FAS(bool) = 0;

                /*!
                 * \brief Set the RIP1
                 */
                virtual void set_RIP1(bool) = 0;

                /*!
                 * \brief Set the NFkB
                 */
                virtual void set_NFkB(bool) = 0;

                /*!
                 * \brief Set the CASP8
                 */
                virtual void set_C8(bool) = 0;

                /*!
                 * \brief Set the cIAP
                 */
                virtual void set_cIAP(bool) = 0;

                /*!
                 * \brief Set the ATP
                 */
                virtual void set_ATP(bool) = 0;

                /*!
                 * \brief Set the CASP3
                 */
                virtual void set_C3(bool) = 0;

                /*!
                 * \brief Set the ROS
                 */
                virtual void set_ROS(bool) = 0;

                /*!
                 * \brief Set the MOMP
                 */
                virtual void set_MOMP(bool) = 0;

                /*!
                 * \brief Set the MPT
                 */
                virtual void set_MPT(bool) = 0;

                /*!
                 * \brief Overloaded operator to show a FADD model.
                 * \param out The output stream to use
                 * \param m The model  to show
                 * \return Return the output stream after the operation
                 */
                friend std::ostream & operator<<(std::ostream &, abstract_models::fadd const &);
        };
    }
}

#endif
