/*
 * TrajController.h
 *
 *  Created on: Sep 11, 2025
 *      Author: din.maimon
 */

#ifndef TRAJ_CONTROLLER_H
#define TRAJ_CONTROLLER_H

#include "trap_traj.h"

class TrajController {
public:
    void init(float max_acc, float max_dec, float max_vel, float dest);
    void process(float dt);
    void activate(bool active) { traj_active = active; }
    bool isActive() const { return traj_active; }
    
private:
    TRAPEZ_trapezoidalTrajectory_t trajectory;
    bool traj_active = false;
};

#endif