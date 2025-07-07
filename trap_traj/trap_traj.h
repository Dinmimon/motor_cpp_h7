/*
 * trap_traj.h
 *
 *  Created on: Apr 29, 2025
 *      Author: din.maimon
 */

#ifndef TRAP_TRAJ_H_
#define TRAP_TRAJ_H_

#include <stdio.h>

#include <stdbool.h>

typedef struct {
    bool trajectory_active;
    //	motion requirements from the trajectory
    float max_acceleration;
    float max_deceleration;
    float max_velocity;
    float destination;
    //	calculated values
    float acceleration_distance;
    float deceleration_distance;
    float constant_speed_distance;
    //	current state of trajectory
    float current_position;
    float current_velocity;
}TRAPEZ_trapezoidalTrajectory_t, * TRAPEZ_trapezoidalTrajectory_tp;

void trajectory_init(
    TRAPEZ_trapezoidalTrajectory_tp traj,
    float max_acceleration,
    float max_deceleration,
    float max_velocity,
    float destination);

void trapez_trajectory_process(
    TRAPEZ_trapezoidalTrajectory_tp traj,
    float delta_time);

void trapez_trajectory_process(TRAPEZ_trapezoidalTrajectory_tp t, float dt);
void trajectory_init(TRAPEZ_trapezoidalTrajectory_tp t,float max_acceleration,
        float max_deceleration,float max_velocity,float destination);

#endif /* TRAP_TRAJ_H_ */
