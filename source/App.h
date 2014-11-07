#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/OpenGL.h>
#elif _WIN32
  #define GLEW_STATIC
  #include "windows.h"
  #include <GL/glew.h>
#else
  #include <GL/gl.h>
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

		bool isRunning;

		SDL_Window* window;
		SDL_Renderer* renderer;
        SDL_GLContext glContext;

        Leap::Controller controller;
        GLuint rawLeftTexture;
        GLuint rawRightTexture;
        GLuint distortionLeftTexture;
        GLuint distortionRightTexture;

        bool showLeftImage;
		int windowWidth;
		int windowHeight;
        
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