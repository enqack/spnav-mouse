#include <math.h>

int clampi(int val, int min, int max) { return val < min ? min : (val > max ? max : val); }

float clampf(float val, float min, float max) { return val < min ? min : (val > max ? max : val); }

int apply_acceleration(int value, float factor) {
  if (value == 0) return 0;
  float sign = value < 0 ? -1.0f : 1.0f;
  float absval = fabsf((float)value);
  return (int)(sign * (absval * absval * factor));
}
