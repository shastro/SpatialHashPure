#include "grid.hpp"


//////////////////
// Spatial Hash //
//////////////////

SpatialHash::SpatialHash(int width, int height, int cellsize)
    {
        m_width    = width;
        m_height   = height;
        m_cellsize = cellsize;

        //Determine number of buckets needed

        int cols = m_width  / m_cellsize;
        int rows = m_height / m_cellsize;

        nBuckets = (cols + 1) * (rows + 1);

        table = new std::vector<std::list<Particle>>;
        // table = new  std::vector<std::list<Particle>> table(nBuckets, std::list<Particle>(1));


        table->reserve(nBuckets);
        for (int i = 0; i < nBuckets; i++){
            std::list<Particle> *temp = new std::list<Particle>;
            (*table).push_back(*temp);
        }

        // std::fill(table->begin(), table->end(), std::list<Particle>(1));
        // std::vector<std::list<Particle>> table(nBuckets, std::list<Particle>(1));

    }
    
void SpatialHash::build(std::vector<Particle>& vecParticles)
{

    //Place Particles in buckets
    for (auto & Particle : vecParticles) {
        insert(Particle);
    }

}

// std::vector<Particle>* SpatialHash::query(Particle &Particle)
// {
//     std::vector<Particle> *Particlequeue = new std::vector<Particle>;

//     std::vector<Particle> *b_Particles;

//     //Add relevant buckets to Particle buckets
//     for (int i = 0 ; i < Particle.bucketids_Max; i++) {
//         int id = Particle.bucketids[i];
            
//         // LOG( "max ",Particle.bucketids_Max)
//         // LOG("id ", id)
//         bucket = buckets[id];
//         b_Particles = bucket.get();

//         //(*Particlequeue) += (*b_Particles);
//        // Particlequeue->reserve(Particlequeue->size() + b_Particles->size());
//         Particlequeue->insert(std::end(*Particlequeue), std::begin(*b_Particles), std::end(*b_Particles));
//             // (echo ../bin/ParticleRenderer sp1.json ; echo ../bin/ParticleRenderer sp2.json) | parallel 
//     }

//     std::vector<Particle>().swap(*b_Particles);
//    // PRINT("bb " << b_Particles->size())
//    // PRINT("bq " << Particlequeue->size())
//    b_Particles->clear();
//     return Particlequeue;
// }

void SpatialHash::insert(Particle& particle)
{
    // Upper Left
    float ulX = particle.getPos().x - particle.getRadius();
    float ulY = particle.getPos().y - particle.getRadius();

    //Bottom Right
    float brX = particle.getPos().x + particle.getRadius();
    float brY = particle.getPos().y + particle.getRadius();

    //Bottom Left
    float blX = ulX;
    float blY = ulY + (particle.getRadius() + particle.getRadius());

    //Upper Right
    float urX = ulX + (particle.getRadius() + particle.getRadius());
    float urY = ulY;

    //ids
    int ulId = pointHash(ulX, ulY);
    int brId = pointHash(brX, brY);
    int blId = pointHash(blX, blY);
    int urId = pointHash(urX, urY);

    // PRINT("ul " << ulId << " br " << brId << " bl " << blId << " ur " << urId)
    if (ulId == brId) {
        particle.addBucket(ulId);
        (*table)[ulId].push_back(particle);

    } else if ((ulId != brId) && (ulId != blId) && (ulId != urId)) {
        particle.addBucket(ulId); //Upp Left
        particle.addBucket(brId); //Bot Right
        particle.addBucket(urId); //Upp Right
        particle.addBucket(blId); //Bot Left
        
        (*table)[ulId].push_back(particle);
        (*table)[brId].push_back(particle);
        (*table)[urId].push_back(particle);
        (*table)[blId].push_back(particle);
  
        //particle must be in two buckets
    } else {
        particle.addBucket(ulId);
        particle.addBucket(brId);

        (*table)[ulId].push_back(particle);
        (*table)[brId].push_back(particle);
    }
    // PRINT(buckets[50].get()->size())

}

int SpatialHash::pointHash(float x, float y)
{
    float cellX = floor(x / m_cellsize);
    float cellY = floor(y / m_cellsize);

    if(x < 0){
        cellX = 0;
    }
    if(y < 0){
        cellY = 0;
    }
    return (int)cellX + ((int)cellY * (m_width / m_cellsize));
}
// void SpatialHash::clear()
// {
//     for (int i = 0 ; i < nBuckets; i++) {
//         buckets[i].clear();
//     }
//     //delete buckets;
//     //free(buckets);
// }

// // Getters //
// int SpatialHash::getBucketCount()
// {
//     return nBuckets;
// }

// Bucket *SpatialHash::getBuckets()
// {
//     return buckets;
// }
// SpatialHash::~SpatialHash()
// {
//    delete[] buckets;
// }

void SpatialHash::print()
{
    for (int i = 0; i < nBuckets; i++){
        printf("i: %d \t", i);
        int size = (*table)[i].size();
        printf("s: %d \n", size);
    }
}