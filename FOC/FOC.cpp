#include "FOC.h"
#include <cmath>

FOC::FOC() {
    // Constructor
}

FOC::~FOC() {
    // Destructor
}

void FOC::InvClarkeParke()
{
	inv_clarke_park.b = ((inv_clarke_park.d * sine_val) + (inv_clarke_park.q * cos_val));
	inv_clarke_park.a = ((inv_clarke_park.d * cos_val) - (inv_clarke_park.q * sine_val));
	inv_clarke_park.u = inv_clarke_park.a;
	inv_clarke_park.v = ((-0.5f * inv_clarke_park.a) + SQRT_3_OVER_2 * inv_clarke_park.b);
	inv_clarke_park.w = ((-0.5f * inv_clarke_park.a) - SQRT_3_OVER_2 * inv_clarke_park.b);
}

void FOC::ClarkeParke()
{
	clarke_park.a = clarke_park.u;
	clarke_park.b = ((ONE_OVER_SQRT_3 * clarke_park.u) + (TWO_OVER_SQRT_3 * clarke_park.v));
	clarke_park.d = ((clarke_park.a * cos_val) + (clarke_park.b * sine_val));
	clarke_park.q = ((clarke_park.b * cos_val) - (clarke_park.a * sine_val));
}

void FOC::_calculate_sin_and_cos_values_of_angle()
{
    sine_val = sinf(electrical_angle);
    cos_val = cosf(electrical_angle);
}
