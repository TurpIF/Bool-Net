/*!
 * \file include/models/gata1.h
 * \author Turpin Pierre
 * \brief Definition of an interface of a model representing the activation of GATA-1 by Epo
 */
#ifndef __MODELS_GATA1_H__
#define __MODELS_GATA1_H__

#include <ostream>

namespace models
{
    /*!
     * \class gata1
     * \brief Model representing the activation of GATA-1 by Epo
     *
     * Lists all the possible interactions with a model
     * representing the activation of GATA-1 by a certain amount of Epo.
     */
    class gata1
    {
        public:
            /*!
             * \brief Get the Epo (erytropoietin)
             */
            virtual bool get_Epo() const = 0;

            /*!
             * \brief Get the GATA-1
             */
            virtual bool get_GATA1() const = 0;

            /*!
             * \brief Set the Epo (erytropoietin)
             */
            virtual void set_Epo(bool) = 0;

            /*!
             * \brief Set the GATA-1
             */
            virtual void set_GATA1(bool) = 0;

            /*!
             * \brief Overloaded operator to show a GATA-1 model.
             * \param out The output stream to use
             * \param m The model  to show
             * \return Return the output stream after the operation
             */
            friend std::ostream & operator<<(std::ostream &, models::gata1 const &);
    };
}

#endif
