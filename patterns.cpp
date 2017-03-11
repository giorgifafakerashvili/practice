#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class Particle {
 public:
 	Particle()
 		: fragment_left_(0)
 	{

 	}

 	void init(double x, double y, 
 						 double x_vel, double y_vel, 
 						 int lieftime) {
 		x_ = x; 
 		y_ = y; 
 		x_vel_ = x_vel; 
 		y_vel_ = y_vel; 
 		fragment_left_ = lifetime; 
 	} 

 	void animate() {
 		if(!inUse()) return;

 		fragment_left_--; 
 		x_ += x_vel_; 
 		y_ += y_vel_; 

 	} 

 	bool inUse() const {
 		return fragment_left_ > 0; 
 	}


};


class ParticlePool {
 public:
 	void create(double x, double y, 
 						  double x_vel, double y_vel, 
 						  int lifetime); 

 	void animate() {
 		for(int i = 0; i < POOL_SIZE; ++i) {
 			particles_[i].animate();  
 		}
 	}

 private:
 	static const int POOL_SIZE = 100; 
 	Particle particles_[POOL_SIZE]; 

}; 

void ParticlePool::create(double x, double y, 
												  double x_vel, double y_vel, 
												  int lifetime) {
	// find an available particle 
	for(int i = 0; i < POOL_SIZE; ++i) {
		if(!particles_[i].inUse()) {
			particles_[i].init(x, y, x_vel, y_vel, lieftime); 
		} 
	}

}



int main(int argc, char* argv[]) {



	return 0;
}