#pragma once
#include "tools.h"


/// <summary>
/// All videogame logic should be handled here
/// As a way to separate the engine from the 
/// </summary>
class Logic {

	// Game logic will have a delta time that is given to it via reference from main engine.
	// Game logic is separate from engine and other modules such as physics, audio, window handling, etc
	// This will have its main Init, Update, & Render function.
	// Engine calls these functions in run.
public:
	Logic();
	~Logic();

	void Update();
	void Render();


private:
	
	float m_fDeltaTime; // Might be static in order to track everywhere else or global...
	

};

