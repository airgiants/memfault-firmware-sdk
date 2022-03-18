#ifndef constrain_h
#define constrain_h
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



float fmapConstrained(float x, float in_min, float in_max, float out_min, float out_max)
{
  float f = fmap( x,  in_min, in_max, out_min, out_max);

  if( f < min(out_min, out_max) )
    f = min(out_min, out_max);

  if( f > max(out_min, out_max) )
    f = max(out_min, out_max);

  return f;
}



float f3mapConstrained(float x, float in_min, float in_max, float out_min, float out_mid, float out_max)
{
  float a = fmapConstrained(x, in_min, in_max, out_min, out_mid);
  float b = fmapConstrained(x, in_min, in_max, out_mid, out_max);
  return min(a,b);
}


float fconstrain(float f, float out_min, float out_max)
{
  if( f < min(out_min, out_max) )
    f = min(out_min, out_max);

  if( f > max(out_min, out_max) )
    f = max(out_min, out_max);

  return f;
}

#endif