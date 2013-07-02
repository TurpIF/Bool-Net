#include "cellBOOL.h"
#include "matrix_model.h"

#include <cstddef>
#include <cstdlib>
#include <ctime>

template <std::size_t N>
struct predicat
{
    Result operator()(coef_type * matrix, unsigned long int data, std::size_t line, std::size_t width) const
    {
        if(false && line == N - 1)
        {
            return (data & (1 << (width - 1)) || data & (1 << width - 2)) ? Activate : Desactivate;
        }
        else
        {
            return sum_operator()(matrix, data, line, width);
            // return and_operator()(matrix, data, line, width);
        }
    }
};

template<std::size_t SizePath, std::size_t Td = 0>
class tf_model : public matrix_model<predicat<SizePath + 1>, SizePath + 1, 1, 0, true>
{
    public:
        // Hack cause of the template argument
        typedef matrix_model<predicat<SizePath + 1>, SizePath + 1, 1, 0, true> super;

        typedef typename super::graph_type graph_type;
        typedef typename super::ref_node_type ref_node_type;

        static const std::size_t node_number = super::node_number;

        tf_model():
            super()
        {
            super::_matrix[0] = 1;
            for(std::size_t i = 0 ; i < node_number ; i++)
            {
                if(i + 1 < node_number)
                {
                    //for(std::size_t j = 0 ; j < i + 1 ; j++)
                    //    super::_matrix[(i + 1) * node_number + j] = 1;
                    //super::_matrix[(i + 1) * node_number + i] = 1;
                    super::_matrix[(i + 1) * node_number] = 1;
                }

                if(i < node_number - 1)
                {
                    //super::_table_deg[i] = 1;
                    //super::_current_table_deg[i] = 1;
                }
                else
                {
                    //super::_table_deg[i] = Td;
                    //super::_current_table_deg[i] = Td;
                }
            }
        }

        ref_node_type ligand()
        {
            return super::_data[0];
        }

        ref_node_type tf()
        {
            return super::_data[node_number - 1];
        }
};

int main()
{
    std::srand(std::time(0));

    static const std::size_t N_node = 10;
    static const std::size_t stop = 50;
    typedef tf_model<N_node> Model;

    double initial_state[Model::node_number] = {1, 0};

    std::size_t n = 0;
    for(std::size_t j = 0 ; j < 1000 ; j++)
    {
        cellBOOL<Model> c(initial_state);
        std::size_t i = 0;
        while(c.model().tf() != true)
        //for(std::size_t i = 0 ; i < 70 ; i++)
        {
            if(i >= stop)
                c.model().ligand() = false;
            else
                c.model().ligand() = true;
            c.model().ligand() = true;

            c.internal_update();
            //std::cout << "Ligand : " << c.model().ligand()
            //    << ", TF : " << c.model().tf() << std::endl;
            i++;
        }
        //std::cout << std::endl;
        n += i;
    }

    std::cout << n << std::endl;
    std::cout << static_cast<double>(n) / 1000.0 << std::endl;

    return 0;
}
