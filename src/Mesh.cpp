#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
    this->m_Vertices = vertices;
    this->m_Indices = indices;
    this->m_Textures = textures;
    this->SetupMesh();
}

void Mesh::SetupMesh() {
    
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind current buffer
	glGenVertexArrays(1, &VAO); // create vertex array object
	glBindVertexArray(VAO); // bind vertex array!!

	glBufferData(GL_ARRAY_BUFFER, this->m_Vertices.size() * sizeof(Vertex), this->m_Vertices.data(), GL_STATIC_DRAW);
	
	// bind stuff to the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_Indices.size() * sizeof(unsigned int), this->m_Indices.data(), GL_STATIC_DRAW);
	// layout location = 0, positions!, 
	// REMINDER, THESE MIGHT HAVE TO CHANGE LATER CAUSE OF HOW OGL DOES ITS SHADERS, OR REWRITE THEM HOW YOU WANT THEM


	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinates));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	/*
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	*/
	// load texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	/*
	// This stuff shouldnt be here but I was testing
   #ifdef WIN32
	this->m_pszData= stbi_load("W:\\Projects\\repos\\Aspera\\textures\\debug_empty.png",
		&m_nWidth, &m_nHeight, &m_nChannelCount, 0);
    #endif
    #ifdef linux
    data = stbi_load("../textures/debug_empty.png", &width, &height, &channel_count, 0);
    #endif
	// check if data actually got put in
	if (this->m_pszData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pszData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		LOG("Did not load texture properly");
	}
	*/
}
void Mesh::Draw(Shader &shader){

	/*
	* I took this from the opengl website, I need to do more research
	* on what a better method might be, or really try to understand shaders & write my own implementation.
	* For now.
	*/
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = m_Textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.SetInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


};

