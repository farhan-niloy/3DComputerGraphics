#include "mesh.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mesh_t mesh = {.vertices = NULL,
               .faces = NULL,
               .rotation = {0, 0, 0},
               .scale = {1.0, 1.0, 1.0},
               .translation = {0, 0, 0}};

void load_obj_file_data(char *filename) {
  FILE *file = fopen(filename, "r");

  char line[1024];

  while (fgets(line, 1024, file)) {
    if (strncmp(line, "v ", 2) == 0) {
      vec3_t vertex;
      sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);

      array_push(mesh.vertices, vertex);
    } else if (strncmp(line, "f ", 2) == 0) {
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

      array_push(mesh.faces, face);
    }
  }

  fclose(file);
}
