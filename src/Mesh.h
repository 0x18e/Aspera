#pragma once
#include "Shader.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <vector>
#include "stb_image.h"
#include "tools.h"


// Structs use sequential memory.
// Use better naming conventions, really nit picking here. Stick to Hungarian
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    //glm::vec3 colors;
    glm::vec2 texture_coordinates;
};

// This needs to change later on
struct Texture {
    unsigned int ID;
    std::string type;
};


class Mesh {
    // This class is good but a part of it borrows a lot from the learnopengl website. Which is fine, just shouldnt be
    // Permanent
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
    unsigned int m_texture;
    unsigned char* m_pszData;
    int m_nWidth, m_nHeight, m_nChannelCount;

   
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
    unsigned int VAO, VBO, EBO; // Change later!! stick to hungarian notation!!!
    void SetupMesh();


};
