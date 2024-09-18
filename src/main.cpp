#include <gl/glew.h>
#include <gl/freeglut.h>

#include <iostream>
#include <stdio.h>
#include <shaderfuncs.hpp>
#include <vector.hpp>
#include <Math/matrix.hpp>
#include <Math/point.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#define NUMVERTS 6

static void RenderSceneCB();
static void CreateVertexBuffer();
int main(int, char**);

GLuint VBO[1];
Point vertices[NUMVERTS];
extern GLint gScaleLocation;
extern GLint transformationLocation;

// Function that actually draws the screen, called repeatedly in the main loop during drawing phases
static void RenderSceneCB() {
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	// Update screen here
	static GLfloat gScale = 0.0f;
	static GLfloat delta = -0.001f;
	static GLfloat rads = 0.0f;
	const GLfloat rDelta = 0.001f;

	if (rads >= 60 * M_PI) rads = 0;

	Matrix4f transformation = CreateRotationMatrix(rads/5, rads/12, 0);

	glUniformMatrix4fv(transformationLocation, 1, GL_TRUE, &(transformation.m[0][0]));
	glUniform1f(gScaleLocation, gScale);

	if (gScale <= -1.0f || gScale >= 1.0f) delta *= -1;

	gScale += delta;
	rads += rDelta;
	// Bind the gl array buffer to the global VBO object
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	// Enable changing of position (attribute 0)
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// How to interpret arrays, where to start, how many to process
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glutSwapBuffers();

	glutPostRedisplay();
}







static void CreateVertexBuffer() {
	/*
	  Culling means that any triangle assembled
	  in a clockwise order will not be rendered
	  as it is facing the 'back' side, meaning
	  it is no longer visible
	*/
	glEnable(GL_CULL_FACE);

	/*
	  Changes which vertex order (CW, CCW) is
	  considered 'front facing'
	*/
	glFrontFace(GL_CW);

	/*
	  Tells OGL which face to cull, front or back
	*/
	glCullFace(GL_FRONT);


	
	vertices[0] = { -0.66f, -0.66f, 0.0f }; //left
	vertices[1] = { 0.165f, -0.66f, 0.0f };//right
	vertices[2] = { -0.165f, 0.66f, 0.0f }; //top
	vertices[3] = { -0.165f, 0.66f, 0.0f }; //left
	vertices[4] = { 0.165f, -0.66f, 0.0f }; //bottom
	vertices[5] = {  0.66f,  0.66f, 0.0f };  //right

	// Number of handles, pointer to GLuint array for x handles
	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int size[2] = { 720, 480 };
	glutInitWindowSize(size[0], size[1]);

	int pos[2] = { 0, 0 };
	glutInitWindowPosition(pos[0], pos[1]);

	int window = glutCreateWindow("Point Example");
	//std::cout << "Window ID: " << window << std::endl;

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error '%s'\n", glewGetErrorString(res));
		return 1;
	}

	/*
	  Add vertices to vertex array to be drawn
	*/
	CreateVertexBuffer();

	CompileShaders();

	/*
	 Attaches RenderSceneCB (callback) as the function to call when the
	 display is set to be updated. This function must handle all the
	 necessary steps to actually render said display
	*/
	glutDisplayFunc(RenderSceneCB);


	/*
	 Needs to be the last function call of main
	 as glutMainLoop never returns
	*/
	glutMainLoop();

	return 0;
}