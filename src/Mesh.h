#pragma once
#include "Shader.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <vector>
#include "stb_image.h"
#include "tools.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 colors;
    glm::vec2 texture_coordinates; 

};

struct Texture {
    unsigned int ID;
};

class Mesh {

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int texture;
    unsigned char* data;
    int width, height, channel_count;

   
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
    unsigned int VAO, VBO, EBO;
    void SetupMesh();
};
