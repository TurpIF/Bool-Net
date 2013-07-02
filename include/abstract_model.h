#ifndef __ABSTRACTMODEL_H__
#define __ABSTRACTMODEL_H__

// =================================================================
//                              Libraries
// =================================================================
#include <cstddef>
#include <bitset>

// =================================================================
//                          Class declarations
// =================================================================

// Base classe of all models.
// Template arguments let the user to do a static config of the model.
// Size represents the graph size, so the number of node
// MaxTime represents the maximum time the boolean network will evolve a cell
// StaticTime represents the time, the network have to wait while the graph is static before considering it's definetly static
// Async represents the choice of using an async mode for the evolution (all protein are updated at the same time) or not.
template<std::size_t Size, std::size_t MaxTime, std::size_t StaticTime = 1, bool Async = false>
class abstract_model
{
    public:
        static const std::size_t node_number = Size;
        static const std::size_t converge_time = MaxTime;
        static const std::size_t static_time = StaticTime;
        static const bool async_mode = Async;

        typedef std::bitset<node_number> graph_type;
        typedef bool node_type;
        typedef typename graph_type::reference ref_node_type;

        // =================================================================
        //                             Constructors
        // =================================================================
        abstract_model():
            _data()
        {
        }

        // =================================================================
        //                             Destructors
        // =================================================================
        virtual ~abstract_model()
        {
        }

        // =================================================================
        //                            Public Methods
        // =================================================================
        virtual node_type rule(std::size_t) = 0;

        const graph_type & data() const
        {
            return _data;
        }

        graph_type & data()
        {
            return _data;
        }

        bool operator<(const abstract_model & model) const
        {
            return _data.to_ulong() < model._data.to_ulong();
        }

    protected:
        graph_type _data;
};

#endif
