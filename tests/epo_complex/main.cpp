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
    static const std::size_t N = 1;//static_cast<std::size_t>(std::pow(2, Model::node_number - 1));
    for(std::size_t i = 0 ; i < N ; i++)
    {
        // Definition of the initial state
        double initial_state[Model::node_number] = {
            1, //i & (0x1 << 11),//static_cast<int>(std::rand() % 2), //1, // Cell size
            0, //static_cast<double>(i & (0x1 << 10)),//static_cast<int>(std::rand() % 2), //0, // Cln3
            0, //static_cast<double>(i & (0x1 << 9)),//static_cast<int>(std::rand() % 2), //0, // SBF
            0, //static_cast<double>(i & (0x1 << 8)),//static_cast<int>(std::rand() % 2), //0, // Cln1,2
            0, //static_cast<double>(i & (0x1 << 7)),//static_cast<int>(std::rand() % 2), //0, // Cdh1
            0, //static_cast<double>(i & (0x1 << 6)),//static_cast<int>(std::rand() % 2), //0, // Cdc20&Cdc14
            0, //static_cast<double>(i & (0x1 << 5)),//static_cast<int>(std::rand() % 2), //0, // Swi5
            0, //static_cast<double>(i & (0x1 << 4)),//static_cast<int>(std::rand() % 2), //0, // Mcm1/SFF
            0, //static_cast<double>(i & (0x1 << 3)),//static_cast<int>(std::rand() % 2), //0, // Clb5,6
            0, //static_cast<double>(i & (0x1 << 2)),//static_cast<int>(std::rand() % 2), //0, // MBF
            0, //static_cast<double>(i & (0x1 << 1)),//static_cast<int>(std::rand() % 2), //0, // Sic1
            0, //static_cast<double>(i & (0x1 << 0)),//static_cast<int>(std::rand() % 2), //0, // Clb1,2
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
            << m.Epo()
            << m.EpoRJD()
            << m.PI3K()
            << m.PIP2_3()
            << m.AKT_PIP3()
            << m.AKTp()
            << m.AKTpp()
            << m.GATA_1()
            << m.EpoRmRNAn()
            << m.EpoRmRNAc()
            << m.EpoR()
            << m.EpoRJ()
            << std::endl;
    }
}

template<std::size_t MaxTime, signed int Ag = 1, signed int Ar = -1, std::size_t Td = 0>
class epo_model : public timed_model<12, MaxTime, Td, true>
{
    private:
        // Hack cause of the template argument
        typedef timed_model<12, MaxTime, Td, true> super;

    public:
        static const unsigned int node_number = super::node_number;
        static const std::size_t converge_time = super::converge_time;
        static const std::size_t static_time = super::static_time;
        static const bool async_mode = super::async_mode;

        typedef typename super::graph_type graph_type;
        typedef typename super::node_type node_type;
        typedef typename super::ref_node_type ref_node_type;
        typedef typename super::coef_type coef_type;
        typedef typename super::time_type time_type;

        static const coef_type ag = static_cast<coef_type>(Ag);
        static const coef_type ar = static_cast<coef_type>(Ar);

