//
//  util.h
//  VRHello
//
//  Created by Joe Ward on 10/23/14.
//  Copyright (c) 2014 Leap Motion, Inc. All rights reserved.
//

#ifndef __VRHello__util__
#define __VRHello__util__
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

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cerrno>
#include <SDL.h>
#include "LeapMath.h"

GLuint createProgram(std::string vertex, std::string fragment);
GLuint createTextureReference();
void printProgramInfoLog(GLuint obj);
void printShaderInfoLog(GLuint obj);
std::string getFileContents(std::string filename);
GLfloat* createPerspectiveMatrix(float fov, float aspect, float nearPlane, float farPlane);
void setPerspectiveFrustrum(GLdouble fovY, GLdouble aspect, GLdouble nearPlane, GLdouble farPlane);

#endif /* defined(__VRHello__util__) */
