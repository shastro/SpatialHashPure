#include "draw.hpp"
#include "grid.hpp"
#include "particle.hpp"
#include "utils.hpp"
#include <ctime>
#include "unistd.h"
// /*
//     Granular Simulation
//     Author:Skyler Hughes
//     Liscense: MIT


// */

sf::Event event;

bool PAUSED;


void drawGrid(sf::Color linecolor, int cellsize, int width, int height, sf::RenderWindow *window) {

    //Vertical
    for (int i = 0; i < (width / cellsize) + 1; i++) {
        int x1 = i * cellsize;
        int y2 = height;

        sf::Vertex line[2]; //= new sf::Vertex[2];

        line[0] = sf::Vertex (sf::Vector2f(x1, 0),  linecolor);
        line[1] = sf::Vertex (sf::Vector2f(x1, y2), linecolor);

        //vlines[i] = line;
        window->draw(line, 2, sf::Lines);
        //free(line);
    }

    //Horizontal
    for (int i = 0; i < (height / cellsize) + 1; i++) {
        int y1 = i * cellsize;
        int x2 = width;

        sf::Vertex line[2];
        // sf::Vertex line2[2];

        // line[0] = sf::Vertex (sf::Vector2f(0, y1),  linecolor);
        // line[1] = sf::Vertex (sf::Vector2f(1000, y1), linecolor);

        line[0] = sf::Vertex (sf::Vector2f(1, y1),  linecolor);
        line[1] = sf::Vertex (sf::Vector2f(1000, y1), linecolor);
        // line2[0] = sf::Vertex (sf::Vector2f(0, y1),      linecolor);
        // line2[1] = sf::Vertex (sf::Vector2f(width, y1),  linecolor);

        window->draw(line, 2, sf::Lines);
        //free(line);
        // hlines[i] = line;
    }

}

bool detectCollision(Particle *a, Particle *b)
{
    sf::Vector2f dist = a->m_pos - b->m_pos;
    float aR = a->m_radius;
    float bR = b->m_radius;

    if (squaredMag(dist) < ((aR + bR) * (aR + bR))) {
        return true;
    } else {
        return false;
    }
}

void applyCollision(Particle *a)
{

    a->colliding = true;
    

}

int main(int argc, char**argv) {

    // CONFIG PARSING //
    int PARTICLE_COUNT = 5000;
    
    int FRAMERATE = 60;
    int WIDTH = 1000;
    int HEIGHT = 1000;
    bool DRAW_BOUNDING_BOX = false;
    bool DRAW_OUTLINE = false;
    int radius = 5;
    int CELLSIZE = 4 *radius;
    float mass = radius * radius * 3.14159 * 0.25;
    double time_delta = 2;


    // WINDOW SETUP //
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
                            std::string("Rendering Sim: ").c_str(), sf::Style::Default, settings);


    PRINT("INITIALIZING PARTICLES")

    // Particle Initialization with first frame's data
    std::vector<Particle*> particles;

    srand(time(NULL));
    for (int j = 0; j < PARTICLE_COUNT; j++) {


        sf::Vector2f pos(random(0, WIDTH), random(0, HEIGHT));
        sf::Vector2f vel(random(-2,2), random(-2,2));
        sf::Vector2f acc(0, 0);

        Particle *p = new Particle(pos, vel, radius, mass, j, &window);
        particles.push_back(p);
    }

    // Grid Lines //

    bool DRAW_GRID = true;

    /////////////

    PRINT("BEGINING MAIN LOOP")
    // MAIN FRAMELOOP //

    
    
    SpatialHash *hashtable = new SpatialHash(1000,1000,CELLSIZE);
    hashtable->attach_DetectCollision(detectCollision);
    hashtable->attach_ApplyCollision(applyCollision);

    while (1)
    {



        clock_t start, end;
        start = clock();
        window.clear(sf::Color(0, 0, 0));

        //////////////////////////
        // DRAW BACKGROUND GRID //
        //////////////////////////

        //Color light blue 189, 209, 242
        // drawGrid(sf::Color(189, 209, 242), 25, WIDTH, HEIGHT, &window);

        /////////////////////////
        // HASHING AND PHYSICS //
        /////////////////////////

        hashtable->build(particles);
        hashtable->collidePairs(); //Performs all collision pair checking and physics
        hashtable->update(time_delta);
        hashtable->clear();


        //////////////
        // Non Hash //
        //////////////
        // for(auto p : particles){
        //     for(auto o : particles){
        //         if(p->m_Id != o->m_Id){
        //             if ((*detectCollision)(p,o)){
        //                 (*applyCollision)(p);
        //                 // printf("DETECTED\n");
        //             }
        //         }
        //     }
        // }

        // for(auto p : particles){
        //     p->update(time_delta);
        //     p->draw(false);
        //     p->colliding = false;
        // }

        ///////////////////////
        // DRAWING HASH GRID //
        ///////////////////////

        if (DRAW_GRID) {
            drawGrid(sf::Color(50,50,50), CELLSIZE, WIDTH, HEIGHT, &window);
        }

        // DISPLAY //
        window.display();
        end = clock();

        //////////////////////////
        // FRAMERATE MANAGEMENT //
        //////////////////////////
        double time = ((double)(end - start) / (double)CLOCKS_PER_SEC) * 1000000;
        double refresh_rate = ((double)1     / (double)FRAMERATE)      * 1000000;
        double remainder;
        if (refresh_rate - time > 0) {

            remainder = refresh_rate - time; // In micro-seconds
        } else {
            remainder = 0;
        }
        usleep(remainder);

        //LOG("FRAME: ", i)
        // LOG("FPS: ", time / 100)


        // EVENT POLLING //
        sf::Event event;
        window.pollEvent(event);

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                PRINT("PAUSED")
                while (1) {
                    sf::Event event;
                    window.pollEvent(event);
                    if (event.type == sf::Event::KeyPressed) {
                        break;
                    }

                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }
                }

            }

            // if (event.key.code == sf::Keyboard::R) {
            //     i = 0;
            // }
            // if(event.key.code == sf::Keyboard::Right) {
            //     i += 1;
            // }
        }

        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }
    }

    PRINT("FINISHED")
    sf::Event newevent;
    while (1) {



        window.pollEvent(newevent);

        if (newevent.type == sf::Event::Closed) {
            // free(vlines);
            window.close();
            return 0;
        }


    }

    for (auto & particle : particles) {
        free((void *)&particle);
    }


    return 0;

}