#include <Alcubierre/Libraries/Render/RenderManager.h>

#include <Alcubierre/Libraries/Render/Shader.h>

void Render_Manager::Add(Renderable* obj)
{
	RenderOBJs_.push_back(obj);
}

void Render_Manager::DoRenders_()
{
	for (Renderable*& OBJ : RenderOBJs_) {
		OBJ->Render();
	}
}

void Render_Manager::Init()
{
	Render_Manager::shaders = std::unordered_map<std::string, GLuint>();
	for (Renderable*& OBJ : RenderOBJs_)
	{
		OBJ->AcceptWindow(myWindow);
		OBJ->Init();
	}
}

void Render_Manager::Render_HOOK()
{
	this->DoRenders_();
}

void Render_Manager::AddShader(std::string name, char* vertex_path, char* fragment_path)
{
	GLuint new_shader = Shader_Loader::CompileShader(vertex_path, fragment_path);
	this->shaders.insert({ name,new_shader });
}
