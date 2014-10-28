//==============================================================================
/*
	Primary application class

	3/11/2014
    SDLTutorials.com
    Tim Jones
*/
//==============================================================================
#include "Log.h"
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include "Leap.h"
#include "LeapMath.h"
#include "util.h"

#ifndef __APP_H__
	#define __APP_H__

//shaders
static const std::string PASSTHROUGH_VERTEXT_SHADER = "vertex.vsl";
static const std::string CORRECTING_FRAGMENT_SHADER = "fragment.fsl";

class App {
	private:
		static App instance;

		bool isRunning = true;

		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
        SDL_GLContext glContext = NULL;

		int windowWidth = 1024;
		int windowHeight = 768;

        Leap::Controller controller;
        GLuint rawLeftTexture = 0;
        GLuint rawRightTexture = 0;
        GLuint distortionLeftTexture = 0;
        GLuint distortionRightTexture = 0;

        Leap::Matrix cameraMatrix = Leap::Matrix(Leap::Vector::zAxis(), 0, Leap::Vector(0, 0, -4.0));

        bool showLeftImage = false;
        
	private:
		App();

		// Capture SDL Events
		void onEvent(SDL_Event* event);

		// Initialize our SDL game / app
		bool init();

		// Logic loop
		void update();

		// Render loop (draw)
		void render();

		// Free up resources
		void cleanup();

	public:
		int execute(int argc, char* argv[]);

	public:
		static App* getInstance();

};

#endif