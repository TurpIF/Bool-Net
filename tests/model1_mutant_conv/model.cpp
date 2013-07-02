// =================================================================
//                              Libraries
// =================================================================
#include <stdexcept>

// =================================================================
//                            Project Files
// =================================================================
#include "model.h"

// =================================================================
//                    Definition of static attributes
// =================================================================


// =================================================================
//                             Constructors
// =================================================================
model_base::model_base():
    abstract_model()
{
}

// =================================================================
//                            Public Methods
// =================================================================
model_base::ref_node_type model_base::TNF()  { return _data[0]; }
model_base::ref_node_type model_base::FAS()  { return _data[1]; }
model_base::ref_node_type model_base::RIP1() { return _data[2]; }
model_base::ref_node_type model_base::NFkB() { return _data[3]; }
model_base::ref_node_type model_base::C8()   { return _data[4]; }
model_base::ref_node_type model_base::cIAP() { return _data[5]; }
model_base::ref_node_type model_base::ATP()  { return _data[6]; }
model_base::ref_node_type model_base::C3()   { return _data[7]; }
model_base::ref_node_type model_base::ROS()  { return _data[8]; }
model_base::ref_node_type model_base::MOMP() { return _data[9]; }
model_base::ref_node_type model_base::MPT()  { return _data[10]; }

model_base::node_type model_base::TNF() const  { return _data[0]; }
model_base::node_type model_base::FAS() const  { return _data[1]; }
model_base::node_type model_base::RIP1() const { return _data[2]; }
model_base::node_type model_base::NFkB() const { return _data[3]; }
model_base::node_type model_base::C8() const   { return _data[4]; }
model_base::node_type model_base::cIAP() const { return _data[5]; }
model_base::node_type model_base::ATP() const  { return _data[6]; }
model_base::node_type model_base::C3() const   { return _data[7]; }
model_base::node_type model_base::ROS() const  { return _data[8]; }
model_base::node_type model_base::MOMP() const { return _data[9]; }
model_base::node_type model_base::MPT() const  { return _data[10]; }

model_base::node_type model_base::rule(std::size_t rule_number)
{
    if(rule_number == 0)
        return _TNF();
    if(rule_number == 1)
        return _FAS();
    if(rule_number == 2)
        return _RIP1();
    if(rule_number == 3)
        return _NFkB();
    if(rule_number == 4)
        return _C8();
    if(rule_number == 5)
        return _cIAP();
    if(rule_number == 6)
        return _ATP();
    if(rule_number == 7)
        return _C3();
    if(rule_number == 8)
        return _ROS();
    if(rule_number == 9)
        return _MOMP();
    if(rule_number == 10)
        return _MTP();

    throw std::runtime_error("Error : using a wrong rule number.");
}

// =================================================================
//                           Protected Methods
// =================================================================
model_wild_type::node_type model_wild_type::_TNF() const
{
    return TNF();
}

model_wild_type::node_type model_wild_type::_FAS() const
{
    return FAS();
}

model_wild_type::node_type model_wild_type::_RIP1() const
{
    return !C8() && (TNF() || FAS());
}

model_wild_type::node_type model_wild_type::_NFkB() const
{
    return (cIAP() && RIP1()) && !C3();
}

model_wild_type::node_type model_wild_type::_C8() const
{
    return (TNF() || FAS() || C3()) && !NFkB();
}

model_wild_type::node_type model_wild_type::_cIAP() const
{
    return (NFkB() || cIAP()) && !MOMP();
}

model_wild_type::node_type model_wild_type::_ATP() const
{
    return !MPT();
}

model_wild_type::node_type model_wild_type::_C3() const
{
    return ATP() && MOMP() && !NFkB();
}

model_wild_type::node_type model_wild_type::_ROS() const
{
    return !NFkB() && (RIP1() || MPT());
}

model_wild_type::node_type model_wild_type::_MOMP() const
{
    return MPT() || (C8() && !NFkB());
}

model_wild_type::node_type model_wild_type::_MTP() const
{
    return ROS() && !NFkB();
}

model_anti_oxidant::node_type model_anti_oxidant::_ROS() const
{
    return RIP1() || MPT();
}

model_APAF1_deletion::node_type model_APAF1_deletion::_C3() const
{
    return false;
}

model_BAX_deletion::node_type model_BAX_deletion::_MOMP() const
{
    return MPT();
}

model_BCL2_over_expression::node_type model_BCL2_over_expression::_MOMP() const
{
    return MPT();
}

model_BCL2_over_expression::node_type model_BCL2_over_expression::_MPT() const
{
    return false;
}

model_CASP8_deletion::node_type model_CASP8_deletion::_C8() const
{
    return false;
}

model_constitutively_activated_CASP8::node_type model_constitutively_activated_CASP8::_C8() const
{
    return true;
}

model_cFLIP_deletion::node_type model_cFLIP_deletion::_C8() const
{
    return TNF() || FAS() || C3();
}

model_cIAP_deletion::node_type model_cIAP_deletion::_cIAP() const
{
    return false;
}

model_FADD_deletion::node_type model_FADD_deletion::_C8() const
{
    return C3() && !NFkB();
}

model_FADD_deletion::node_type model_FADD_deletion::_RIP1() const
{
    return !C8() && TNF();
}

model_NFkB_deletion::node_type model_NFkB_deletion::_NFkB() const
{
    return false;
}

model_constitutively_activated_NFkB::node_type model_constitutively_activated_NFkB::_NFkB() const
{
    return true;
}

model_RIP1_deletetion::node_type model_RIP1_deletetion::_RIP1() const {
    return false;
}

model_XIAP_deletetion::node_type model_XIAP_deletetion::_C3() const {
    return ATP() && MOMP();
}

model_z_VAD::node_type model_z_VAD::_C3() const {
    return false;
}

model_z_VAD_RIP1_deletion::node_type model_z_VAD_RIP1_deletion::_C3() const {
    return false;
}

model_z_VAD_RIP1_deletion::node_type model_z_VAD_RIP1_deletion::_C8() const {
    return false;
}

model_z_VAD_RIP1_deletion::node_type model_z_VAD_RIP1_deletion::_RIP1() const {
    return false;
}
