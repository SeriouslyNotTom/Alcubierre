
struct Video_Settings
{
	double ScalingFactor;
	int Width;
	int Height;
};

class Settings
{
public:
	static Video_Settings LoadSettings(char* path);
};

