#include "vector.h"
#include <math.h>

vec3_t vec3_rodate_x(vec3_t v, float angle) {
  vec3_t rotated_vector = {.x = v.x,
                           .y = v.y * cos(angle) - v.z * sin(angle),
                           .z = v.y * sin(angle) + v.z * cos(angle)};
  return rotated_vector;
}

vec3_t vec3_rodate_y(vec3_t v, float angle) {
  vec3_t rotated_vector = {.x = v.x * cos(angle) - v.z * sin(angle),
                           .y = v.y,
                           .z = v.y * sin(angle) + v.z * cos(angle)};
  return rotated_vector;
}

vec3_t vec3_rodate_z(vec3_t v, float angle) {
  vec3_t rotated_vector = {.z = v.x,
                           .x = v.y * cos(angle) - v.z * sin(angle),
                           .y = v.y * sin(angle) + v.z * cos(angle)};
  return rotated_vector;
}
