#include "particle.hpp"

void Particle::drawBoundingBox()
{
    sf::RectangleShape bounding_box;

    bounding_box.setPosition(m_pos.x - m_radius, m_pos.y - m_radius);
    bounding_box.setSize(sf::Vector2f(2 * m_radius, 2 * m_radius));
    bounding_box.setOutlineColor(sf::Color::Black);
    bounding_box.setFillColor(sf::Color(255,255,255,0));
    bounding_box.setOutlineThickness(2);


    int point_radius = 5;

    sf::CircleShape ul;
    sf::CircleShape bl;
    sf::CircleShape ur;
    sf::CircleShape br;

    ul.setRadius(point_radius);
    bl.setRadius(point_radius);
    ur.setRadius(point_radius);
    br.setRadius(point_radius);

    ul.setOrigin(point_radius, point_radius);
    bl.setOrigin(point_radius, point_radius);
    ur.setOrigin(point_radius, point_radius);
    br.setOrigin(point_radius, point_radius);

    ul.setPosition(m_pos.x - m_radius, m_pos.y - m_radius);
    bl.setPosition(m_pos.x - m_radius, m_pos.y + m_radius);
    ur.setPosition(m_pos.x + m_radius, m_pos.y - m_radius);
    br.setPosition(m_pos.x + m_radius, m_pos.y + m_radius);

    ur.setFillColor(sf::Color::Red);
    bl.setFillColor(sf::Color::Red);
    ul.setFillColor(sf::Color::Green);
    br.setFillColor(sf::Color::Green);

    m_window->draw(bounding_box);
    m_window->draw(ul);
    m_window->draw(bl);
    m_window->draw(ur);
    m_window->draw(br);
}

void Particle::draw(bool DRAW_OUTLINE)
{

    //Particle

    if(colliding){
        m_color = sf::Color::Red;
    }else{
        m_color = sf::Color::Blue;
    }

    m_shape.setOrigin(m_radius, m_radius);
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    m_shape.setPosition(m_pos);



    if (m_radius < 10) {
        m_shape.setPointCount(10);
    }

    if (DRAW_OUTLINE) {
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setOutlineThickness(2);
    }


    m_window->draw(m_shape);
    //colliding = false;

    //Center Display
    // sf::CircleShape center_disp;
    // center_disp.setRadius(5);
    // center_disp.setOrigin(5, 5);
    // center_disp.setPosition(m_pos);
    // center_disp.setFillColor(sf::Color::Yellow);
    // m_window->draw(center_disp);


}


//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Particle::update(double time_delta)
{

    //Euler Method with momentum principle
    m_vel = vrMult(m_p, 1.0f/(float)m_mass);
    m_pos = m_pos + vrMult(m_vel, time_delta);

    //Speed Clamping at Rest
    if(squaredMag(vrMult(m_p, 1.0f/(float)m_mass)) < 0.00005){
        m_p = vrMult(m_p , 0);
    }

    float c_e = 1; //Coefficient of Elasticity (roughly speaking) this only applies to wall collision 


    //Edge Detection
    if (m_pos.x + m_radius > m_winW) {
        m_pos.x = m_winW - m_radius;
        m_p.x *= -c_e;
    }
    if (m_pos.x - m_radius < 0) {
        m_pos.x = m_radius;
        m_p.x *= -c_e;
    }

    if (m_pos.y +  m_radius > m_winH) {
        m_pos.y = m_winH- m_radius;
        m_p.y *= -c_e;
    }

    if (m_pos.y - m_radius < 0) {
        m_pos.y = m_radius;
        m_p.y *= -c_e;
    }


}

void Particle::applyForce(sf::Vector2f force, double time_delta)
{
    
    m_p = m_p + vrMult(force, time_delta);

}



/////////////
// Getters //
/////////////

float Particle::getRadius() const
{
    return m_radius;
}

float Particle::getMass() const
{
    return m_mass;
}

sf::Vector2f &Particle::getPos()
{
    return m_pos;
}

float Particle::getX() const
{
    return m_pos.x;
}

float Particle::getY() const
{
    return m_pos.y;
}