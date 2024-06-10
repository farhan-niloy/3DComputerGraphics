#include "mesh.h"
#include "array.h"
#include "triangle.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mesh_t mesh = {.vertices = NULL, .faces = NULL, .rotation = {0, 0, 0}};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
    {.x = -1, .y = -1, .z = -1}, {.x = -1, .y = 1, .z = -1},
    {.x = 1, .y = 1, .z = -1},   {.x = 1, .y = -1, .z = -1},
    {.x = 1, .y = 1, .z = 1},    {.x = 1, .y = -1, .z = 1},
    {.x = -1, .y = 1, .z = 1},   {.x = -1, .y = -1, .z = 1},
};

face_t cube_faces[N_CUBE_FACES] = {
    // front
    {.a = 0, .b = 1, .c = 2},
    {.a = 0, .b = 2, .c = 3},
    // right
    {.a = 3, .b = 2, .c = 4},
    {.a = 3, .b = 4, .c = 5},
    // back
    {.a = 5, .b = 4, .c = 6},
    {.a = 5, .b = 6, .c = 7},
    // left
    {.a = 7, .b = 6, .c = 1},
    {.a = 7, .b = 1, .c = 0},
    // top
    {.a = 1, .b = 6, .c = 4},
    {.a = 1, .b = 4, .c = 2},
    // bottom
    {.a = 7, .b = 0, .c = 3},
    {.a = 7, .b = 3, .c = 5},
};

void load_cube_mesh_data(void) {
  for (int i = 0; i < N_CUBE_VERTICES; i++) {
    vec3_t cube_vertex = cube_vertices[i];
    array_push(mesh.vertices, cube_vertex);
  }
  for (int i = 0; i < N_CUBE_FACES; i++) {
    face_t cube_face = cube_faces[i];
    array_push(mesh.faces, cube_face);
  }
}

void load_obj_file_data(char *filename) {
  FILE *file;

  file = fopen(filename, "r");
  char line[1024];

  while (fgets(line, 1024, file)) {
    if (strncmp(line, "v ", 2) == 0) {
      vec3_t vertex;
      sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
      array_push(mesh.vertices, vertex);
    }

    if (strncmp(line, "f ", 2)) {
      int vertex_indices[3];
      int texture_indices[3];
      int normal_indices[3];
      sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertex_indices[0],
             &texture_indices[0], &normal_indices[0], &vertex_indices[1],
             &texture_indices[1], &normal_indices[1], &vertex_indices[2],
             &texture_indices[2], &normal_indices[2]);
      face_t face = {.a = vertex_indices[0],
                     .b = vertex_indices[1],
                     .c = vertex_indices[2]};
    }
  }

  fclose(file);
}
