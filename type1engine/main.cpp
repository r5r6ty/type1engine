#include "System/Graphics/window.h"
#include "System/Graphics/shader.h"
#include "System/Utils/timer.h"
#include "System/Graphics/Buffers/vertexarray.h"
#include "System/Graphics/Buffers/indexbuffer.h"
#include "System/Graphics/simple2Drenderer.h"
#include "System/Graphics/batchrenderer2D.h"
#include "System/Graphics/static_sprite.h"
#include "System/Graphics/sprite.h"
#include "System/Graphics/Layers/tilelayer.h"
#include "System/Graphics/Layers/groups.h"
#include "System/Graphics/texture.h"
#include "System/Graphics/label.h"
#include "System/Graphics/fontmanager.h"

#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 1

#if 1

int main()
{
	srand((unsigned int)time(NULL));

	using namespace Engine;
	using namespace Graphics;	

	Window window("Type 1 Engine", 960, 540);

	Shader *shader1 = new Shader("System/Shaders/shader.vert", "System/Shaders/shader.frag");
	//Shader *shader2 = new Shader("System/Shaders/shader.vert", "System/Shaders/shader.frag");
	shader1->Enable();

	//Shader.SetUniformMat4("vm_matrix", glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	//Shader.SetUniformMat4("pr_matrix", glm::perspective(90.0f, (GLfloat)(window.GetWindowWidth() / window.GetWindowHeight()), 0.1f, 100.0f));
	shader1->SetUniformMat4("pr_matrix", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	shader1->SetUniformMat4("ml_matrix", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)));
	shader1->SetUniform2f("light_pos", glm::vec2(0.0f, 0.0f));

	//shader2->Enable();
	//shader2->SetUniformMat4("pr_matrix", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	//shader2->SetUniformMat4("ml_matrix", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	//shader2->SetUniform2f("light_pos", glm::vec2(0.0f, 0.0f));

	TileLayer layer(shader1);
	//TileLayer layer2(shader2);

	Texture *textures[] =
	{
	new Texture("111.bmp"),
	new Texture("112.bmp"),
	new Texture("113.bmp"),
	new Texture("001.png"),
	new Texture("large.bmp")
	};

#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 1.0f)
	{
		for (float x = -16.0f; x < 16.0f; x += 1.0f)
		{
			//if (rand() % 2 == 0)
			//{
				layer.Add(new Sprite(glm::vec2(x, y), glm::vec2(0.8f, 0.8f), Color_FloatToInt(glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f))));
			//}
			//else
			//{
			//	layer.Add(new Sprite(glm::vec2(x, y), glm::vec2(0.8f, 0.8f), textures[rand() % 4]));
			//}

			//Label *fps = new Label("fps", glm::vec2(x, y), glm::vec2(1, 1), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			//layer.Add(fps);

		}
	}
#else

	Group *group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), (float)M_PI / 180 * 45.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	group->Add(new Sprite(glm::vec2(0.0f, 0.0f), glm::vec2(6.0f, 3.0f), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));


	Group *button = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f)) * glm::rotate(glm::mat4(1.0f), (float)M_PI / 180 * 45.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	button->Add(new Sprite(glm::vec2(0.0f, 0.0f), glm::vec2(5.0f, 2.0f), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));
	button->Add(new Sprite(glm::vec2(0.5f, 0.5f), glm::vec2(3.0f, 1.0f), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));
	group->Add(button);

	layer.Add(group);

#endif

	//layer2.Add(new Sprite(glm::vec2(0.0f, 0.0f), glm::vec2(4.0f, 4.0f), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));


	//Label *fps = new Label(localeToUTF8("�򱬺��繷ͷ��"), glm::vec2(-5, 0), glm::vec2(1, 1), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f));	
	
	FontManager::Add(new Font("΢���ź�", "΢���ź�.ttf", 32));
	FontManager::Add(new Font("Arial", "Arial.ttf", 16));
	
	Group *group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-16.0f, 8.0f, 0.0f)));
	Label *fps = new Label("FPS: 0", glm::vec2(0, 0), glm::vec2(1, 1), FontManager::GetFont("΢���ź�", 32), Color_FloatToInt(glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f)));

	group->Add(fps);

	layer.Add(group);


	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
	};

	shader1->Enable();
	shader1->SetUniform1iv("textures", texIDs, 32);

	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.IsClosed())
	{
		window.Clear();

		if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			window.Close();
		}

		if (window.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		{
			double mx, my;
			window.GetMousePosition(&mx, &my);

			shader1->Enable();
			shader1->SetUniform2f("light_pos", glm::vec2((float)(mx * 32.0f / window.GetWindowWidth()) - 16.0f, (float)(9.0f - my * 18.0f / (float)window.GetWindowHeight())));
			//shader2->Enable();
			//shader2->SetUniform2f("light_pos", glm::vec2((float)(mx * 32.0f / window.GetWindowWidth()) - 16.0f, (float)(9.0f - my * 18.0f / (float)window.GetWindowHeight())));

		}

		const std::vector<Renderable2D*> &rs = layer.GetRenderables();
		for (unsigned int i = 0; i < rs.size(); i++)
		{
			rs[i]->SetColor(Color_FloatToInt(glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f)));
		}

		layer.render();
		//layer2.render();

		//if (window.IsKeyTyped(GLFW_KEY_S))
		//{
		//	std::cout << "S";
		//}

		//if (window.IsMouseButtonClicked(GLFW_MOUSE_BUTTON_1))
		//{
		//	std::cout << "1";
		//}

		window.Update();
		frames++;
		if (time.Elapsed() - timer > 1.0f)
		{
			timer += 1.0f;

			char str[100];
			sprintf_s(str, "FPS: %i Sprites: %i", frames, layer.GetLayerSize());
			fps->m_Text = str;

			printf("FPS: %i Sprites: %i\n", frames, layer.GetLayerSize());
			frames = 0;
		}

		group->m_transformationmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-16.0f, 8.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), time.Elapsed(), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		delete textures[i];
	}
	

	return 0;
}

#endif 