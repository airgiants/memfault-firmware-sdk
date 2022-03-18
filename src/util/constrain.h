#ifndef constrain_h
#define constrain_h

float fmap(float x, float in_min, float in_max, float out_min, float out_max);

float fmapConstrained(float x, float in_min, float in_max, float out_min, float out_max);


float f3mapConstrained(float x, float in_min, float in_max, float out_min, float out_mid, float out_max);


float fconstrain(float f, float out_min, float out_max);

#endif