#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/OpenGL.h>
#elif _WIN32
  #define GLEW_STATIC
  #include <GL/glew.h>
  #include "windows.h"
#else
  #include <GL/glew.h>
#endif

#include "Log.h"
#include "SDL.h"
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
		void onEvent(SDL_Event* event);
		bool init();
		void update();
		void render();
		void cleanup();

	public:
		int execute(int argc, char* argv[]);

	public:
		static App* getInstance();

};

#endif