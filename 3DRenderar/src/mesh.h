#ifndef MESH_H
#define MESH_H

#include "vector.h"

#define N_MESH_VERTICES 8

vec3_t mesh_vertices[N_MESH_VERTICES] = {
    {.x = -1, .y = -1, .z = -1}, {.x = -1, .y = 1, .z = -1},
    {.x = 1, .y = 1, .z = -1},   {.x = 1, .y = -1, .z = -1},
    {.x = 1, .y = 1, .z = 1},    {.x = 1, .y = -1, .z = 1},
    {.x = -1, .y = 1, .z = 1},   {.x = -1, .y = -1, .z = 1},
};

#endif
