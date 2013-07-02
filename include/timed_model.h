#ifndef __TIMED_MODEL__
#define __TIMED_MODEL__

#include "abstract_model.h"

#include <cstddef>
#include <cstdlib>

template<std::size_t Size, std::size_t MaxTime, std::size_t StaticTime = 1, bool Async = false>
class timed_model : public abstract_model<Size, MaxTime, StaticTime, Async>
{
    private:
        // Need this hack because of the template
        typedef abstract_model<Size, MaxTime, StaticTime, Async> super;

    public:
        // Redefinition of the superclass
        static const std::size_t node_number = super::node_number;
        static const std::size_t converge_time = super::converge_time;
        static const std::size_t static_time = super::static_time;
        static const bool async_mode = super::async_mode;

        typedef typename super::node_type node_type;
        typedef typename super::graph_type graph_type;
        typedef typename super::ref_node_type ref_node_type;

        // Type definition of the matrix
        typedef signed int coef_type;
        typedef std::size_t time_type;

        struct transition_type
        {
            coef_type coef;
            time_type time;
            time_type time_ori;
            bool reset_on_activation;
        };

        typedef transition_type matrix_type[node_number * node_number];

        timed_model(const matrix_type & matrix = {0}):
            super(),
            _matrix()
        {
            // Copy from the input to the matrix
            for(std::size_t i = 0 ; i < node_number * node_number ; i++)
            {
                _matrix[i] = matrix[i];
            }
        }

        graph_type & data()
        {
            return super::_data;
        };

        const graph_type & data() const
        {
            return super::_data;
        }

        virtual node_type rule(std::size_t i)
        {
            coef_type sum = 0;
            for(std::size_t j = 0 ; j < node_number ; j++)
            {
                if(super::_data[j])
                {
                    if(_matrix[i * node_number + j].time > 0)
                        _matrix[i * node_number + j].time--;

                    // Test if the time let us to do the calcul
                    if(_matrix[i * node_number + j].time == 0)
                    {
                        sum += _matrix[i * node_number + j].coef;
                        //_matrix[i * node_number + j].time = _matrix[i * node_number + j].time_ori;
                    }
                }
            }

            if(sum > 0)
            {
                for(std::size_t j = 0 ; j < node_number ; j++)
                {
                    if(_matrix[i * node_number + j].reset_on_activation)
                        _matrix[i * node_number + j].time = _matrix[i * node_number + j].time_ori;
                }
                return true;
            }
            if(sum < 0)
            {
                for(std::size_t j = 0 ; j < node_number ; j++)
                {
                    _matrix[i * node_number + j].time = _matrix[i * node_number + j].time_ori;
                }
                return false;
            }
            else
                return super::_data[i];
        }

    protected:
        matrix_type _matrix;
};

#endif

