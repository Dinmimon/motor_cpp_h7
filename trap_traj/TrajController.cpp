/*
 * TrajController.cpp
 *
 *  Created on: Sep 11, 2025
 *      Author: din.maimon
 */

#include <TrajController.h>

#include "TrajController.h"

void TrajController::init(float max_acc, float max_dec, float max_vel, float dest) {
    trajectory_init(&trajectory, max_acc, max_dec, max_vel, dest);
}

void TrajController::process(float dt) {
    if (traj_active) {
        trapez_trajectory_process(&trajectory, dt);
    }
}