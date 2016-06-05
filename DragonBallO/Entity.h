#include <string>

class Entity{

	friend class SDLInit;

	protected:
		std::string name;
		int mHealth;
		int xPos;
		int yPos;
};