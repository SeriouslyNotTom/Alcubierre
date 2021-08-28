#include <gl/GL.h>
#include <vector>
#include <map>

enum ALCB_Texture_state_
{
	EMPTY,
	UNLOADED,
	LOADED_RAW_BYTES,
	LOADED_OPENGL,
	FREED
};

struct ALCB_Texture
{
	
	ALCB_Texture_state_ load_state;
	GLuint gl_texture_id;
	char* raw_bytes;
	size_t raw_bytes_size;
	const char* system_image_path;
};

struct ALCB_SceneRenderPointer_list
{
	
};

class Renderer
{
private:
	std::vector<ALCB_Texture> texture_list;

public:

};