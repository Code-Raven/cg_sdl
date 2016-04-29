//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GameManager{
	public:
		bool Init();
		bool Cleanup();

		void Update();
};