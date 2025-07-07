/**********************************************************************
 *  Trapezoidal-trajectory generator – fixed edition (2025-04-29)
 *  Sign conventions
 *      • max_acceleration   > 0  (magnitudes)
 *      • max_deceleration   > 0
 *      • max_velocity       > 0
 *      • destination        ≥ 0  (extend easily to <0 if you need)
 *********************************************************************/

#include <math.h>
#include <stdbool.h>
#include "trap_traj.h"
#define EPS_POS   1e-5f          /* position tolerance  (units)   */
#define EPS_VEL   1e-5f          /* velocity tolerance (units/s)  */

/* ───────────────── helper ───────────────── */

static void calc_d_acc_dec(TRAPEZ_trapezoidalTrajectory_tp t)
{
    /* time to ramp up/down */
    const float t_acc = t->max_velocity / t->max_acceleration;
    const float t_dec = t->max_velocity / t->max_deceleration;

    /* s = ½ a t² */
    t->acceleration_distance = 0.5f * t->max_acceleration * t_acc * t_acc;
    t->deceleration_distance = 0.5f * t->max_deceleration * t_dec * t_dec;

    /* useful for diagnostics */
    t->constant_speed_distance =
        fmaxf(t->destination - t->acceleration_distance - t->deceleration_distance, 0.0f);
}

/* peak-velocity when the run is too short for Vmax
 * v_peak² = 2·s·a_acc·a_dec / (a_acc + a_dec)
 */
static void limit_max_velocity(TRAPEZ_trapezoidalTrajectory_tp t)
{
    const float num   = 2.0f * t->destination * t->max_acceleration * t->max_deceleration;
    const float denom = t->max_acceleration + t->max_deceleration;

    if (denom < EPS_VEL) {          /* both accelerations ~0 ⇒ disable */
        t->trajectory_active = false;
        return;
    }

    t->max_velocity = sqrtf(fmaxf(num / denom, 0.0f));
}

/* ───────────────── public API ───────────────── */

void trajectory_init(
        TRAPEZ_trapezoidalTrajectory_tp t,
        float max_acceleration,
        float max_deceleration,
        float max_velocity,
        float destination)
{
    if (!t) return;

    /* guard against impossible parameters */
    if (max_acceleration <= EPS_VEL ||
        max_deceleration <= EPS_VEL ||
        max_velocity     <= EPS_VEL ||
        destination      <  EPS_POS)
    {
        t->trajectory_active = false;
        return;
    }

    /* copy user parameters */
    t->max_acceleration = fabsf(max_acceleration);   /* magnitudes only */
    t->max_deceleration = fabsf(max_deceleration);
    t->max_velocity     = fabsf(max_velocity);
    t->destination      = destination;

    t->current_position = 0.0f;
    t->current_velocity = 0.0f;

    /* compute distances for the requested Vmax */
    calc_d_acc_dec(t);

    /* shorten the profile if we cannot reach Vmax */
    if (t->destination < t->acceleration_distance + t->deceleration_distance) {
        limit_max_velocity(t);
        calc_d_acc_dec(t);          /* redo with the limited Vmax */
    }

    t->trajectory_active = true;
}

void trapez_trajectory_process(TRAPEZ_trapezoidalTrajectory_tp t, float dt)
{
    if (!t || !t->trajectory_active || dt <= 0.0f) return;

    const float s_remaining = t->destination - t->current_position;

    /* ───── termination test ───── */
    if (s_remaining <= EPS_POS && t->current_velocity <= EPS_VEL) {
        t->current_position   = t->destination;
        t->current_velocity   = 0.0f;
        t->trajectory_active  = false;
        return;
    }

    /* ───── three-phase profile ───── */
    if (t->current_position < t->acceleration_distance) {
        /* 1. accelerate */
        t->current_position += t->current_velocity * dt
                             + 0.5f *  t->max_acceleration * dt * dt;

        t->current_velocity = fminf(t->current_velocity
                                   + t->max_acceleration * dt,
                                    t->max_velocity);
    }
    else if (t->current_position >= t->destination - t->deceleration_distance) {
        /* 3. decelerate (note: –a) */
        t->current_position += t->current_velocity * dt
                             - 0.5f *  t->max_deceleration * dt * dt;

        t->current_velocity = fmaxf(t->current_velocity
                                   - t->max_deceleration * dt,
                                    0.0f);
    }
    else {
        /* 2. cruise */
        t->current_velocity = t->max_velocity;
        t->current_position += t->current_velocity * dt;
    }
}
