#ifndef FOC_H_
#define FOC_H_

#include <stdio.h>


#define ONE_OVER_SQRT_3 0.57735026919f
#define TWO_OVER_SQRT_3 1.15470053838f
#define SQRT_3_OVER_2   0.86602540378f

struct clarkepark_vars{
    float d;
    float q;
    float a;
    float b;
    float u;
    float v;
    float w;
};

class FOC {
public:
    FOC();
    virtual ~FOC();
protected:
    clarkepark_vars inv_clarke_park;
    clarkepark_vars clarke_park;
    float sine_val;
    float cos_val;
    float electrical_angle;
    void ClarkeParke();
    void InvClarkeParke();
    void _calculate_sin_and_cos_values_of_angle();
};

#endif /* FOC_H_ */
