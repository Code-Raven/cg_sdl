#include "GameManager.h"

int main( int argc, char* args[] )
{
	GameManager gameManager;

	if(gameManager.Init()){
		gameManager.Update();
	}

	//TODO: Do something with actual return value...
	(void)gameManager.Cleanup();

	return 0;
}