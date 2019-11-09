#ifndef PARTICLE_H
#define PARTICLE_H
#include "draw.hpp"
#include "utils.hpp"

/** Class to handle rendering of particle data, represents something draw able.
*/
class Particle{

private:
    //Kinematic Data
    sf::Vector2f m_pos; //Position
    sf::Vector2f m_vel; //Velocity
    sf::Vector2f m_acc; //Acceleration
    sf::Vector2f m_p;   //Momentum

    //Radius
    int m_radius;
    float m_mass;
  
  public:  
    //Identification
    unsigned int m_id;

    //Hash Ids
    int bucketids[4];
    int bucketids_Max; 

    //SFML
    sf::Color m_color;
    sf::CircleShape m_shape;
    sf::RenderWindow *m_window;
    int m_winH;
    int m_winW;



    Particle(sf::Vector2f pos, sf::Vector2f vel, int radius, float mass, unsigned int id, sf::RenderWindow *window)
    :m_pos(pos.x, pos.y), m_vel(vel.x, vel.y)
    {

        bucketids_Max = 0;
        m_radius = radius;
        m_id     = id;
        m_window = window;
        m_winW   = 1000;
        m_winW   = 1000;
        m_mass   = mass;
        m_p = m_vel * m_mass;
    }
   
public: 
    


    
    

    //Directives
    void update(double time_delta);
    void draw(bool DRAW_OUTLINE, int PARTICLE_COUNT);
    void applyForce(sf::Vector2f force, double time_delta);
    void drawBoundingBox();

    //Getters
    float getRadius();
    float getMass();
    sf::Vector2f &getPos();
    //Setters
    void addBucket(int bucketid);
};

#endif