#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "utils.hpp"
#include "particle.hpp"
#include <vector>

struct p_data_t {

    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float v_mag;

};

#endif