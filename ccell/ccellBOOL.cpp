

// =================================================================
//                              Libraries
// =================================================================
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>


// =================================================================
//                            Project Files
// =================================================================
#include "ccellBOOL.h"
#include "calea.h"


// =================================================================
//                    Definition of static attributes
// =================================================================


// =================================================================
//                             Constructors
// =================================================================

ccellBOOL::ccellBOOL( int32_t id, ccelltype type_cell, double x, double y, double z, double int_rad, double ext_rad, double initial_state[] ) : ccell(id, BOOL, type_cell, x, y, z, int_rad, ext_rad)
{
    for (int16_t i = 0; i < BOOLSYSTEMSIZE; i++) _internal_state[i] = initial_state[i];
    
    // CIRCADIAN CLOCK PARAMETERS
    
    
    // CELL CYCLE PARAMETERS
    // death and survival
    
    // cell cyle parameters
    
    
    signals_update();
} 

ccellBOOL::ccellBOOL( int32_t id, ccell * mycell ) : ccell(id, BOOL, mycell->_cell_type, mycell->_x, mycell->_y, mycell->_z, mycell->_internal_radius, mycell->_external_radius)
{
    for (int16_t i = 0; i < BOOLSYSTEMSIZE; i++) _internal_state[i] = 0;
    
    for (int16_t i = 0; i < BOOLNBPARAMS; i++) _parameter_values[i] = 0;
    
    
    signals_update();
}

// =================================================================
//                             Destructors
// =================================================================

ccellBOOL::~ccellBOOL( void )
{
    // printf("appel destructeur \n");
}


// =================================================================
//                            Public Methods
// =================================================================

// WARNING : interactions MUST have been computed before !
void ccellBOOL::internal_update( void )
{
    // Cell types
    // 0 STEM,
    // 1 CANCER,
    // 2 DIFFERENTIATED_A,
    // 3 DIFFERENTIATED_B,
    // 4 NICHE,
    // 5 SUBSTRATE, not a cell
    
    
    double cycling_threshold = 0.0001; 
    double death_threshold = 1;   
    double dividing_threshold = 0.5;
    double mitotic_threshold = 0.5;
    
    if ( _id == 0 ) printf("cyc_st=%f, volume=%f, cycling=%d, mitotic=%d\n",
                           _internal_state[CYC_ST],_volume,_iscycling,_ismitotic);
    
    // printf(" updating cell %d of type %d\n", _id,_cell_type);
    
    // update the intracellular state of the cell
    intracellular_update();
    signals_update();
    
    // update death status 
    //  printf(" cell id %d has int state %f\n",_id,_internal_state[0]);
    if ( (_cell_type != NICHE) && (_internal_state[DEATH_ST] > death_threshold) ) 
    {
        // printf("cell %d has _internal_state[1] %f\n",_id,_internal_state[1]);
        _hastodie = true;
    }
    
    // update positions due to cell movement 
    if ( !(_hastodie) && (_cell_type != NICHE) ) // don't move niche cells 
    {
        position_update();
    }
    
    
    // update the cycling status
    if ( (_cell_type != NICHE) && _internal_state[CYC_ST] > cycling_threshold )
    {
        // stem cells (cell type 0)  must be in contact with niche cells to cycle but not cancer cells
        if ( ((_cell_type == STEM) && _isincontactwith_nichecells) || (_cell_type == CANCER) ) 
        {
            _iscycling = true; 
        }
    }
    else
        _iscycling = false;
    
    // update the radius (volume) of the cell if cycling and not dying
    if ( _iscycling && !(_hastodie) ) radius_update();
    
    // determine is cell divides
    if ( (_cell_type != NICHE) && _ismitotic && _internal_state[CYC_ST] < dividing_threshold )
  	{
  		_hastodivide=true;
  		if (_id == 0) printf("dividing\n");
  	}	
    
    // update mitotic status
    if ( (_internal_state[CYC_ST] > mitotic_threshold && _iscycling))
    {
		_ismitotic = true; 
    }
    else
    	_ismitotic = false;
    
    
}