        epo_model(time_type const & k1,
                time_type const & k2,
                time_type const & k3,
                time_type const & k4,
                time_type const & k5,
                time_type const & k6,
                time_type const & k7,
                time_type const & k8,
                time_type const & k9,
                time_type const & k10,
                time_type const & k11,
                time_type const & k12,
                time_type const & k13,
                time_type const & k14,
                time_type const & k15,
                time_type const & k16,
                time_type const & k17,
                time_type const & k18
                ):
            super({
                    // Epo           EpoRJD           PI3K           PIP2_3         AKT_PIP3          AKTp            AKTpp          GATA_1         EpoRmRNAn       EpoRmRNAc         EpoR           EpoRJ
                 {ar, k1, k1, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // Epo
                 {ag, k1, k1, false},   {ar, k2, k2, true},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, {ag, k18, k18, false}, // EpoRJD
                    {0, 0, 0, false},   {ag, k3, k3, false},   {ar, k4, k4, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // PI3K
                    {0, 0, 0, false},      {0, 0, 0, false},   {ag, k5, k5, false},   {ar, k6, k6, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // PIP2_3
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},   {ag, k7, k7, false},   {ar, k8, k8, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // AKT_PIP3
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},   {ag, k8, k8, false},   {ar, k9, k9, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // AKTp
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},   {ag, k9, k9, false},   {ar, k9, k9, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // AKTpp
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, {ag, k10, k10, false}, {ar, k11, k11, true},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // GATA_1
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, {ag, k12, k12, false}, {ar, k13, k13, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, // EpoRmRNAn
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, {ag, k13, k13, false}, {ar, k14, k14, true},      {0, 0, 0, false},      {0, 0, 0, false}, // EpoRmRNAc
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, {ag, k15, k15, false}, {ar, k16, k16, false},      {0, 0, 0, false}, // EpoR
                    {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false},      {0, 0, 0, false}, {ag, k16, k16, false}, {ar, k17, k17, true}, // EpoRJ
                    })
        {
        }

        graph_type & data()
        {
            return super::_data;
        };

        const graph_type & data() const
        {
            return super::_data;
        }

        ref_node_type Epo()       { return super::_data[0]; }
        ref_node_type EpoRJD()    { return super::_data[1]; }
        ref_node_type PI3K()      { return super::_data[2]; }
        ref_node_type PIP2_3()    { return super::_data[3]; }
        ref_node_type AKT_PIP3()  { return super::_data[4]; }
        ref_node_type AKTp()      { return super::_data[5]; }
        ref_node_type AKTpp()     { return super::_data[6]; }
        ref_node_type GATA_1()    { return super::_data[7]; }
        ref_node_type EpoRmRNAn() { return super::_data[8]; }
        ref_node_type EpoRmRNAc() { return super::_data[9]; }
        ref_node_type EpoR()      { return super::_data[10]; }
        ref_node_type EpoRJ()     { return super::_data[11]; }

        node_type Epo() const       { return super::_data[0]; }
        node_type EpoRJD() const    { return super::_data[1]; }
        node_type PI3K() const      { return super::_data[2]; }
        node_type PIP2_3() const    { return super::_data[3]; }
        node_type AKT_PIP3() const  { return super::_data[4]; }
        node_type AKTp() const      { return super::_data[5]; }
        node_type AKTpp() const     { return super::_data[6]; }
        node_type GATA_1() const    { return super::_data[7]; }
        node_type EpoRmRNAn() const { return super::_data[8]; }
        node_type EpoRmRNAc() const { return super::_data[9]; }
        node_type EpoR() const      { return super::_data[10]; }
        node_type EpoRJ() const     { return super::_data[11]; }
};

template<std::size_t k1,
    std::size_t k2,
    std::size_t k3,
    std::size_t k4,
    std::size_t k5,
    std::size_t k6,
    std::size_t k7,
    std::size_t k8,
    std::size_t k9,
    std::size_t k10,
    std::size_t k11,
    std::size_t k12,
    std::size_t k13,
    std::size_t k14,
    std::size_t k15,
    std::size_t k16,
    std::size_t k17,
    std::size_t k18,
    std::size_t MaxTime, signed int Ag = 1, signed int Ar = -1, std::size_t Td = 0>
class epo_model_wrap : public epo_model<MaxTime, Ag, Ar, Td>
{
    private:
        // Hack cause of the template argument
        typedef epo_model<MaxTime, Ag, Ar, Td> super;

    public:
        static const unsigned int node_number = super::node_number;
        static const std::size_t converge_time = super::converge_time;
        static const std::size_t static_time = super::static_time;
        static const bool async_mode = super::async_mode;

        typedef typename super::graph_type graph_type;
        typedef typename super::node_type node_type;
        typedef typename super::ref_node_type ref_node_type;
        typedef typename super::coef_type coef_type;
        typedef typename super::time_type time_type;

        epo_model_wrap():
            epo_model<MaxTime, Ag, Ar, Td>(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10, k11, k12, k13, k14, k15, k16, k17, k18)
        {
        }

        const graph_type & data() const
        {
            return super::_data;
        }

        graph_type & data()
        {
            return super::_data;
        };
};

int _main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    simule_matrix<epo_model_wrap<17, 2, 2, 4, 2, 2, 2, 10, 5, 2, 2, 2, 2, 12, 2, 4, 2, 2, 100, 10, -1, 1> >();

    return 0;
}

int main()
{
    std::srand(std::time(0));

    static const std::size_t N_node = 10;
    static const std::size_t stop = 8;
    typedef epo_model_wrap<5, 2, 3, 4, 2, 2, 2, 10, 5, 2, 2, 2, 2, 5, 6, 4, 1, 2, 3, 10, -1, 1> Model;

    double initial_state[Model::node_number] = {1, 0};

    std::size_t n = 0;
    for(std::size_t j = 0 ; j < 1 ; j++)
    {
        cellBOOL<Model> c(initial_state);
        std::size_t i = 0;
        //while(c.model().tf() != true)
        for(std::size_t i = 0 ; i < 50 ; i++)
        {
            //if(i >= stop)
            //    c.model().Epo() = false;
            //else
            //    c.model().Epo() = true;
            if(i < stop)
                c.model().Epo() = true;

            c.internal_update();
            //std::cout << "Epo : " << c.model().Epo()
            //    << ", GATA-1 : " << c.model().GATA_1() << std::endl;
        }
        std::cout << std::endl;
        n += i;
    }

    std::cout << n << std::endl;
    std::cout << static_cast<double>(n) / 1000.0 << std::endl;

    return 0;
}
