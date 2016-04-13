#pragma once

#define WinSizeW 640
#define WinSizeH 480

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 mvp;

	Camera() : pos(glm::vec3(0.f, 0.f, 3.f)), target(glm::vec3(0.f, 0.f, 0.f)) {
		dir = glm::normalize(pos - target);
		right = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), dir));
		up = glm::normalize(glm::cross(dir, right));

		view = glm::lookAt(pos, target, up);
		proj = glm::perspective(45.f, (GLfloat)WinSizeW/(GLfloat)WinSizeH, 0.01f, 1000.f);
		mvp = proj*view;
	}
};
