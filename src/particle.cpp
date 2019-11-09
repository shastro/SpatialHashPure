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

void Particle::draw(bool DRAW_OUTLINE, int PARTICLE_COUNT)
{

    sf::CircleShape center_disp;

    float v_mag = sqrt(squaredMag(vrMult(m_p,m_mass)));

    // if(colliding){
    //     m_color = sf::Color::Red;
    // }else{
    double hue_val;
    int min = 0;
    int max = 500000;
    if (v_mag < max) {
        hue_val = l_map(v_mag, min, max, 235, 0);

    } else {
        hue_val = 0;
    }
    //hue_val = l_map(m_id, 0, PARTICLE_COUNT, 235, 0);

    m_color = hsv((int)hue_val, 1.0f, 1.0f);
    //}

    // PRINT("DRAWCALL PARTICLE")
    //Particle
    m_shape.setOrigin(m_radius, m_radius);
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    m_shape.setPosition(m_pos);


 
    //bounding_box.setFillColor(sf::Color::White);

    if (m_radius < 10) {
        m_shape.setPointCount(10);
    }

    if (DRAW_OUTLINE) {
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setOutlineThickness(2);
    }
    // LOG("x: ", m_pos.x)
    // LOG("y: ", m_pos.y)
    // LOG("r: ", m_radius)

    m_window->draw(m_shape);
    //colliding = false;

    //Center Display
    // center_disp.setRadius(5);
    // center_disp.setOrigin(5, 5);
    // center_disp.setPosition(m_pos);
    // center_disp.setFillColor(sf::Color::Yellow);
    // m_window->draw(center_disp);


}


//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Particle::update(double time_delta)
{


    int b_zone = 10;

    sf::Vector2f m_acc_cpy = m_acc;
    sf::Vector2f m_vel_cpy = m_vel;

    //Euler Method with momentum principle
    m_vel = vrMult(m_p, 1/m_mass);
    m_pos = m_pos + vrMult(m_vel, time_delta);

    //Speed Clamping at Rest
    if(squaredMag(m_p/m_mass) < 0.00005){
        m_p = vrMult(m_p , 0);
    }

    float c_e = 0.5; //Coefficient of Elasticity (roughly speaking) this only applies to wall collision 


    //Edge Detection
    if (m_pos.x + m_radius > m_winW - b_zone) {
        m_pos.x = m_winW - b_zone - m_radius;
        m_p.x *= -c_e;
    }
    if (m_pos.x - m_radius < b_zone) {
        m_pos.x = m_radius + b_zone;
        m_p.x *= -c_e;
    }

    if (m_pos.y +  m_radius > m_winH - b_zone) {
        m_pos.y = m_winH - b_zone - m_radius;
        m_p.y *= -c_e;
    }

    if (m_pos.y - m_radius < b_zone) {
        m_pos.y = m_radius + b_zone;
        m_p.y *= -c_e;
    }


}

void Particle::applyForce(sf::Vector2f force, double time_delta)
{
    
    m_p = m_p + vrMult(force, time_delta);
    m_vel = vrMult(m_p, 1/m_mass);

}

void Particle::addBucket(int bucketid)
{
 //bucketids.emplace_back(bucketid);
 // if(bucketids_Max < 3){
     bucketids[bucketids_Max] = bucketid;
 // if(bucketids_Max < 3)
     bucketids_Max++;
 // }
}

/////////////
// Getters //
/////////////

float Particle::getRadius()
{
    return m_radius;
}

float Particle::getMass()
{
    return m_mass;
}

sf::Vector2f &Particle::getPos()
{
    return m_pos;
}