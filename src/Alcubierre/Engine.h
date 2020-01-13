
class Render
{
public:
	enum Video_Modes { Fullscreen, Windowed, Borderless_Fullscreen };
	Video_Modes Mode;
};

class Engine
{
public:
	static Render _Render;
};

