#pragma once

#include <stdlib.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include <glad/glad.h>
#include <Alcubierre/Libraries/Render/Window/WindowManager.h>

class Renderable
{
public:
	virtual void AcceptWindow(Window* window) {};
	virtual void Init() {};
	virtual void PreRender() {};
	virtual void Render() {};
	virtual void PostRender() {};
};

class Render_Manager
{
public:
	void Add(Renderable* obj);
	void Render_HOOK();
	void Init();
	Window* myWindow;
	std::unordered_map<std::string, GLuint> shaders;
	void AddShader(std::string name, std::string vertex_path, std::string fragment_path);

private:
	std::vector<Renderable*> RenderOBJs_;
	void DoRenders_();
};