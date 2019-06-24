#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cppc/render/shader_loader.cpp>
#include <stdlib.h>

using namespace std;
using namespace Shader;

const std::string asset_path = "assets/";

namespace Primitives {

	GLuint VAO, VBO;
	GLuint TexQuadShader;
	

	class RenderPrimitive {
	public:
		static void Init()
		{
			fprintf(stdout, "Initializing Primitive util library \n");
			TexQuadShader = LoadAndCompileShader(std::string(asset_path + "text.vshad").c_str(), std::string(asset_path + "text.fshad").c_str());
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		static void Polygon(glm::vec2 Position)
		{
		}
		static void TexturedQuad(int X, int Y, int W, int H, GLuint TextureID)
		{
			//glUseProgram(TexQuadShader);
			glUniform3f(glGetUniformLocation(TexQuadShader, "textColor"), 1, 1, 1);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VAO);
			GLfloat xpos = X;
			GLfloat ypos = Y;
			GLfloat w = W;
			GLfloat h = H;
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			
			glBindTexture(GL_TEXTURE_2D, TextureID);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);
		}
	};
};