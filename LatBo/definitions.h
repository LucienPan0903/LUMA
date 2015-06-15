// Header guard
#ifndef LBM_DEFINITIONS_H
#define LBM_DEFINITIONS_H

// Declarations here
#include <time.h>		// Timing functionality
#include <iostream>		// IO functionality
#include <fstream>		// File functionality
#include <vector>		// Vector template access
#include <iomanip>		// Output precision control
#include <math.h>		// Mathematics
#include <string>		// String template access

#include "ops_generic.h"	// Forward declarations of generic functions

/*	
***************************************************************************************************************
************************************** Global configuration data **********************************************
***************************************************************************************************************
*/
#define PI 3.14159265358979323846

#define acc_g .00001			// Acceleration due to gravity -- where does this come from and is it general?

// Output Options
//#define TEXTOUT
//#define ENSIGHTGOLD
#define VTK_WRITER

// Gravity (acts in -y direction)
//#define GRAVITY_ON

/*	
***************************************************************************************************************
********************************************** Time data ******************************************************
***************************************************************************************************************
*/
#define T 50		// End time of simulation (seconds)

/*	
***************************************************************************************************************
******************************************* Domain dimensions *************************************************
***************************************************************************************************************
*/
#define dims 2		// Number of dimensions to the problem
#define N 250		// Number of x lattice sites
#define M 50		// Number of y lattice sites
#define K 50		// Number of z lattice sites
#define a_x 0		// Start of domain-x
#define b_x 10		// End of domain-x
#define a_y 0		// Start of domain-y
#define b_y 2		// End of domain-y
#define a_z 0		// Start of domain-z
#define b_z 2		// End of domain-z

/*	
***************************************************************************************************************
******************************************* Immersed Boundary *************************************************
***************************************************************************************************************
*/

//#define IBM_ON		// Turn on IBM
//#define IBM_DEBUG	// Write IBM body data out to text files

#define Lspace 25	// Number of Lagrange points (approximately)

#define ibb_x 1.5		// x Position of body centre
#define ibb_y 1.0		// y Position of body centre
#define ibb_z 1.0		// z Position of body centre
#define ibb_w .5		// width (x) of IB body
#define ibb_l .25		// length (y) of IB body
#define ibb_d .25		// depth (z) of IB body
#define ibb_r .5		// radius of IB body

#define INSERT_CIRCLE_SPHERE
//#define INSERT_RECTANGLE_CUBOID

/*	
***************************************************************************************************************
********************************************** Wall data ******************************************************
***************************************************************************************************************
*/

//#define SOLID_ON		// Turn on solid object (bounce-back)
//#define WALLS_ON		// Turn on top, bottom, front, and back no-slip walls
#define INLET_ON		// Turn on inlet boundary (assumed left-hand wall for now)
#define OUTLET_ON		// Turn on outlet boundary (assumed right-hand wall for now)

#ifdef SOLID_ON				// Labelling routine only allows for squares at the minute
#define obj_x_min 40		// Index of start of object/wall in x-direction
#define obj_x_max 50		// Index of end of object/wall in x-direction
#define obj_y_min 20		// Index of start of object/wall in y-direction
#define obj_y_max 30		// Index of end of object/wall in y-direction
#define obj_z_min 20		// Index of start of object/wall in z-direction
#define obj_z_max 30		// Index of end of object/wall in z-direction
#endif


/*	
***************************************************************************************************************
*********************************************** Fluid data ****************************************************
***************************************************************************************************************
*/

// Lattice units
#define u_0x 0.1	// Initial x-velocity
#define u_0y 0		// Initial y-velocity
#define u_0z 0		// Initial z-velocity
#define rho_in 1	// Initial density
#define nu .02		// Kinematic viscosity (constant across all grid levels)


/*	
***************************************************************************************************************
******************************************** Multi-grid data **************************************************
***************************************************************************************************************
*/
#define NumLev 0		// Levels of refinement (can't use with IBM yet)
#define NumReg 1		// Number of refined regions (can be arbitrary if NumLev = 0)

#if NumLev != 0
// Lattice indices for refined region on level L0 start numbering at 0

	#if NumReg == 2 // Inlcuded for testing purposes so I don't have to keep re-commenting bits
	static size_t RefXstart[NumReg]		= {44, 66};
	static size_t RefXend[NumReg]		= {56, 78};
	static size_t RefYstart[NumReg]		= {24, 24};
	static size_t RefYend[NumReg]		= {36, 36};
	// If doing 2D, these can be arbitrary values
	static size_t RefZstart[NumReg]		= {24, 24};
	static size_t RefZend[NumReg]		= {36, 36};

	#elif NumReg == 1
	static size_t RefXstart[NumReg]		= {64};
	static size_t RefXend[NumReg]		= {72};
	static size_t RefYstart[NumReg]		= {24};
	static size_t RefYend[NumReg]		= {36};
	static size_t RefZstart[NumReg]		= {24};
	static size_t RefZend[NumReg]		= {36};
	#endif

#endif

/*	
***************************************************************************************************************
************************************** Clean-up -- no need to edit ********************************************
***************************************************************************************************************
*/

// Set default options if using 2D
#if dims == 3
	#define nVels 19	// Use D3Q19
#else
	#define nVels 9		// Use D2Q9
	
	// Set Z limits for 2D
	#undef a_z
	#define a_z 0

	#undef b_z
	#define b_z 2

	#undef K
	#define K 1

	// Set object limits for 2D
	#undef obj_z_min
	#define obj_z_min 0

	#undef obj_z_max
	#define obj_z_max 0

	#undef ibb_d
	#define ibb_d 0

#endif

#if NumLev == 0
// Set region info to default as no refinement
#undef NumReg
#define NumReg 1
static size_t RefXstart[NumReg]		= {0};
static size_t RefXend[NumReg]		= {0};
static size_t RefYstart[NumReg]		= {0};
static size_t RefYend[NumReg]		= {0};
static size_t RefZstart[NumReg]		= {0};
static size_t RefZend[NumReg]		= {0};
#endif


#endif