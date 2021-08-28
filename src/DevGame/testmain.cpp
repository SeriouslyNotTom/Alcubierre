#include <Alcubierre/Alcubierre.h>

int main(int argc, char* argv[])
{
	Alcubierre::Accept_Arguments(argc, *argv);
	Alcubierre::Initialize_Core();

	while (true)
	{
		Alcubierre::update();
	}
}