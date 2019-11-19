#include <Alcubierre/Libraries/Render/RenderManager.h>

#include <Alcubierre/Libraries/Render/Shader.h>

void RenderManager::Add(Renderable* obj)
{
	RenderOBJs_.push_back(obj);
}

void RenderManager::DoRenders_()
{
	for (Renderable*& OBJ : RenderOBJs_) {
		OBJ->Render();
	}
}

void RenderManager::Init()
{
	RenderManager::shaders = std::unordered_map<std::string, GLuint>();
	for (Renderable*& OBJ : RenderOBJs_)
	{
		OBJ->AcceptWindow(myWindow);
		OBJ->Init();
	}
}

void RenderManager::Render_HOOK()
{
	this->DoRenders_();
}

void RenderManager::AddShader(std::string name, char* vertex_path, char* fragment_path)
{
	GLuint new_shader = Shader_Loader::CompileShader(vertex_path, fragment_path);
	this->shaders.insert({ name,new_shader });
}
