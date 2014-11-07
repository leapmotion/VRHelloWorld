//==============================================================================
#include "App.h"

App App::instance;
GLuint vertShader, fragShader, program;

App::App() {
	isRunning = true;
	showLeftImage = false;
	windowWidth = 1024;
	windowHeight = 768;
}

using namespace Leap;

//------------------------------------------------------------------------------
bool App::init() {
    //Enable Leap Motion images and optimize controller for HMD use
    controller.setPolicyFlags(static_cast<Controller::PolicyFlag>(Controller::PolicyFlag::POLICY_IMAGES | Controller::PolicyFlag::POLICY_OPTIMIZE_HMD));

    //SDL setup
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    	Log("Unable to Init SDL: %s", SDL_GetError());
    	return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    Log("If error setting version: %s", SDL_GetError());

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        Log("Unable to Init hinting: %s", SDL_GetError());
    }

    if((window = SDL_CreateWindow(
    	"Leap Motion VR",
    	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    	windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
    ) == NULL) {
    	Log("Unable to create SDL Window: %s", SDL_GetError());
    	return false;
    }

    glContext = SDL_GL_CreateContext(window);

    if((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        Log("Unable to create renderer");
        return false;
    }

    SDL_GL_MakeCurrent(window, glContext);

    Log("gl_renderer: %s", glGetString(GL_RENDERER));
    Log("gl_version: %s", glGetString(GL_VERSION));
    Log("glsl_version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    //Scene setup

    //Create the shader program
    program = createProgram(PASSTHROUGH_VERTEXT_SHADER, CORRECTING_FRAGMENT_SHADER);
    glUseProgram(program);
    GLuint rawSampler = glGetUniformLocation(program, "rawTexture");
    GLuint distortionSampler  = glGetUniformLocation(program, "distortionTexture");
    glUniform1i(rawSampler, 0);
    glUniform1i(distortionSampler,  1);

    //Create textures
    rawLeftTexture = createTextureReference();
    rawRightTexture = createTextureReference();
    distortionLeftTexture = createTextureReference();
    distortionRightTexture = createTextureReference();

    //Setup perspective and view matrices
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspectiveFrustrum(110, windowWidth*2/windowHeight, 1, 20);
    glMatrixMode(GL_MODELVIEW);

    return true;
}

//------------------------------------------------------------------------------
int App::execute(int argc, char* argv[]) {
	if(!init()) return 10;
	SDL_Event event;

	while(isRunning) {
		while(SDL_PollEvent(&event) != 0) { onEvent(&event); }
		update();
		render();
		SDL_Delay(1);
	}
	cleanup();
	return 0;
}

//------------------------------------------------------------------------------
void App::update() {
    Frame frame = controller.frame();
    if (frame.isValid()) {
        //Update image and distortion textures
        Image left = frame.images()[0];
        if (left.width() > 0) {
                glBindTexture(GL_TEXTURE_2D, rawLeftTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, left.width(), left.height(), 0, GL_RED, GL_UNSIGNED_BYTE, left.data());
                glBindTexture(GL_TEXTURE_2D, distortionLeftTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, left.distortionWidth()/2, left.distortionHeight(), 0, GL_RG, GL_FLOAT, left.distortion());
        }
        Image right = frame.images()[1];
        if (right.width() > 0) {
                glBindTexture(GL_TEXTURE_2D, rawRightTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, right.width(), right.height(), 0, GL_RED, GL_UNSIGNED_BYTE, right.data());
                glBindTexture(GL_TEXTURE_2D, distortionRightTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, right.distortionWidth()/2, right.distortionHeight(), 0, GL_RG, GL_FLOAT, right.distortion());
        }
    }

}

//------------------------------------------------------------------------------
void App::render() {
    SDL_RenderClear(renderer);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Move world away from camera
    glTranslatef(0.0, 0.0, -10.0);

    glPushMatrix();
    //Move sensor images away from camera and scale to maintain distance-to-size ratio of 4:1
    glScalef(80.0, 80.0, 1.0);
    glTranslatef(0.0, 0.0, -10.0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glUseProgram(program);

    if(showLeftImage){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rawLeftTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, distortionLeftTexture);
    } else {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rawRightTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, distortionRightTexture);
    }
    glBegin(GL_QUADS); // Draw A Quad for camera image
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f); // Top Left
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f); // Top Right
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f); // Bottom Right
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f); // Bottom Left
    glEnd(); // Done Drawing The Quad
    glPopMatrix();

    SDL_RenderPresent(renderer);
}

//------------------------------------------------------------------------------
void App::onEvent(SDL_Event* event) {
    if(event->type == SDL_QUIT) isRunning = false;
}

//------------------------------------------------------------------------------
void App::cleanup() {
	if(renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if(window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}

    SDL_Quit();
}

//==============================================================================
App* App::getInstance() { return &App::instance; }
