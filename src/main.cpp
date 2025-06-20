#include "Engine.h"

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
// important early goals
// use RAII
// kernighan and ritchie convention
// hungarian notation
// use public, protected, private conventions.


int main(int argc, char* argv[]){
	Engine engine;

	engine.Run();

	return 0;
}
