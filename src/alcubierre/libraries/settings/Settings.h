
struct Video_Settings
{
	int ScalingFactor;
	int Width;
	int Height;
};

class Settings
{
public:
	static Video_Settings LoadSettings(char* path);
};

