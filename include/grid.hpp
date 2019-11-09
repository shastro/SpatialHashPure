// Contains Implementation of a Spatial Hash //
//                                           //
// Classes                                   //                                //
//  -Spatial Hash                            //
//                                           //
///////////////////////////////////////////////

#ifndef GRID_H
#define GRID_H

// #include "engine.hpp"
#include "particle.hpp"
#include <deque>
#include <iterator>
#include <list>


//////////////////
// Spatial Hash //
//////////////////

class SpatialHash
{
private:

    std::vector<std::list<Particle>> *table;

    int m_width;
    int m_height;
    int m_cellsize;
    int nBuckets;

public:
    SpatialHash(int width, int height, int cellsize);
    // ~SpatialHash();

    // Constructs a spatial hash given a vector of particles
    void build(std::vector<Particle>& vecParticles);
    void print();
    //Returns a list of objects that are nearby.
    /*Nearby is defined by all objects in the cell of the query
     as well any cells touched by the query given the radius */
    // std::vector<Particle>* query(Particle &Particle);

    // Returns the id of the Bucket that contains a point
    int pointHash(float x, float y);

    //Inserts a Particle into its appropriate buckets
    void insert(Particle &particle);

    // int getBucketCount();
    // Bucket *getBuckets();

    // void clear();


};




#endif