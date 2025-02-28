#pragma once

#include "Common.h"

class ShaderLoader {
	
public:

	static GLuint LoadShaders(const char* vertexPath, const char* fragmentPath);

};
