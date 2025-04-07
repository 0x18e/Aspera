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
	
	LOG("argv: " << argv[0] << '\n');
	//initialize glfw
	if (!glfwInit()){
		LOG("Could not initialize glfw");
	}
	// on macos, the opengl version has to be set explicitly to 3 or it throws a segfault? what voodoo shit is this
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	

	GLFWwindow* window = glfwCreateWindow(800, 600, "lorem ipsum", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Load opengl functions from glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// GLAD initialization failed
		LOG("Failed to initialize glad functions");
		return -1;
	}


	// general positions, imagine you're writing vertices for an actual square.
	// generally in opengl this isnt what usually happens, you would load models from blender
	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};


	// for the EBO
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// create our buffers
	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); // make our ebo as well
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO); // now any calls to VAO or our EBO would happen here

	// now we feed our data into our VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind our buffer first
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// setup our EBO, cause i forgot
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// data has been fed into our current GL_ARRAY_BUFFER object
	// check later
	//glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind our buffer, might be a mistake

	// fill in our vertex attribute pointers
	// layout location for our position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); // enable our tex coords after we filled them

	

	// create our texture
	unsigned int debug_texture;
	glGenTextures(1, &debug_texture); // create texture
	glBindTexture(GL_TEXTURE_2D, debug_texture); // we bind GL_TEXTURE_2D to our current texture
	
	// parameters can be set here and all that, probably before as well.

	// Load our textures data and hold its width and height variables
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data;	
#ifdef _WIN64
	data = stbi_load("W:\\Projects\\repos\\Aspera\\textures\\debug_empty.png",
		&width, &height, &nrChannels, 0);
#endif
#ifdef __APPLE__
	LOG("loading texture on apple");
	data = stbi_load("../textures/debug_empty.png", &width, &height, &nrChannels, 0);
#endif
	if (data) {
		// to whatever is bound to our current gl_texture2d, heres what it is, and its data.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		LOG("Loaded texture data");
	}
	else {
		LOG("Could not load texture data");
	}


	// i like to load shaders at the end, dont know why it just makes sense to me.
#ifdef _WIN32
	Shader shader("W:\\Projects\\repos\\Aspera\\shaders\\vertex.vs", "W:\\Projects\\repos\\Aspera\\shaders\\fragment.fs");
#endif
#ifdef __APPLE__
	Shader shader("../shaders/vertex.vs", "../shaders/fragment.fs");
#endif
	// this is the part that might really fuck me over
	// before running, we make sure that our sampler knows that GL_TEXTURE_2D, is bound to GL_TEXTURE_0
	// if this never happens then it never knows where this textures location belongs in.
	shader.use();
	shader.SetInt("texture1", 0); 

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, debug_texture);

		shader.use();
		
		// here is the hard part, matrix logic, it all makes sense but does the code check out?
		// initialize our matrices with their identity matrix
		glm::mat4 model = glm::mat4(1.0f); 
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		
		// rotate our camera by -55 degrees
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		// move our camera backwards
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		//setup the projection matrix, first argument can be seen as fov
		projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	
		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
		unsigned int projLoc = glGetUniformLocation(shader.ID, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// render container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		processInput(window);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}



	return 0;
};
