#include "Ressources.h"

#define WinSizeW 640
#define WinSizeH 480

void loadRessources();

int main(int argc, char* argv[]) {

	GLFWwindow* window;

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glViewport(0, 0, WinSizeW, WinSizeH);
	glBindVertexArray(Res::defaultVAO);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(Res::programs["billborad"]);
		glBindTexture(GL_TEXTURE_2D, Res::textures["heart"].id_);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);

	glfwTerminate();

	return 0;
}

void loadRessources() {
	glGenVertexArrays(1, &Res::defaultVAO);
	Res::loadTexture("heart", "../res/images/heart.png");
	Res::createProgram("billboard", vBillborad, fBillborad);
}