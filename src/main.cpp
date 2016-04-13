#include <time.h>

#include "Ressources.h"
#include "Camera.h"
#include "Simulator.h"

#define MAP_SIZE 100
#define COL_GRID_SIZE 10
#define START_ANTS 1000

void loadRessources();

double lastTime;
int nbFrames;
void FPS() {
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) {
		printf("%d FPS\n", nbFrames);
		nbFrames = 0;
		lastTime += 1.0;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	GLFWwindow* window;
	Simulator sim(MAP_SIZE, COL_GRID_SIZE, START_ANTS );
	std::vector<AntAttribute>& antAttribute = sim.getAntAttributes();

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
	glfwSetKeyCallback(window, key_callback);
	

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glGetError();

	loadRessources();

	glViewport(0, 0, WinSizeW, WinSizeH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera cam;

	GLuint antVAO, antVBO;
	glGenVertexArrays(1, &antVAO);
	glGenBuffers(1, &antVBO);
	glBindVertexArray(antVAO);
	glBindBuffer(GL_ARRAY_BUFFER, antVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(AntAttribute) * antAttribute.size(), &antAttribute[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	lastTime = glfwGetTime();
	nbFrames = 0;
	while (!glfwWindowShouldClose(window))
	{
		FPS();
		sim.step();

		glBindVertexArray(Res::defaultVAO);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(Res::programs["ant"]);
		glBindVertexArray(antVAO);
		glBindBuffer(GL_ARRAY_BUFFER, antVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(AntAttribute) * sim.getNbAnts(), &antAttribute[0]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(AntAttribute), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AntAttribute), (GLvoid*)(sizeof(glm::vec2)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glUniform1f(glGetUniformLocation(Res::programs["ant"], "size"), 0.004);
		glDrawArrays(GL_POINTS, 0, sim.getNbAnts());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
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
	Res::createProgram("ant", vAnt, gAnt, fAnt);
	Res::loadGeometry("cube", "../res/meshes/cube.fbx");
}