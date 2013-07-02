#ifndef __CELLBOOL_H__
#define __CELLBOOL_H__

// =================================================================
//                              Libraries
// =================================================================
#include <vector>
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <iostream>

// =================================================================
//                            Project Files
// =================================================================

// =================================================================
//                          Class declarations
// =================================================================
template<typename Model>
class cellBOOL
{
    public :
        static const std::size_t node_number = Model::node_number;
        static const std::size_t converge_time = Model::converge_time;
        static const std::size_t static_time = Model::static_time;
        static const bool async_mode = Model::async_mode;

        typedef typename Model::graph_type graph_type;
        typedef std::vector<graph_type> visited_type;
        typedef std::size_t time_type;

        // =================================================================
        //                             Constructors
        // =================================================================
        cellBOOL(double initial_state[node_number]):
            _time(0),
            _visited(),
            _begin_cycle(_visited.end()),
            _in_cycle(false),
            _static_chrono(static_time),
            _model()
        {
            for(std::size_t i = 0 ; i < node_number ; i++)
            {
                _model.data()[node_number - i - 1] = false;
                if(initial_state[i] > 0.5)
                    _model.data()[node_number - i - 1] = true;
            }
            _visited.push_back(_model.data());
        }

        // =================================================================
        //                             Destructors
        // =================================================================
        ~cellBOOL()
        {
        }

        // =================================================================
        //                              Accessors
        // =================================================================
        const Model & model() const
        {
            return _model;
        }

        Model & model()
        {
            return _model;
        }

        // =================================================================
        //                            Public Methods
        // =================================================================
        void internal_update()
        {
            for(std::size_t i = 0 ; i < converge_time ; i++)
            {
                // std::string s = _model.data().to_string();
                // std::reverse(s.begin(), s.end());
                // std::cout << s << std::endl;
                // 500ms
                if(true || !_in_cycle)
                {
                    intracellular_update();
                }
                else
                {
                    // If there is a cycle, we jump directly to the final result and break the loop
                    _time += converge_time - i - 1;
                    std::ptrdiff_t d = std::distance(_begin_cycle, _visited.end());

                    if(d == 0)
                        _model.data() = *_begin_cycle;
                    else
                        _model.data() = *(_begin_cycle + _time % d);

                    break;
                }
            }
        }

        // =================================================================
        //                           Public Attributes
        // =================================================================

    protected :

        // =================================================================
        //                         Forbidden Constructors
        // =================================================================
        cellBOOL()
        {
            std::cerr << "ERROR : Call to forbidden constructor in file " << __FILE__ << " : l" << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }

        cellBOOL(const cellBOOL &)
        {
            std::cerr << "ERROR : Call to forbidden constructor in file " << __FILE__ << " : l" << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }

        cellBOOL & operator=(const cellBOOL &)
        {
            std::cerr << "ERROR : Call to forbidden copie operator in file " << __FILE__ << " : l" << __LINE__ << std::endl;
            exit(EXIT_FAILURE);
        }

        // =================================================================
        //                           Protected Methods
        // =================================================================
        void intracellular_update()
        {
            graph_type g = _model.data();
            std::size_t list_modified[node_number] = {0};
            std::size_t size_modified = 0;

            // Searching for modified nodes
            for(std::size_t i = 0 ; i < node_number ; i++)
            {
                g[i] = _model.rule(i);

                // If one if modified, this one is stored to potentionnaly be keep
                if(g[i] != _model.data()[i])
                {
                    list_modified[size_modified] = i;
                    size_modified++;
                }
            }

            // The network is stabilized
            if(size_modified == 0)
            {
                // It's like a cycle of one step
                _begin_cycle = _visited.end();
                if(_static_chrono == 0)
                    _in_cycle = true;
                _static_chrono--;
            }
            else
            {
                if(!async_mode)
                {
                    // Pick up an random modified node and keep the modification in the graph
                    std::size_t picked = std::rand() % size_modified;
                    _model.data()[list_modified[picked]] = g[list_modified[picked]];
                    //std::size_t picked = std::rand() % node_number;
                    //_model.data()[picked] = g[picked];
                }
                else
                {
                    // This line turn the evolution in a async mode (all state are changed)
                    _model.data() = g;
                }

                // If the graph is already met, it's  cycle
                typename visited_type::iterator it = std::find(_visited.begin(), _visited.end(), _model.data());
                if(it != _visited.end())
                {
                    // It's now useless to recalculate the modification
                    // we can use the visited container
                    _begin_cycle = it;
                    if(_static_chrono == 0)
                        _in_cycle = true;
                    _static_chrono--;
                }
                else
                {
                    // Else, we store the graph in the visited container
                    _visited.push_back(_model.data());
                    _in_cycle = false;
                    _static_chrono = static_time;
                }
            }

            // The local time increment
            _time++;
        }

        // =================================================================
        //                          Protected Attributes
        // =================================================================
        time_type _time;
        visited_type _visited;
        typename visited_type::iterator _begin_cycle;
        bool _in_cycle;
        std::size_t _static_chrono;
        Model _model;

        // =================================================================
        //                           Private Methods
        // =================================================================

    private :
};

#endif // __CELLBOOL_H__