void ccellBOOL::divide_cell(ccellBOOL * mynewcell)
{
    double dx, dy, dz;
    double distance;
    double norm_direction;
    
    // printf("old: %d, new %d \n",_id,mynewcell->_id);
    
    // divide intracellular content
    for ( int16_t i = 0; i < BOOLSYSTEMSIZE; i++ )
    {
        // _internal_state are expressed in concentration for the moment (stay constant at division)
        // _internal_state[i] /= 2.0;
        mynewcell->_internal_state[i] = _internal_state[i];
    }
    for ( int16_t i = 0; i < BOOLNBPARAMS; i++ )
    {
        mynewcell->_parameter_values[i] = _parameter_values[i];
    }
    // reset hastodivide
    _hastodivide = false;
    // reset ismitotic
    _ismitotic = false;
    
    // update volume
    _volume /= 2.0;
    mynewcell->_volume = _volume;
    
    // update radii
    double old_external_radius = _external_radius;
    _internal_radius /= CBRT2;
    _external_radius /= CBRT2;
    mynewcell->_internal_radius /= CBRT2;
    mynewcell->_external_radius /= CBRT2;
    
    // update positions : divide along the axis with less mechanical constraints 
    // which are already computed in _interactions[1..3]
    // if the new position is too close to a wall, do not move in that direction
    // If new positions are the same for the two cells, divide in a random direction
    distance = 2.0*old_external_radius - (_external_radius + mynewcell->_external_radius);
    
    if ( distance == 0 ) distance = 0.1*old_external_radius; // in case cell radius is not changing
    
    // cells divide along an axis parallel to the direction of less constraints
    norm_direction = sqrt( _interactions[PX]*_interactions[PX] +	\
                          _interactions[PY]*_interactions[PY] + \
                          _interactions[PZ]*_interactions[PZ] );
    
    double u,v,theta; // to generate random points on a sphere
    // pick a point evenly distributed  on the 3D sphere
    u = calea::random();
    v = -1 + 2.0*(calea::random());
    theta = 6.28318530718*u; 
    
    if ( norm_direction > 0 )
    { 
        // add a bit of noise to the cell division axis: we add a point on a small sphere 
        // to the direction of division
        // convert v-theta to cartesian coords.
        double dx_noise = distance*sqrt(1-v*v)*cos(theta)/2.0/norm_direction;
        double dy_noise = distance*sqrt(1-v*v)*sin(theta)/2.0/norm_direction;
        double dz_noise = distance*v/2.0/norm_direction;
        // calculate the new position relative to the center of the mother cell 
        dx = distance*( _interactions[PX] )/2/norm_direction + 0.1*dx_noise;
        dy = distance*( _interactions[PY] )/2/norm_direction + 0.1*dy_noise;
        dz = distance*( _interactions[PZ] )/2/norm_direction + 0.1*dz_noise;
        // printf("cell_divide : dist %f norm dx %f\n",distance,sqrt(dx*dx+dy*dy+dz*dz));
    }
    else  // random division axis
    {
        // convert v-theta to cartesian coords.
        dx = distance*sqrt(1-v*v)*cos(theta)/2.0;
        dy = distance*sqrt(1-v*v)*sin(theta)/2.0;
        dz = distance*v/2.0;
    }
    
    // code not robust: it is possible for cell to have the same new position 
    if ((_x - dx > _internal_radius) &&					\
        (_x - dx < NBVOXELS*VOXELSIZE - _internal_radius)) _x -= dx;
    if ((_y - dy > _internal_radius) && \
        (_y - dy < NBVOXELS*VOXELSIZE - _internal_radius)) _y -= dy;
    if ((_z - dz > _internal_radius) && \
        (_z - dz < NBVOXELS*VOXELSIZE - _internal_radius)) _z -= dz;
    if ((mynewcell->_x + dx > mynewcell->_internal_radius) && \
        (mynewcell->_x + dx < NBVOXELS*VOXELSIZE - mynewcell->_internal_radius)) mynewcell->_x += dx;
    if ((mynewcell->_y + dy > mynewcell->_internal_radius) && \
        (mynewcell->_y + dy < NBVOXELS*VOXELSIZE - mynewcell->_internal_radius)) mynewcell->_y += dy;
    if ((mynewcell->_z + dz > mynewcell->_internal_radius) && \
        (mynewcell->_z + dz < NBVOXELS*VOXELSIZE - mynewcell->_internal_radius)) mynewcell->_z += dz;
    
    // Watch out! _X _Y _Z have not been updated. 
    // This needs to be updated in csimulation, along with the cgrid _grid
    
}

// =================================================================
//                           Protected Methods
// =================================================================

// =================================================================
//                           Private Methods
// =================================================================

void ccellBOOL::signals_update( void )
{
    // CELL CYCLE SIGNALS
    _signals[CYC_SIG] = _internal_state[CYC_ST]; // cycling signal: -> _interactions 
    // DEATH SIGNALS
    _signals[DEATH_SIG] = 0.0; // not used at the moment at the moment
    // CIRCADIAN CLOCK SIGNALS
    _signals[CLOCK_SIG] = _internal_state[CLOCK_ST]; // circadian signal -> _interactions[5]
    
    // _interactions are defined in csimulation::cellcell_communication
}

void ccellBOOL::intracellular_update( void )
{

}
