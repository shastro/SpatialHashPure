#include "grid.hpp"


////////////
// Bucket //
////////////

void Bucket::fill(std::vector <Ball>& iBalls)
{
    // if (!(iBalls.empty())) {
    //     vBalls.insert(vBalls.end(), iBalls.begin(), iBalls.end());
    // } else {
    //     vBalls = iBalls;
    // }
}

void Bucket::insert(Ball &ball)
{
    Balls.emplace_back(ball);
    //PRINT(index)
    //vBalls.emplace_back(ball);

}

std::vector<Ball> *Bucket::get()
{
    return &Balls;
}


void Bucket::clear()
{
    //free(Balls);
    Balls.clear();
    Balls.shrink_to_fit();
    std::vector<Ball>().swap(Balls);
}

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
        buckets = new Bucket[nBuckets];
        ballqueue = new std::vector<Ball>;
        ballqueue->reserve(sizeof(Ball) * 30);

        LOG("CS: ", m_cellsize)
        LOG("nBuckets: ", nBuckets)
    }
    
void SpatialHash::build(std::vector<Ball>& vecBalls)
{

    //Place balls in buckets
    for (auto & ball : vecBalls) {
        insert(ball);
    }

}

std::vector<Ball>* SpatialHash::query(Ball &ball)
{
    //std::vector<Ball> *ballqueue = new std::vector<Ball>;
     Bucket bucket;
    std::vector<Ball> *b_balls;

    //Add relevant buckets to ball buckets
    for (int i = 0 ; i < ball.bucketids_Max; i++) {
        int id = ball.bucketids[i];
            
        // LOG( "max ",ball.bucketids_Max)
        // LOG("id ", id)
        bucket = buckets[id];
        b_balls = bucket.get();

        //(*ballqueue) += (*b_balls);
       // ballqueue->reserve(ballqueue->size() + b_balls->size());
        ballqueue->insert(std::end(*ballqueue), std::begin(*b_balls), std::end(*b_balls));
            // (echo ../bin/ParticleRenderer sp1.json ; echo ../bin/ParticleRenderer sp2.json) | parallel 
    }

    std::vector<Ball>().swap(*b_balls);
   // PRINT("bb " << b_balls->size())
   // PRINT("bq " << ballqueue->size())
   //b_balls->clear();
    return ballqueue;
}

void SpatialHash::insert(Ball& ball)
{
    // Upper Left
    float ulX = ball.m_pos[0] - ball.m_radius;
    float ulY = ball.m_pos[1] - ball.m_radius;

    //Bottom Right
    float brX = ball.m_pos[0] + ball.m_radius;
    float brY = ball.m_pos[1] + ball.m_radius;

    //Bottom Left
    float blX = ulX;
    float blY = ulY + (ball.m_radius + ball.m_radius);

    //Upper Right
    float urX = ulX + (ball.m_radius + ball.m_radius);
    float urY = ulY;

    //ids
    int ulId = pointQuery(ulX, ulY);
    int brId = pointQuery(brX, brY);
    int blId = pointQuery(blX, blY);
    int urId = pointQuery(urX, urY);

    // PRINT("ul " << ulId << " br " << brId << " bl " << blId << " ur " << urId)
    if (ulId == brId) {
        ball.addBucket(ulId);
        (buckets[ulId]).insert(ball);
        // Ball must be in 4 buckets
    } else if ((ulId != brId) && (ulId != blId) && (ulId != urId)) {
        ball.addBucket(ulId); //Upp Left
        ball.addBucket(brId); //Bot Right
        ball.addBucket(urId); //Upp Right
        ball.addBucket(blId); //Bot Left
        
        (buckets[ulId]).insert(ball);
        (buckets[brId]).insert(ball);
        (buckets[urId]).insert(ball);
        (buckets[blId]).insert(ball);
  
        //Ball must be in two buckets
    } else {
        ball.addBucket(ulId);
        ball.addBucket(brId);

        (buckets[ulId]).insert(ball);
        (buckets[brId]).insert(ball);
    }
    // PRINT(buckets[50].get()->size())

}

int SpatialHash::pointQuery(float x, float y)
{
    float cellX = floor(x / m_cellsize);
    float cellY = floor(y / m_cellsize);
    return (int)cellX + ((int)cellY * (m_width / m_cellsize));
    //return buckets + bucketid;
}
void SpatialHash::clear()
{
    for (int i = 0 ; i < nBuckets; i++) {
        buckets[i].clear();
    }
    //delete buckets;
    //free(buckets);
}

// Getters //
int SpatialHash::getBucketCount()
{
    return nBuckets;
}

Bucket *SpatialHash::getBuckets()
{
    return buckets;
}
SpatialHash::~SpatialHash()
{
   delete[] buckets;
}