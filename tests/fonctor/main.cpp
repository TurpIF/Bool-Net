#include "network.h"
#include "fonctor_bool.h"
#include "fonctor_coef.h"
#include "fonctor_generic.h"

#include <bitset>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

template <coef_type Ag, coef_type Ar, std::size_t Td>
void test()
{
    std::srand(std::time(0));

    static const coef_type ag = Ag;
    static const coef_type ar = Ar;
    static const coef_type de = -1;
    static const std::size_t td = Td;

    using namespace fonctor_coef;

    static const std::size_t n_Cell_Size = 0;
    static const std::size_t n_Cln3 = 1;
    static const std::size_t n_SBF = 2;
    static const std::size_t n_Cln1_2 = 3;
    static const std::size_t n_Cdh1 = 4;
    static const std::size_t n_Cdc20_Cdc14 = 5;
    static const std::size_t n_Swi5 = 6;
    static const std::size_t n_Mcm1_SFF = 7;
    static const std::size_t n_Clb5_6 = 8;
    static const std::size_t n_MBF = 9;
    static const std::size_t n_Sic1 = 10;
    static const std::size_t n_Clb1_2 = 11;

    typedef fonctor_traits<coef_type, 12> traits;

    auto f_Cell_Size = make_to_bool(make_set_value<traits>(0)); // Cell_Size
    auto f_Cln3 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Cell_Size),
            make_degradation<traits>(de, td))); // Cln3
    auto f_SBF = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Cln3),
            make_set_value_if_node<traits>(ar, n_Clb1_2))); // SBF
    auto f_Cln1_2 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_SBF),
            make_degradation<traits>(de, td))); // Cln1_2
    auto f_Cdh1 = make_to_bool(make_sum(make_set_value_if_node<traits>(ar, n_Cln1_2),
            make_set_value_if_node<traits>(ar, n_Clb5_6),
            make_set_value_if_node<traits>(ar, n_Clb1_2),
            make_set_value_if_node<traits>(ag, n_Cdc20_Cdc14))); // Cdh1
    auto f_Cdc20_Cdc14 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Mcm1_SFF),
            make_set_value_if_node<traits>(ag, n_Clb1_2),
            make_degradation<traits>(de, td))); // Cdc20_Cdc14
    auto f_Swi5 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Cdc20_Cdc14),
            make_set_value_if_node<traits>(ag, n_Mcm1_SFF),
            make_set_value_if_node<traits>(ar, n_Clb1_2),
            make_degradation<traits>(de, td))); // Swi5
    auto f_Mcm1_SFF = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Clb5_6),
            make_set_value_if_node<traits>(ag, n_Clb1_2),
            make_degradation<traits>(de, td))); // Mcm1_SFF
    auto f_Clb5_6 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_MBF),
            make_set_value_if_node<traits>(ar, n_Sic1),
            make_set_value_if_node<traits>(ar, n_Cdc20_Cdc14))); // Clb5_6
    auto f_MBF = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Cln3),
            make_set_value_if_node<traits>(ar, n_Clb1_2))); // MBF
    auto f_Sic1 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Cdc20_Cdc14),
            make_set_value_if_node<traits>(ag, n_Swi5),
            make_set_value_if_node<traits>(ar, n_Cln1_2),
            make_set_value_if_node<traits>(ar, n_Clb5_6),
            make_set_value_if_node<traits>(ar, n_Clb1_2))); // Sic1
    auto f_Clb1_2 = make_to_bool(make_sum(make_set_value_if_node<traits>(ag, n_Clb5_6),
            make_set_value_if_node<traits>(ag, n_Mcm1_SFF),
            make_set_value_if_node<traits>(ar, n_Cdc20_Cdc14),
            make_set_value_if_node<traits>(ar, n_Cdh1),
            make_set_value_if_node<traits>(ar, n_Sic1))); // Clb1_2

    typedef std::map<unsigned long int, std::size_t> visited_type;
    visited_type visited;

    std::bitset<12> state;
    static const std::size_t N = 1000;
    for(std::size_t n = N - 1 ; n < N ; n++)
    {
        state[n_Cln3]        = static_cast<bool>(n & (1 << 0));
        state[n_MBF]         = static_cast<bool>(n & (1 << 1));
        state[n_SBF]         = static_cast<bool>(n & (1 << 2));
        state[n_Cln1_2]      = static_cast<bool>(n & (1 << 3));
        state[n_Cdh1]        = static_cast<bool>(n & (1 << 4));
        state[n_Swi5]        = static_cast<bool>(n & (1 << 5));
        state[n_Cdc20_Cdc14] = static_cast<bool>(n & (1 << 6));
        state[n_Clb5_6]      = static_cast<bool>(n & (1 << 7));
        state[n_Sic1]        = static_cast<bool>(n & (1 << 8));
        state[n_Clb1_2]      = static_cast<bool>(n & (1 << 9));
        state[n_Mcm1_SFF]    = static_cast<bool>(n & (1 << 10));
        state[n_Cell_Size]   = static_cast<bool>(n & (1 << 11));

        std::cout << state[n_Cln3]
            << state[n_MBF]
            << state[n_SBF]
            << state[n_Cln1_2]
            << state[n_Cdh1]
            << state[n_Swi5]
            << state[n_Cdc20_Cdc14]
            << state[n_Clb5_6]
            << state[n_Sic1]
            << state[n_Clb1_2]
            << state[n_Mcm1_SFF]
            << state[n_Cell_Size]
            << std::endl;

        std::size_t time_static = 0;

        for(unsigned int i = 0 ; i < 200 ; i++)
        {
            network_traits<bool, 12>::update_type u_0  = f_Cell_Size(state);
            network_traits<bool, 12>::update_type u_1  = f_Cln3(state);
            network_traits<bool, 12>::update_type u_2  = f_SBF(state);
            network_traits<bool, 12>::update_type u_3  = f_Cln1_2(state);
            network_traits<bool, 12>::update_type u_4  = f_Cdh1(state);
            network_traits<bool, 12>::update_type u_5  = f_Cdc20_Cdc14(state);
            network_traits<bool, 12>::update_type u_6  = f_Swi5(state);
            network_traits<bool, 12>::update_type u_7  = f_Mcm1_SFF(state);
            network_traits<bool, 12>::update_type u_8  = f_Clb5_6(state);
            network_traits<bool, 12>::update_type u_9  = f_MBF(state);
            network_traits<bool, 12>::update_type u_10 = f_Sic1(state);
            network_traits<bool, 12>::update_type u_11 = f_Clb1_2(state);

            std::bitset<12> copy(state);

            if(u_0 == network_traits<bool, 12>::Active)  state[n_Cell_Size]   = true;
            if(u_1 == network_traits<bool, 12>::Active)  state[n_Cln3]        = true;
            if(u_2 == network_traits<bool, 12>::Active)  state[n_SBF]         = true;
            if(u_3 == network_traits<bool, 12>::Active)  state[n_Cln1_2]      = true;
            if(u_4 == network_traits<bool, 12>::Active)  state[n_Cdh1]        = true;
            if(u_5 == network_traits<bool, 12>::Active)  state[n_Cdc20_Cdc14] = true;
            if(u_6 == network_traits<bool, 12>::Active)  state[n_Swi5]        = true;
            if(u_7 == network_traits<bool, 12>::Active)  state[n_Mcm1_SFF]    = true;
            if(u_8 == network_traits<bool, 12>::Active)  state[n_Clb5_6]      = true;
            if(u_9 == network_traits<bool, 12>::Active)  state[n_MBF]         = true;
            if(u_10 == network_traits<bool, 12>::Active) state[n_Sic1]        = true;
            if(u_11 == network_traits<bool, 12>::Active) state[n_Clb1_2]      = true;

            if(u_0 == network_traits<bool, 12>::Desactive)  state[n_Cell_Size]   = false;
            if(u_1 == network_traits<bool, 12>::Desactive)  state[n_Cln3]        = false;
            if(u_2 == network_traits<bool, 12>::Desactive)  state[n_SBF]         = false;
            if(u_3 == network_traits<bool, 12>::Desactive)  state[n_Cln1_2]      = false;
            if(u_4 == network_traits<bool, 12>::Desactive)  state[n_Cdh1]        = false;
            if(u_5 == network_traits<bool, 12>::Desactive)  state[n_Cdc20_Cdc14] = false;
            if(u_6 == network_traits<bool, 12>::Desactive)  state[n_Swi5]        = false;
            if(u_7 == network_traits<bool, 12>::Desactive)  state[n_Mcm1_SFF]    = false;
            if(u_8 == network_traits<bool, 12>::Desactive)  state[n_Clb5_6]      = false;
            if(u_9 == network_traits<bool, 12>::Desactive)  state[n_MBF]         = false;
            if(u_10 == network_traits<bool, 12>::Desactive) state[n_Sic1]        = false;
            if(u_11 == network_traits<bool, 12>::Desactive) state[n_Clb1_2]      = false;

            std::cout << state[n_Cln3]
                << state[n_MBF]
                << state[n_SBF]
                << state[n_Cln1_2]
                << state[n_Cdh1]
                << state[n_Swi5]
                << state[n_Cdc20_Cdc14]
                << state[n_Clb5_6]
                << state[n_Sic1]
                << state[n_Clb1_2]
                << state[n_Mcm1_SFF]
                //<< state[n_Cell_Size]
                << " : " << state.to_string()
                << std::endl;

            if(state.to_ulong() == copy.to_ulong())
                time_static++;
            else
                time_static = 0;

            if(time_static > td)
                break;
        }

        bool find = false;
        for(typename visited_type::iterator it = visited.begin() ;
                it != visited.end() ; it++)
        {
            if(it->first == state.to_ulong())
            {
                find = true;
                it->second++;
                break;
            }
        }
        if(!find)
        {
            visited.insert(std::pair<unsigned long int, std::size_t>(state.to_ulong(), 1));
        }
    }

    for(typename visited_type::const_iterator it = visited.begin() ;
            it != visited.end() ; it++)
    {
        unsigned long int n = it->first;
        std::cout << std::setw(10) << it->second << " "
            << static_cast<bool>(n & (1 << n_Cln3))
            << static_cast<bool>(n & (1 << n_MBF))
            << static_cast<bool>(n & (1 << n_SBF))
            << static_cast<bool>(n & (1 << n_Cln1_2))
            << static_cast<bool>(n & (1 << n_Cdh1))
            << static_cast<bool>(n & (1 << n_Swi5))
            << static_cast<bool>(n & (1 << n_Cdc20_Cdc14))
            << static_cast<bool>(n & (1 << n_Clb5_6))
            << static_cast<bool>(n & (1 << n_Sic1))
            << static_cast<bool>(n & (1 << n_Clb1_2))
            << static_cast<bool>(n & (1 << n_Mcm1_SFF))
            << std::endl;
    }
}

int main()
{
    test<1, -10, 4>();
    std::cout << std::endl;
    //test<2, -2, 1>();
    //std::cout << std::endl;
    //test<150, -150, 1>();
    //std::cout << std::endl;
    //test<150, -150, 10>();
    //std::cout << std::endl;
    //test<1000, -10000, 1>();
    //std::cout << std::endl;
    //test<1000, -10000, 42>();
    //std::cout << std::endl;
    //test<2, -1, 1>();
    //std::cout << std::endl;
    //test<10000, -1, 1>();

    return 0;
}
