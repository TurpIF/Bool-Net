#include "timed_model.h"
#include "cellBOOL.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

template<typename Model>
void simule_matrix()
{
    typedef std::map<Model, std::size_t> visited_type;
    visited_type visited;

    // Loop generating the every cell
    // There is 2^node_number type of cell.
    // The network has 12 nodes (with Cell_size) => 2^12 = 4096.
    // It's not very big so we can test all of this
    // A path is determinist.
    static const std::size_t N = static_cast<std::size_t>(std::pow(2, Model::node_number - 1));
    for(std::size_t i = 0 ; i < N ; i++)
    {
        // Definition of the initial state
        double initial_state[Model::node_number] = {
            0, //i & (0x1 << 11),//static_cast<int>(std::rand() % 2), //1, // Cell size
            static_cast<double>(i & (0x1 << 10)),//static_cast<int>(std::rand() % 2), //0, // Cln3
            static_cast<double>(i & (0x1 << 9)),//static_cast<int>(std::rand() % 2), //0, // SBF
            static_cast<double>(i & (0x1 << 8)),//static_cast<int>(std::rand() % 2), //0, // Cln1,2
            static_cast<double>(i & (0x1 << 7)),//static_cast<int>(std::rand() % 2), //0, // Cdh1
            static_cast<double>(i & (0x1 << 6)),//static_cast<int>(std::rand() % 2), //0, // Cdc20&Cdc14
            static_cast<double>(i & (0x1 << 5)),//static_cast<int>(std::rand() % 2), //0, // Swi5
            static_cast<double>(i & (0x1 << 4)),//static_cast<int>(std::rand() % 2), //0, // Mcm1/SFF
            static_cast<double>(i & (0x1 << 3)),//static_cast<int>(std::rand() % 2), //0, // Clb5,6
            static_cast<double>(i & (0x1 << 2)),//static_cast<int>(std::rand() % 2), //0, // MBF
            static_cast<double>(i & (0x1 << 1)),//static_cast<int>(std::rand() % 2), //0, // Sic1
            static_cast<double>(i & (0x1 << 0)),//static_cast<int>(std::rand() % 2), //0, // Clb1,2
        };

        // Creation of the cell and update
        cellBOOL<Model> c(initial_state);
        c.internal_update();

        bool find = false;
        for(typename visited_type::iterator it = visited.begin() ;
                it != visited.end() ; it++)
        {
            if(it->first.data() == c.model().data())
            {
                find = true;
                it->second++;
                break;
            }
        }
        if(!find)
        {
            visited.insert(std::pair<Model, std::size_t>(c.model(), 1));
        }
    }

    for(typename visited_type::const_iterator it = visited.begin() ;
            it != visited.end() ; it++)
    {
        const Model & m = it->first;
        //double ratio = static_cast<double>(it->second) / static_cast<double>(N) * 100;
        std::cout << std::setw(10) << it->second << " "
            << m.Cln3()
            << m.MBF()
            << m.SBF()
            << m.Cln1_2()
            << m.Cdh1()
            << m.Swi5()
            << m.Cdc20_Cdc14()
            << m.Clb5_6()
            << m.Sic1()
            << m.Clb1_2()
            << m.Mcm1_SFF()
            << std::endl;
    }
}

template<std::size_t MaxTime, signed int Ag = 1, signed int Ar = -1, std::size_t Td = 0>
class yeast_model : public timed_model<12, MaxTime, Td, true>
{
    public:
        // Hack cause of the template argument
        typedef timed_model<12, MaxTime, Td, true> super;

        typedef typename super::graph_type graph_type;
        typedef typename super::node_type node_type;
        typedef typename super::ref_node_type ref_node_type;
        typedef typename super::coef_type coef_type;

        static const coef_type ag = static_cast<coef_type>(Ag);
        static const coef_type ar = static_cast<coef_type>(Ar);

