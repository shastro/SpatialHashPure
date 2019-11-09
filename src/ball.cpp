// #include "ball.hpp"


// /////////////
// // PHYSICS //
// /////////////


// void Ball::applyForce(Eigen::Vector2f force, double time_delta)
// {
	
// 	m_p = m_p + (force * time_delta);

// }

// //Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
// void Ball::update(double time_delta, int b_zone)
// {

	
// 	//applyForce(Eigen::Vector2f(0.0, 30000000), time_delta); //Gravity 
// 	//m_acc = m_acc + Eigen::Vector2f(0.0, 800000000);

// 	Eigen::Vector2f m_acc_cpy = m_acc;
// 	Eigen::Vector2f m_vel_cpy = m_vel;

// 	//Integration of Newton's Laws

// 	m_pos = m_pos + (m_p/m_mass)*time_delta;

// 	//Speed Clamping at Rest
// 	if(m_vel.squaredNorm() < 0.00005){
// 		m_vel = m_vel * 0;
// 	}

// 	float c_e = 0.5; //Coefficient of Elasticity (roughly speaking) this only applies to wall collision 


// 	//Edge Detection
// 	if (m_pos[0] + m_radius > m_window->width - b_zone) {
// 		m_pos[0] = m_window->width - b_zone - m_radius;
// 		m_vel[0] *= -c_e;
// 	}
// 	if (m_pos[0] - m_radius < b_zone) {
// 		m_pos[0] = m_radius + b_zone;
// 		m_vel[0] *= -c_e;
// 	}

// 	if (m_pos[1] +  m_radius > m_window->height - b_zone) {
// 		m_pos[1] = m_window->height - b_zone - m_radius;
// 		m_vel[1] *= -c_e;
// 	}

// 	if (m_pos[1] - m_radius < b_zone) {
// 		m_pos[1] = m_radius + b_zone;
// 		m_vel[1] *= -c_e;
// 	}

// 	//Air Drag
// 	//applyForce(mult2f_cpy(m_vel, -10), time_delta);


// }

// //Spring Force, sums of momentum divided by radii sum squared


// void Ball::addBucket(int bucketid)
// {
// 	//bucketids.emplace_back(bucketid);
// 	// if(bucketids_Max < 3){
// 		bucketids[bucketids_Max] = bucketid;
// 	// if(bucketids_Max < 3)
// 		bucketids_Max++;
// 	// }
// }

// void Ball::clearBuckets()
// {
// 	//PRINT("CLEARED")
// 	for(int i = 0; i < bucketids_Max; i++){
// 		//PRINT(bucketids[i])
// 		bucketids[i] = -1;
// 	}
// 	//LOG("ID: ", id)
// 	//LOG("MAX: ", bucketids_Max + 1)
// 	bucketids_Max = 0;
// 	// bucketids.clear();
// 	// bucketids.shrink_to_fit();
// 	// std::vector<int>().swap(bucketids);
// }


// Ball::~Ball()
// {
// 	//printf("Ball %d Deleted\n", id);
// }

