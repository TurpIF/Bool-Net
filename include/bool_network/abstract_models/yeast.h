/*!
 * \file bool_network/abstract_models/yeast.h
 * \author Turpin Pierre
 * \brief Definition of an interface representing a yeast's model
 */
#ifndef __BOOL_NETWORK_ABSTRACT_MODELS_YEAST_H__
#define __BOOL_NETWORK_ABSTRACT_MODELS_YEAST_H__

#include <ostream>

namespace bn
{
    namespace abstract_models
    {
        /*!
         * \class yeast
         * \brief Yeast model
         *
         * Lists all the possible interactions with a model
         * representing the life of a yeast.
         */
        class yeast
        {
            public:
                /*!
                 * \brief Get the Cell Size ckeckpoint
                 */
                virtual bool get_Cell_size() const = 0;

                /*!
                 * \brief Get the Cln3
                 */
                virtual bool get_Cln3() const = 0;

                /*!
                 * \brief Get the SBF
                 */
                virtual bool get_SBF() const = 0;

                /*!
                 * \brief Get the Cln1,2
                 */
                virtual bool get_Cln1_2() const = 0;

                /*!
                 * \brief Get the Cdh1
                 */
                virtual bool get_Cdh1() const = 0;

                /*!
                 * \brief Get the Cdc20&Cdc14
                 */
                virtual bool get_Cdc20_Cdc14() const = 0;

                /*!
                 * \brief Get tje Swi5
                 */
                virtual bool get_Swi5() const = 0;

                /*!
                 * \brief Get the Mcm1/SFF
                 */
                virtual bool get_Mcm1_SFF() const = 0;

                /*!
                 * \brief Get the Clb5,6
                 */
                virtual bool get_Clb5_6() const = 0;

                /*!
                 * \brief Get the MBF
                 */
                virtual bool get_MBF() const = 0;

                /*!
                 * \brief Get the Sic1
                 */
                virtual bool get_Sic1() const = 0;

                /*!
                 * \brief Get the Clb1,2
                 */
                virtual bool get_Clb1_2() const = 0;

                /*!
                 * \brief Set the Cell Size ckeckpoint
                 */
                virtual void set_Cell_size(bool) = 0;

                /*!
                 * \brief Set the Cell Size ckeckpoint
                 */
                virtual void set_Cln3(bool) = 0;

                /*!
                 * \brief Set the SBF
                 */
                virtual void set_SBF(bool) = 0;

                /*!
                 * \brief Set the Cln1,2
                 */
                virtual void set_Cln1_2(bool) = 0;

                /*!
                 * \brief Set the Cdh1
                 */
                virtual void set_Cdh1(bool) = 0;

                /*!
                 * \brief Set the Cdc20&Cdc14
                 */
                virtual void set_Cdc20_Cdc14(bool) = 0;

                /*!
                 * \brief Set the Swi5
                 */
                virtual void set_Swi5(bool) = 0;

                /*!
                 * \brief Set the Mcm1/SFF
                 */
                virtual void set_Mcm1_SFF(bool) = 0;

                /*!
                 * \brief Set the Clb5,6
                 */
                virtual void set_Clb5_6(bool) = 0;

                /*!
                 * \brief Set the MBF
                 */
                virtual void set_MBF(bool) = 0;

                /*!
                 * \brief Set the Sic1
                 */
                virtual void set_Sic1(bool) = 0;

                /*!
                 * \brief Set the Clb1,2
                 */
                virtual void set_Clb1_2(bool) = 0;

                /*!
                 * \brief Overloaded operator to show a yeast model.
                 * \param out The output stream to use
                 * \param m The model  to show
                 * \return Return the output stream after the operation
                 */
                friend std::ostream & operator<<(std::ostream &, abstract_models::yeast const &);
        };
    }
}

#endif
