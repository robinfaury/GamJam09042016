#include "Ressources.h"
#include "Camera.h"
#include "Simulator.h"

#define MAP_SIZE 100
#define COL_GRID_SIZE 10
#define START_ANTS 10

void loadRessources();

int main(int argc, char* argv[]) {

	GLFWwindow* window;
	Simulator sim(MAP_SIZE, COL_GRID_SIZE, START_ANTS );

	if (!glfwInit()) {
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WinSizeW, WinSizeH, "Gam Jam", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glGetError();

	loadRessources();

	glViewport(0, 0, WinSizeW, WinSizeH);
	glEnable(GL_DEPTH_TEST);

	Camera cam;

	while (!glfwWindowShouldClose(window))
	{
		sim.step();

		glBindVertexArray(Res::defaultVAO);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(Res::programs["mesh"]);
		glBindTexture(GL_TEXTURE_2D, Res::textures["cube"].id_);
		glUniformMatrix4fv(glGetUniformLocation(Res::programs["mesh"], "MVP"), 1, GL_FALSE, &cam.mvp[0][0]);
		Res::mesh["cube"].draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void loadRessources() {
	glGenVertexArrays(1, &Res::defaultVAO);
	Res::loadTexture("heart", "../res/images/heart.png");
	Res::loadTexture("cube", "../res/images/cube.png");
	Res::createProgram("billboard", vBillborad, fBillborad);
	Res::createProgram("mesh", vMesh, fMesh);
	Res::loadGeometry("cube", "../res/meshes/cube.fbx");
}