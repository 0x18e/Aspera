#include "Engine.h"

#include "Mesh.h"
// important early goals
/*use RAII*/
/*kernighan and ritchie convention*/
/*hungarian notation*/
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	LOG("Changing");
}

int main(int argc, char* argv[]){
    

	Engine engine;

	engine.Initialize();
	engine.Run();

	


	return 0;
}
