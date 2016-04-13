#include <time.h>

#include "Ressources.h"
#include "Camera.h"

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

struct t {
	glm::vec2 pos;
	glm::vec3 color;
	t(glm::vec2 p, glm::vec3 i) {
		pos = p;
		color = i;
	}
};

int main(int argc, char* argv[]) {

	srand(time(NULL));

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
	glfwSetKeyCallback(window, key_callback);

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


	std::vector<t> position;
	for (int i = 0; i < 10000; ++i) {
		position.push_back(t(glm::vec2((rand()%100)/50.f - 1.f, (rand() % 100) / 50.f - 1.f), glm::vec3(0.2f*(rand()%5))));
	}

	GLuint antVAO, antVBO;
	glGenVertexArrays(1, &antVAO);
	glGenBuffers(1, &antVBO);
	glBindVertexArray(antVAO);
	glBindBuffer(GL_ARRAY_BUFFER, antVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t) * position.size(), &position[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	lastTime = glfwGetTime();
	nbFrames = 0;
	while (!glfwWindowShouldClose(window))
	{
		FPS();
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (std::vector<t>::iterator it = position.begin(); it != position.end(); it++) {
			(*it).pos.x += ((rand() % 100) / 50.f - 1.f) / 1000.f;
			(*it).pos.y += ((rand() % 100) / 50.f - 1.f) / 1000.f;
		}

		glUseProgram(Res::programs["ant"]);
		glBindVertexArray(antVAO);
		glBindBuffer(GL_ARRAY_BUFFER, antVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(t) * position.size(), &position[0]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(t), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t), (GLvoid*)(sizeof(glm::vec2)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_POINTS, 0, position.size());
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
	Res::createProgram("ant", vant, gant, fant);
	Res::loadGeometry("cube", "../res/meshes/cube.fbx");
}