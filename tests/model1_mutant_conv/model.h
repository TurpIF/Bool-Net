#ifndef __MODEL_H__
#define __MODEL_H__

// =================================================================
//                              Libraries
// =================================================================

// =================================================================
//                            Project Files
// =================================================================
#include "abstract_model.h"

// =================================================================
//                          Class declarations
// =================================================================
class model_base : public abstract_model<11, 100, 0, false>
{
    public:
        // =================================================================
        //                             Constructors
        // =================================================================
        model_base();

        // =================================================================
        //                            Public Methods
        // =================================================================
        ref_node_type TNF();
        ref_node_type FAS();
        ref_node_type RIP1();
        ref_node_type NFkB();
        ref_node_type C8();
        ref_node_type cIAP();
        ref_node_type ATP();
        ref_node_type C3();
        ref_node_type ROS();
        ref_node_type MOMP();
        ref_node_type MPT();

        node_type TNF() const;
        node_type FAS() const;
        node_type RIP1() const;
        node_type NFkB() const;
        node_type C8() const;
        node_type cIAP() const;
        node_type ATP() const;
        node_type C3() const;
        node_type ROS() const;
        node_type MOMP() const;
        node_type MPT() const;

        virtual node_type rule(std::size_t rule_number);

        // =================================================================
        //                           Public Attributes
        // =================================================================

    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _TNF() const = 0;
        virtual node_type _FAS() const = 0;
        virtual node_type _RIP1() const = 0;
        virtual node_type _NFkB() const = 0;
        virtual node_type _C8() const = 0;
        virtual node_type _cIAP() const = 0;
        virtual node_type _ATP() const = 0;
        virtual node_type _C3() const = 0;
        virtual node_type _ROS() const = 0;
        virtual node_type _MOMP() const = 0;
        virtual node_type _MTP() const = 0;
};

struct model_wild_type : public model_base
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _TNF() const;
        virtual node_type _FAS() const;
        virtual node_type _RIP1() const;
        virtual node_type _NFkB() const;
        virtual node_type _C8() const;
        virtual node_type _cIAP() const;
        virtual node_type _ATP() const;
        virtual node_type _C3() const;
        virtual node_type _ROS() const;
        virtual node_type _MOMP() const;
        virtual node_type _MTP() const;
};

struct model_anti_oxidant : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _ROS() const;
};

struct model_APAF1_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C3() const;
};

struct model_BAX_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _MOMP() const;
};

struct model_BCL2_over_expression : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _MOMP() const;
        virtual node_type _MPT() const;
};

struct model_CASP8_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C8() const;
};

struct model_constitutively_activated_CASP8 : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C8() const;
};

struct model_cFLIP_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C8() const;
};

struct model_cIAP_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _cIAP() const;
};

struct model_FADD_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C8() const;
        virtual node_type _RIP1() const;
};

struct model_NFkB_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _NFkB() const;
};

struct model_constitutively_activated_NFkB : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _NFkB() const;
};

struct model_RIP1_deletetion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _RIP1() const;
};

struct model_XIAP_deletetion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C3() const;
};

struct model_z_VAD : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C3() const;
};

struct model_z_VAD_RIP1_deletion : public model_wild_type
{
    protected:
        // =================================================================
        //                           Protected Methods
        // =================================================================
        virtual node_type _C3() const;
        virtual node_type _C8() const;
        virtual node_type _RIP1() const;
};

#endif
