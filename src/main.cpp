#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define LOG(x) std::cout << x << '\n';
// important early goals
/*use RAII*/
/*kernighan and ritchie convention*/
/*hungarian notation*/
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]){
	
	float window_width, window_height;
	window_width = 800.0f;
	window_height = 600.0f;
	LOG("argv: " << argv[0] << '\n');
	//initialize glfw
	if (!glfwInit()){
		LOG("Could not initialize glfw");
	}
	// on macos, the opengl version has to be set explicitly to 3 or it throws a segfault? what voodoo shit is this
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "lorem ipsum", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Load opengl functions from glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// GLAD initialization failed
		LOG("Failed to initialize glad functions");
		return -1;
	}

	// Transforming random things using matrix math
	// example! moving vector (1, 0, 0) by (1, 1, 0)
	glm::vec4 vec = glm::vec4(1, 0, 0, 1); // the last 1 is our homogenous coordinate
	glm::mat4 identity = glm::mat4(1.0f); // create our identity matrix,
	glm::vec3 mov(1, 1, 0);
	glm::mat4 trans = glm::translate(identity, mov); // this is now the matrix we need to multiply stuff

	vec = trans * vec;

	LOG("x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z);
	
	// vertices
	float vertices[] = {
		// positions		// colors		// texture coords
		-0.5f, 0.5, 0.0f, 0.5f, 0.5f, 0.5f,	0.0f, 1.0f, // top left corner
		-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // bottom left
		0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.5f, 0.2f, 0.4f, 1.0f, 0.0f	// bottom right
	};
	int indices[] = {
		0, 2, 1, // first triangle
		3, 2, 1 // second triangle
	};

	unsigned int VAO, VBO, EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind our current buffer
	glGenVertexArrays(1, &VAO); // create our vertex array object
	glBindVertexArray(VAO); // bind our vertex array!!

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// bind stuff to the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// layout location = 0, positions!
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	// load texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, channel_count;

	unsigned char* data = stbi_load("W:\\Projects\\repos\\Aspera\\textures\\debug_empty.png",
		&width, &height, &channel_count, 0);
	// check if data actually got put in
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		LOG("Did not load texture properly");
	}

	//TODO: CREATE THE FRUSTUM
	// Also add the projection, view, and model matrices to our shaders
	// this computation i believe is needed only once unless, the vertices move a lot.
	
	// matrices need to be read from left to right!
	// so all orders of multiplication need to be flipped
	glm::mat4 projection, model, view;

	model = glm::mat4(1.0f); // create our identity matrix, all diagonals are 1
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // rotate about the x
	
	view = glm::mat4(1.0f); // identity matrix!!

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	// the reason this is -3.0f, is because to go backwards we shift the whole scene forwards

	// last thing to make is the projection matrix, we will be using perspective matrix
	// cause perspective...
	projection = glm::perspective(glm::radians(54.0f), window_width / window_height, 0.1f, 100.0f);

	// now to send them off to the shader!



	// create our shader
	Shader shader("W:\\Projects\\repos\\Aspera\\shaders\\vert.vs", "W:\\Projects\\repos\\Aspera\\shaders\\frag.fs");
	// since this is a 2d triangle, we just draw it now
	shader.use();
	shader.SetInt("missing_texture", 0);

	
	shader.SetMat4("model", model);
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		model = glm::rotate(model, ((float)glfwGetTime() * 0.3f )* glm::radians(10.0f), glm::vec3(0.5f, 0.0f, 0.0f));
		shader.SetMat4("model", model);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	


	return 0;
};
