#ifndef __STOCHASTIC_MODEL__
#define __STOCHASTIC_MODEL__

#include "abstract_model.h"

#include <cstddef>
#include <cstdlib>

template<std::size_t Size, std::size_t MaxTime, std::size_t StaticTime = 1, bool Async = false>
class stochastic_model : public abstract_model<Size, MaxTime, StaticTime, Async>
{
    private:
        // Need this hack because of the template
        typedef abstract_model<Size, MaxTime, StaticTime, Async> super;

    public:
        // Redefinition of the superclass
        static const std::size_t node_number = super::node_number;
        typedef typename super::node_type node_type;

        // Type definition of the matrix
        typedef signed int coef_type;
        typedef std::size_t time_type;

        struct elem_type
        {
            coef_type coef;
            time_type time;
        };

        typedef elem_type matrix_type[node_number * node_number];

        stochastic_model(const matrix_type & matrix = {0}):
            super(),
            _matrix()
        {
            // Copy from the input to the matrix
            for(std::size_t i = 0 ; i < node_number * node_number ; i++)
            {
                _matrix[i] = matrix[i];
            }
        }

        virtual node_type rule(std::size_t i)
        {
            coef_type sum = 0;
            for(std::size_t j = 0 ; j < node_number ; j++)
            {
                // Test if the random let us to do the calcul
                if(_matrix[i * node_number + j].time > 0)
                {
                    unsigned long int r = std::rand() % _matrix[i * node_number + j].time;
                    if(r < (super::async_mode ? 1 : node_number))
                    {
                        if(super::_data[j])
                            sum += _matrix[i * node_number + j].coef;
                    }
                }
            }

            if(sum > 0)
                return true;
            if(sum < 0)
                return false;
            else
                return super::_data[i];
        }

    protected:
        matrix_type _matrix;
};

#endif
