#include "grid.hpp"


//////////////////
// Spatial Hash //
//////////////////

SpatialHash::SpatialHash(int width, int height, int cellsize)
    {
        m_width    = width;
        m_height   = height;
        m_cellsize = cellsize;
        m_particleCount = 0;

        //Determine number of buckets needed

        int cols = m_width  / m_cellsize;
        int rows = m_height / m_cellsize;

        nBuckets = (cols + 1) * (rows + 1);

        table = new std::vector<std::list<Particle*>>;
        table->reserve(nBuckets);

        for (int i = 0; i < nBuckets; i++){
            std::list<Particle*> *temp = new std::list<Particle*>;
            (*table).push_back(*temp);
        }

    }

// SpatialHash::~SpatialHash()
// {
//    delete[] buckets;
// }

void SpatialHash::build(const std::vector<Particle*>& vecParticles)
{

    //Place Particles in buckets
    m_particleCount = vecParticles.size();
    for (auto &p : vecParticles) {
        insert(p);
    }

    // for(int i = 0; i < nBuckets; i++)
    // {
    //     std::list<Particle> &temp = (*table)[i];

    //     for(auto &p : temp){
    //         insert(p);
    //     }

}

void SpatialHash::attach_DetectCollision( bool (*collide)(Particle *a, Particle *b))
{
    detectCollision = collide;
}
void SpatialHash::attach_ApplyCollision(void (*resolve)(Particle *a))
{
    applyCollision = resolve;
}

/** Hashes a single point and returns its cellId
*@param x, x coord of point
*@param y, y coord of point
*@return cellId
*/
int SpatialHash::pointHash(float x, float y)
{
    float cellX = floor(x / m_cellsize);
    float cellY = floor(y / m_cellsize);

    //Clamping inside window range
    if(x < 0){
        cellX = 0;
    }
    if(y < 0){
        cellY = 0;
    }

    if(x > m_width){
        x = m_width;
    }

    if(y > m_height){
        y = m_height;
    }

    return (int)cellX + ((int)cellY * (m_width / m_cellsize));
}

/** Hashes a Particle to its relevant cells within grid
*@param Ref to a particle->
*/
void SpatialHash::insert(Particle* particle)
{
    // Upper Left
    float ulX = particle->getX() - particle->getRadius();
    float ulY = particle->getY() - particle->getRadius();

    //Bottom Right
    float brX = particle->getX() + particle->getRadius();
    float brY = particle->getY() + particle->getRadius();

    //Bottom Left
    float blX = ulX;
    float blY = ulY + (particle->getRadius() + particle->getRadius());

    //Upper Right
    float urX = ulX + (particle->getRadius() + particle->getRadius());
    float urY = ulY;

    //ids
    int ulId = pointHash(ulX, ulY);
    int brId = pointHash(brX, brY);
    int blId = pointHash(blX, blY);
    int urId = pointHash(urX, urY);

    // PRINT("ul " << ulId << " br " << brId << " bl " << blId << " ur " << urId)
    if (ulId == brId) {
        (*table)[ulId].push_back(particle);

    } else if ((ulId != brId) && (ulId != blId) && (ulId != urId)) { 
        (*table)[ulId].push_back(particle);
        (*table)[brId].push_back(particle);
        (*table)[urId].push_back(particle);
        (*table)[blId].push_back(particle);
  
        //particle must be in two buckets
    } else {
        (*table)[ulId].push_back(particle);
        (*table)[brId].push_back(particle);
    }
    // PRINT(buckets[50].get()->size())

}


void SpatialHash::collidePairs()
{
    //N loop through buckets
    for(int i = 0; i < nBuckets; i++)
    {
        std::list<Particle*> &temp = (*table)[i];

        if(temp.size() > 1){
            
            //N^2 loop through objects in each bucket
            for(auto p : temp){
                for(auto o : temp){
                    if ((*detectCollision)(p,o)){
                        (*applyCollision)(p);
                        // printf("DETECTED\n");
                    }
                }
            }
        }
    }
}

void SpatialHash::update(double time_delta)
{
    bool checked[m_particleCount] = {false};

    for(int i = 0; i < nBuckets; i++)
    {
        std::list<Particle*> &temp = (*table)[i];

        for(auto p : temp){
            if(!checked[p->m_Id]){
                checked[p->m_Id] = true;  
                p->update(time_delta);
                p->draw(false);
                p->drawBoundingBox();
                
            }
            p->colliding = false;
        }

    } 
}

void SpatialHash::clear()
{
    for(int i = 0; i < nBuckets; i++)
    {
        (*table)[i].clear();
    }
}

void SpatialHash::print()
{
    for (int i = 0; i < nBuckets; i++)
    {
        printf("i: %d \t", i);
        int size = (*table)[i].size();
        printf("s: %d \n", size);
    }
}