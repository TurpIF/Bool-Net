#ifndef __ABSTRACTMATRIXMODEL_H__
#define __ABSTRACTMATRIXMODEL_H__

// =================================================================
//                              Libraries
// =================================================================
#include <cstddef>
#include <bitset>

// =================================================================
//                            Project Files
// =================================================================
#include "abstract_model.h"

typedef signed int coef_type;

// =================================================================
//                          Class declarations
// =================================================================

// Results enumeration
enum Result {Activate, Desactivate, NoChange};

// Usefull operator for some models
struct sum_operator
{
    Result operator()(coef_type * matrix, unsigned long int data, std::size_t line, std::size_t width) const
    {
        // Sum of the product between the state of an protein by his coef in the matrix
        coef_type sum = 0;
        for(std::size_t j = 0 ; j < width ; j++)
        {
            if(data & (1 << j))
                sum += matrix[line * width + j];
        }

        if(sum > 0)
            return Activate;
        else if(sum < 0)
            return Desactivate;
        return NoChange;
    }
};

struct and_operator
{
    Result operator()(coef_type * matrix, unsigned long int data, std::size_t line, std::size_t width) const
    {
        bool used = false;
        for(std::size_t j = 0 ; j < width ; j++)
        {
            if(matrix[line * width + j])
            {
                used = true;
                if(!(data & (1 << j)) && matrix[line * width + j])
                    return Desactivate;
            }
        }

        if(used)
            return Activate;
        else
            return NoChange;
    }
};

template<typename Operator, std::size_t Size, std::size_t MaxTime, std::size_t StaticTime = 1, bool Async = false>
class matrix_model : public abstract_model<Size, MaxTime, StaticTime, Async>
{
    private:
        // Need this hack because of the template
        typedef abstract_model<Size, MaxTime, StaticTime, Async> super;

    public:
        // Redefinition of the superclass
        static const std::size_t node_number = super::node_number;
        typedef typename super::node_type node_type;

        // Type definition of the matrix
        typedef ::coef_type coef_type;
        typedef coef_type matrix_type[node_number * node_number];

        // Type definition of the degradation table
        typedef std::size_t degradation_type;
        typedef degradation_type table_type[node_number];

        // =================================================================
        //                             Constructors
        // =================================================================
        matrix_model(const matrix_type & matrix = {0},
                const table_type & table_deg = {0},
                const table_type & table_anti_deg = {0},
                const Operator & op = Operator()):
            super(),
            _matrix(),
            _table_deg(),
            _table_anti_deg(),
            _current_table_deg(),
            _current_table_anti_deg(),
            _operator(op)
        {
            // Copy from the input to the matrix
            for(std::size_t i = 0 ; i < node_number * node_number ; i++)
            {
                _matrix[i] = matrix[i];
            }

            // Copy from the input to the table
            for(std::size_t i = 0 ; i < node_number ; i++)
            {
                _table_deg[i] = table_deg[i];
                _table_anti_deg[i] = table_anti_deg[i];
                _current_table_deg[i] = _table_deg[i];
                _current_table_anti_deg[i] = _table_anti_deg[i];
            }
        }

        // =================================================================
        //                            Public Methods
        // =================================================================
        virtual node_type rule(std::size_t i)
        {
            // Do the predicat of the existance
            Result result = _operator(_matrix, super::_data.to_ulong(), i, node_number);

            // Decrease the counter of the time before the protein is degrated if there is no good result
            // Else put the counter to the initial amount of time
            if(result == Activate)
            {
                _current_table_deg[i] = _table_deg[i];
                return true;
            }
            else if(result == Desactivate)
            {
                _current_table_anti_deg[i] = _table_anti_deg[i];
                return false;
            }
            else if(result == NoChange)
            {
                if(super::_data[i])
                {
                    if(_table_deg[i] > 0)
                    {
                        _current_table_deg[i]--;
                        if(_current_table_deg[i] == 0)
                        {
                            _current_table_deg[i] = _table_deg[i];
                            return false;
                        }
                    }
                    _current_table_anti_deg[i] = _table_anti_deg[i];

                    return true;
                }

                if(_table_anti_deg[i] > 0)
                {
                    _current_table_anti_deg[i]--;
                    if(_current_table_anti_deg[i] == 0)
                    {
                        _current_table_anti_deg[i] = _table_anti_deg[i];
                        return true;
                    }
                }

                _current_table_deg[i] = _table_deg[i];
                return false;
            }
            return false;
        }

    protected:
        matrix_type _matrix;
        table_type _table_deg;
        table_type _table_anti_deg;
        table_type _current_table_deg;
        table_type _current_table_anti_deg;
        Operator _operator;
};

#endif

