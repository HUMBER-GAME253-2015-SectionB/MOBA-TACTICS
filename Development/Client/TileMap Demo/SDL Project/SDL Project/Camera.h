#include <SDL.h>

class Camera
{
public:
	Camera();

private:
	int worldPosX;
	int worldPosY;
	int horizontalSpeed;
	int verticalSpeed;
	int minZoom;
	int maxZoom;
	int minPosX;
	int maxPosX;
	int minPosY;
	int maxPosX;
};