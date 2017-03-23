#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Utils/fileutils.h"

namespace Engine
{
	namespace Graphics
	{
		class Shader
		{
		private:
			GLuint m_shaderID;
			const char *m_vertex_shader;
			const char *m_fragement_shader;
		public:
			Shader(const char *vertexP,const char *fragementP);
			~Shader();
			void Enable() const;
			void Disable() const;

			void SetUniform1fv(const GLchar *name, float *value, int count) const;
			void SetUniform1i(const GLchar *name, GLint i) const;
			void SetUniform1iv(const GLchar *name, int *value, int count) const;
			void SetUniform2f(const GLchar *name, glm::vec2 f2f) const;
			void SetUniform4f(const GLchar *name, glm::vec4 f4f) const;
			void SetUniformMat4(const GLchar *name, glm::mat4 f4m) const;
		private:
			GLuint SetShader();
			void AddShader(GLuint shaderID, const char *ShaderText, GLenum ShaderType);
			GLint GetUniformLocation(const GLchar *name) const;
		};
	}
}