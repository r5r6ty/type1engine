#include "shader.h"
#include "../Utils/fileutils.h"

namespace Engine
{
	namespace Graphics
	{
		Shader::Shader(const char *vertexP, const char *fragementP)
		{
			m_vertex_shader = vertexP;
			m_fragement_shader = fragementP;
			m_shaderID = SetShader();
		}
		Shader::~Shader()
		{
			glDeleteShader(m_shaderID);
		}

		GLuint Shader::SetShader()
		{
			std::string vs = ReadFile(m_vertex_shader);
			std::string fs = ReadFile(m_fragement_shader);
			GLuint SP = glCreateProgram();

			AddShader(SP, vs.c_str(), GL_VERTEX_SHADER);
			AddShader(SP, fs.c_str(), GL_FRAGMENT_SHADER);
			glLinkProgram(SP);
			//GLint success;
			//glGetShaderiv(SP, GL_LINK_STATUS, &success);
			//if (!success)
			//{
			//	GLchar ErrorLog[1024] = { 0 };
			//	glGetShaderInfoLog(SP, sizeof(ErrorLog), NULL, ErrorLog);
			//	fprintf(stderr, "Error linking shader type: %s\n", ErrorLog);
			//	exit(1);
			//}
			glValidateProgram(SP);
			//glGetShaderiv(SP, GL_VALIDATE_STATUS, &success);
			//if (!success)
			//{
			//	GLchar ErrorLog[1024] = { 0 };
			//	glGetShaderInfoLog(SP, sizeof(ErrorLog), NULL, ErrorLog);
			//	fprintf(stderr, "Error validating shader type: %s\n", ErrorLog);
			//	exit(1);
			//}
			return SP;
		}

		void Shader::AddShader(GLuint shaderID, const char *ShaderText, GLenum ShaderType)
		{
			GLuint ShaderObj = glCreateShader(ShaderType);
			if (ShaderObj == 0)
			{
				exit(1);
			}

			glShaderSource(ShaderObj, 1, &ShaderText, NULL);
			glCompileShader(ShaderObj);
			GLint success;
			glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				GLchar InfoLog[1024] = { 0 };
				glGetShaderInfoLog(ShaderObj, sizeof(InfoLog), NULL, InfoLog);
				fprintf(stderr, "Error compiling shader type: %d -> %s\n", ShaderType, InfoLog);
				exit(1);
			}
			glAttachShader(shaderID, ShaderObj);
			glDeleteShader(ShaderObj);
		}

		void Shader::Enable() const
		{
			glUseProgram(m_shaderID);
		}
		void Shader::Disable() const
		{
			glUseProgram(0);
		}

		GLint Shader::GetUniformLocation(const GLchar *name) const
		{
			return glGetUniformLocation(m_shaderID, name);
		}

		void Shader::SetUniform1i(const GLchar *name, GLint i) const
		{
			glUniform1i(GetUniformLocation(name), i);
		}

		void Shader::SetUniform2f(const GLchar* name, glm::vec2 f2f) const
		{
			glUniform2f(GetUniformLocation(name), f2f.x, f2f.y);
		}

		void Shader::SetUniform4f(const GLchar *name, glm::vec4 f4f) const
		{
			glUniform4f(GetUniformLocation(name), f4f.x, f4f.y, f4f.z, f4f.w);
		}

		void Shader::SetUniformMat4(const GLchar *name, glm::mat4 f4m) const
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(f4m));
		}
	}
}