#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace Engine
{
	namespace Graphics
	{
#define KEY_MAX 1024
#define MOUSE_MAX 32

		class Window
		{
		private:
			const char *m_title;
			unsigned int m_width,m_height;
			GLFWwindow *m_window;
			bool m_keys[KEY_MAX];
			bool m_KeysState[KEY_MAX];
			bool m_KeysTyped[KEY_MAX];
			bool m_mouse[MOUSE_MAX];
			bool m_MouseState[MOUSE_MAX];
			bool m_MouseClicked[MOUSE_MAX];
			double m_mouseposX, m_mouseposY;
		public:
			Window(const char *t, unsigned int w, unsigned int h);
			~Window();
			void Clear() const;
			void Update();
			int IsClosed() const;
			void Close() const;
			bool IsKeyPressed(unsigned int key) const;
			bool IsKeyTyped(unsigned int key) const;
			bool IsMouseButtonPressed(unsigned int button) const;
			bool IsMouseButtonClicked(unsigned int button) const;
			void GetMousePosition(double *x, double *y) const;
			inline unsigned int GetWindowWidth() const { return m_width; };
			inline unsigned int GetWindowHeight() const { return m_height; };
		private:
			bool Init();
			friend static void window_size_callback(GLFWwindow *window, int width, int height);
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}