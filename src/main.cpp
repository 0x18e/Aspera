#include "Engine.h"

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
// important early goals
/*use RAII*/
/*kernighan and ritchie convention*/
/*hungarian notation*/
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------



int main(int argc, char* argv[]){
	Engine engine;

	engine.Run();

	return 0;
}