        yeast_model():
            super({
                    {ar, 1, 1},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, // Cell size
                    {ag, 1, 1},  {-1, Td, Td},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, // Cln3
                     {0, 0, 0}, {ag, 1, 1},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1}, // SBF
                     {0, 0, 0},  {0, 0, 0}, {ag, 1, 1},  {-1, Td, Td},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, // Cln1,2
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1},  {0, 0, 0}, {ag, 1, 1},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1}, // Cdh1
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {-1, Td, Td},  {0, 0, 0}, {ag, 1, 1},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ag, 1, 1}, // Cdc20&Cdc14
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ag, 1, 1},  {-1, Td, Td}, {ag, 1, 1},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1}, // Swi5
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {-1, Td, Td}, {ag, 1, 1},  {0, 0, 0},  {0, 0, 0}, {ag, 1, 1}, // Mcm1/SFF
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ag, 1, 1}, {ar, 1, 1},  {0, 0, 0}, // Clb5,6
                     {0, 0, 0}, {ag, 1, 1},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1}, // MBF
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1},  {0, 0, 0}, {ag, 1, 1}, {ag, 1, 1},  {0, 0, 0}, {ar, 1, 1},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1}, // Sic1
                     {0, 0, 0},  {0, 0, 0},  {0, 0, 0},  {0, 0, 0}, {ar, 1, 1}, {ar, 1, 1},  {0, 0, 0}, {ag, 1, 1}, {ag, 1, 1},  {0, 0, 0}, {ar, 1, 1},  {0, 0, 0}, // Clb1,2
                    })
        {
        }

        ref_node_type Cell_size()   { return super::_data[0]; }
        ref_node_type Cln3()        { return super::_data[1]; }
        ref_node_type SBF()         { return super::_data[2]; }
        ref_node_type Cln1_2()      { return super::_data[3]; }
        ref_node_type Cdh1()        { return super::_data[4]; }
        ref_node_type Cdc20_Cdc14() { return super::_data[5]; }
        ref_node_type Swi5()        { return super::_data[6]; }
        ref_node_type Mcm1_SFF()    { return super::_data[7]; }
        ref_node_type Clb5_6()      { return super::_data[8]; }
        ref_node_type MBF()         { return super::_data[9]; }
        ref_node_type Sic1()        { return super::_data[10]; }
        ref_node_type Clb1_2()      { return super::_data[11]; }

        node_type Cell_size() const   { return super::_data[0]; }
        node_type Cln3() const        { return super::_data[1]; }
        node_type SBF() const         { return super::_data[2]; }
        node_type Cln1_2() const      { return super::_data[3]; }
        node_type Cdh1() const        { return super::_data[4]; }
        node_type Cdc20_Cdc14() const { return super::_data[5]; }
        node_type Swi5() const        { return super::_data[6]; }
        node_type Mcm1_SFF() const    { return super::_data[7]; }
        node_type Clb5_6() const      { return super::_data[8]; }
        node_type MBF() const         { return super::_data[9]; }
        node_type Sic1() const        { return super::_data[10]; }
        node_type Clb1_2() const      { return super::_data[11]; }
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "C = 30 ; ag = 1 ; ar = -10 ; td = 4" << std::endl;
    simule_matrix<yeast_model<30, 1, -10, 4> >();
    std::cout << std::endl;

    std::cout << "C = 20 ; ag = 1 ; ar = -1 ; td = 1" << std::endl;
    simule_matrix<yeast_model<20, 1, -1, 1> >();
    std::cout << std::endl;

    std::cout << "C = 20 ; ag = 150 ; ar = -150 ; td = 1" << std::endl;
    simule_matrix<yeast_model<20, 150, -150, 1> >();
    std::cout << std::endl;

    std::cout << "C = 85 ; ag = 150 ; ar = -150 ; td = 10" << std::endl;
    simule_matrix<yeast_model<85, 150, -150, 10> >();
    std::cout << std::endl;

    std::cout << "C = 20 ; ag = 1000 ; ar = -10000 ; td = 1" << std::endl;
    simule_matrix<yeast_model<20, 1000, -10000, 1> >();
    std::cout << std::endl;

    std::cout << "C = 225 ; ag = 1000 ; ar = -10000 ; td = 42" << std::endl;
    simule_matrix<yeast_model<225, 1000, -10000, 42> >();
    std::cout << std::endl;

    std::cout << "C = 20 ; ag = 2 ; ar = -1 ; td = 1" << std::endl;
    simule_matrix<yeast_model<20, 2, -1, 1> >();
    std::cout << std::endl;

    std::cout << "C = 20 ; ag = 10000 ; ar = -1 ; td = 1" << std::endl;
    simule_matrix<yeast_model<20, 10000, -1, 1> >();
    std::cout << std::endl;

    return 0;
}
