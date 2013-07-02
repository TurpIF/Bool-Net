#ifndef __CCELLBOOL_H__
#define __CCELLBOOL_H__


// =================================================================
//                              Libraries
// =================================================================
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


// =================================================================
//                            Project Files
// =================================================================

#include "ccell.h"
#include "params.h"

// =================================================================
//                          Class declarations
// =================================================================



class ccellBOOL : public ccell
{
  public :

    // =================================================================
    //                             Constructors
    // =================================================================
  ccellBOOL( int32_t id, ccelltype type_cell, double x, double y, double z, double int_rad, double ext_rad, double initial_state[] );
  ccellBOOL( int32_t id, ccell * mycell );

    // =================================================================
    //                             Destructors
    // =================================================================
  virtual ~ccellBOOL( void );

    // =================================================================
    //                              Accessors
    // =================================================================
  
    
    // =================================================================
    //                            Public Methods
    // =================================================================
  virtual void internal_update( void );
  virtual void divide_cell(ccellBOOL * mynewcell);

    // =================================================================
    //                           Public Attributes
    // =================================================================

  bool _internal_state[BOOLSYSTEMSIZE];
  double _parameter_values[BOOLNBPARAMS];

 protected :

    // =================================================================
    //                         Forbidden Constructors
    // =================================================================
  ccellBOOL( void )
    {
      printf( "ERROR : Call to forbidden constructor in file %s : l%d\n", __FILE__, __LINE__ );
      exit( EXIT_FAILURE );
    };
  ccellBOOL( const ccellBOOL &model )
    {
      printf( "ERROR : Call to forbidden constructor in file %s : l%d\n", __FILE__, __LINE__ );
      exit( EXIT_FAILURE );
    };


    // =================================================================
    //                           Protected Methods
    // =================================================================
  

    // =================================================================
    //                          Protected Attributes
    // =================================================================

    // =================================================================
    //                           Private Methods
    // =================================================================
    
 private :

    void intracellular_update( void );
    void signals_update( void );

};

#endif // __ccellBOOL_H__
