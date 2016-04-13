#pragma once

static const char* vAnt = {
	"#version 330 core\n"
	"layout (location = 0) in vec2 in_position;\n"
	"layout (location = 1) in vec3 in_color;\n"
	"out vec3 color;\n"
	"void main() {\n"
	"	color = in_color;\n"
	"	gl_Position = vec4(in_position, 0.0, 1.0);\n"
	"}\n"
};

static const char* gAnt = {
	"#version 330 core\n"
	"layout (points) in;\n"
	"layout (triangle_strip) out;\n"
	"layout (max_vertices = 4) out;\n"
	"in vec3 color[];\n"
	"uniform float size;\n"
	"out vec3 ocolor;\n"
	"out vec2 texCoord;\n"
	"void main() {\n"
	"	ocolor = color[0];\n"
	"	vec3 pos = gl_in[0].gl_Position.xyz;\n"
	"	gl_Position = vec4(pos.x-size, pos.y-size, 0.0, 1.0);\n"
	"	texCoord = vec2(0.0, 0.0);\n"
	"	EmitVertex();\n"
	"	gl_Position = vec4(pos.x+size, pos.y-size, 0.0, 1.0);\n"
	"	texCoord = vec2(0.0, 1.0);\n"
	"	EmitVertex();\n"
	"	gl_Position = vec4(pos.x-size, pos.y+size, 0.0, 1.0);\n"
	"	texCoord = vec2(1.0, 0.0);\n"
	"	EmitVertex();\n"
	"	gl_Position = vec4(pos.x+size, pos.y+size, 0.0, 1.0);\n"
	"	texCoord = vec2(1.0, 1.0);\n"
	"	EmitVertex();\n"
	"	EndPrimitive();\n"
	"}\n"
};

static const char* fAnt = {
	"#version 330 core\n"
	"in vec2 texCoord;\n"
	"in vec3 ocolor;"
	"uniform sampler2D tex;\n"
	"out vec4 outColor;"
	"void main()\n"
	"{\n"
	"    //outColor = texture2D(tex, texCoord);\n"
	"    outColor = vec4(ocolor, 0.5-length(texCoord-vec2(0.5)));\n"
	"}\n"
};

static const char* vBillborad = {
	"#version 330 core\n"
	"const vec2 positionGen[3] = vec2[3](vec2(0.0, 0.0), vec2(2.0, 0.0), vec2(0.0, 2.0));\n"
	"out vec2 texCoord;\n"
	"void main() {\n"
	"    texCoord = vec2(positionGen[gl_VertexID].x, 1.0-positionGen[gl_VertexID].y);\n"
	"    gl_Position = vec4(2.0*positionGen[gl_VertexID]-1.0, 0.0, 1.0);\n"
	"}\n"
};

static const char* fBillborad = {
	"#version 330 core\n"
	"in vec2 texCoord;\n"
	"uniform sampler2D tex;\n"
	"out vec4 outColor;"
	"void main()\n"
	"{\n"
	"    outColor = texture2D(tex, texCoord);\n"
	"    //outColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n"
};

static const char* vMesh = {
	"#version 330 core\n"
	"layout (location = 0) in vec3 in_position;\n"
	"layout (location = 1) in vec3 in_normal;\n"
	"layout (location = 2) in vec2 in_uv;\n"
	"uniform mat4 MVP;"
	"out vec3 normal;\n"
	"out vec2 texCoord;\n"
	"void main() {\n"
	"    normal = in_normal;\n"
	"    texCoord = in_uv;\n"
	"    gl_Position = MVP * vec4(in_position, 1.0);\n"
	"}\n"
};

static const char* fMesh = {
	"#version 330 core\n"
	"in vec3 normal;\n"
	"in vec2 texCoord;\n"
	"uniform sampler2D tex;\n"
	"out vec4 outColor;"
	"void main()\n"
	"{\n"
	"    outColor = texture2D(tex, texCoord);\n"
	"}\n"
};
