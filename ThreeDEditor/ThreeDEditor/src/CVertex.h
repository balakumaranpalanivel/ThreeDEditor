#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define LENGTH_POSITION				3
#define LENGTH_NORMALS				3
#define LENGTH_TEXTURE_COORDINATES	2

struct CVertex
{
	glm::vec3 v3Position;
	glm::vec3 v3Normal;
	glm::vec2 v2TexCoords;
};