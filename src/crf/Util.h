/***************************************************************************
/*	CAVE Rendering Framework - a BFH-TI Thesis Project
/*	Computer Perception and Virtual Reality Research Group
/*	www.cpvr.ch
/*
/*	Author: jonas@realboarder.ch
/*  Consult copyright.txt for additional information.
/***************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <osg/Matrix>
#include <vmmlib/matrix4.h>

/**
 * Converts a matrix from the VMML library to a matrix of the OSG library.
 * @ return The osg matrix.
 * @ param matrix The vmml Matrix.
 */
inline osg::Matrix vmmlToOsg( vmml::Matrix4f matrix )
{
    return osg::Matrix( matrix.getElement( 0, 0 ), matrix.getElement( 1, 0 ) , matrix.getElement( 2, 0 ), matrix.getElement( 3, 0 ),
                        matrix.getElement( 0, 1 ), matrix.getElement( 1, 1 ) , matrix.getElement( 2, 1 ), matrix.getElement( 3, 1 ),
                        matrix.getElement( 0, 2 ), matrix.getElement( 1, 2 ) , matrix.getElement( 2, 2 ), matrix.getElement( 3, 2 ),
                        matrix.getElement( 0, 3 ), matrix.getElement( 1, 3 ) , matrix.getElement( 2, 3 ), matrix.getElement( 3, 3 ) );
}


inline vmml::Vector3<float> orthographicVector( const vmml::Vector3<float> &vector )
{
    vmml::Vector3<float> result;
    float x = vector.x;
    float z = vector.z;
    result.x = z;
    result.z = -x;
    result.y = 0;
    return result;
}

/// Normalises the vector
/// @return The normalised vetor.
/// @param vector The vector to normalise.
inline vmml::Vector3<float> norm( const vmml::Vector3<float> &vector )
{
    float length = sqrt( vector.x * vector.x + vector.y * vector.y
		                  + vector.z * vector.z );
    return ( vector / length );
}
#endif
