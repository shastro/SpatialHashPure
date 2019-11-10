#ifndef PARTICLE_H
#define PARTICLE_H
#include "draw.hpp"
#include "utils.hpp"

/** Class to handle rendering of particle data, represents something draw able.
*/
class Particle{

public:
    //Kinematic Data
    sf::Vector2f m_pos; //Position
    sf::Vector2f m_vel; //Velocity
    sf::Vector2f m_acc; //Acceleration
    sf::Vector2f m_p;   //Momentum

    //Radius

  
  public:  
    //Identification
    unsigned int m_Id;


    //SFML
    sf::Color m_color;
    sf::CircleShape m_shape;
    sf::RenderWindow *m_window;
    int m_winH;
    int m_winW;

    int m_radius;
    float m_mass;

    bool colliding;



    Particle(sf::Vector2f pos, sf::Vector2f vel, int radius, float mass, unsigned int id, sf::RenderWindow *window)
    :m_pos(pos.x, pos.y), m_vel(vel.x, vel.y)
    {

        colliding = false;
        m_radius = radius;
        m_Id     = id;
        m_window = window;
        m_winW   = 1000;
        m_winH   = 1000;
        m_mass   = mass;
        m_p = m_vel * m_mass;

        m_color = sf::Color::Blue;
    }
   
public: 
    
    //Directives
    void update(double time_delta);
    void draw(bool DRAW_OUTLINE);
    void applyForce(sf::Vector2f force, double time_delta);
    void drawBoundingBox();
    //Getters
    float getRadius() const;
    float getMass()   const;
    sf::Vector2f &getPos();
    float getX() const;
    float getY() const;

};

#endif