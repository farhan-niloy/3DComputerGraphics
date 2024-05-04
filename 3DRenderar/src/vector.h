#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} vec2_t;

typedef struct {
  float x;
  float y;
  float z;
} vec3_t;

vec3_t vec3_rodate_x(vec3_t v, float angle);
vec3_t vec3_rodate_y(vec3_t v, float angle);
vec3_t vec3_rodate_z(vec3_t v, float angle);

#endif
