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
template<typename T>
class SpatialHash
{
private:

    std::vector<std::list<Particle*>> *table;

    int m_width;
    int m_height;
    int m_cellsize;
    int m_particleCount;
    int nBuckets;

    bool (*detectCollision)(Particle *a, Particle *b);
    
    void (*applyCollision)(Particle *a);

public:
    SpatialHash(int width, int height, int cellsize);
    // ~SpatialHash();

    //Directives High-Level
    void build(const std::vector<Particle*>& vecParticles);
    void clear();
    void update(double time_delta);
    void collidePairs(int &COLLISION_CHECKS);
    void print();

    //Directives Low-Level
    int pointHash(float x, float y);
    void insert(Particle *particle);


    //Setters
    void attach_DetectCollision( bool (*collide)(Particle *a, Particle *b));
    void attach_ApplyCollision(void (*resolve)(Particle *a));


};




#endif