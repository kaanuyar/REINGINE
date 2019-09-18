#include <vector>
#include "EntityShaderProgram.h"
#include "Entity.h"
#include "RawEntity.h"
#include "Renderer.h"
#include "Window.h"
#include "Texture.h"
#include "Vector3f.h"
#include "OBJLoader.h"
#include "Terrain.h"
#include "Camera.h"
#include "InputHandler.h"
#include "InteractableEntity.h"
#include "Light.h"
#include "Timer.h"
#include "ViewFrustum.h"
#include "IUpdatable.h"
#include "RayCaster.h"
#include "CollideableEntity.h"
#include "CollisionManager.h"

int main()
{
	Window window(800, 450, std::string("Kaimon"));
	ViewFrustum frustum(800.0f, 450.0f, 60.0f, 0.1f, 100.0f);
	EntityShaderProgram entityShaderProgram("src/shaders/VertexShader.vert", "src/shaders/FragmentShader.frag");
	Camera camera(Vector3f(0.0f, 9.0f, 3.0f), Vector3f(0.0f, -3.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f));
	Light light(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.2f, 0.2f, 0.2f), Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f));
	entityShaderProgram.loadLight(light);

	RawEntity rawEntity = OBJLoader::loadFile("res/models/wallCube2.obj");
	RawEntity rawTerrain = Terrain::createTerrain(20, 20);
	Texture texture1("res/textures/checker128.png", 0);
	Texture texture2("res/textures/wall.jpg", 1);

	Entity terrain(rawTerrain, texture1, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	InteractableEntity entity(rawEntity, texture2, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	CollideableEntity staticEntity(rawEntity, texture2, Vector3f(0.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), 1.0f);

	std::vector<Entity*> entityList = { &terrain, &entity, &staticEntity };
	std::vector<IUpdatable*> updatableList = { &camera, &frustum, &entity };
	std::vector<ICollideable*> collideableList = { &entity, &staticEntity };

	RayCaster rayCaster(camera, frustum);
	entity.addRayCaster(&rayCaster);

	InputHandler inputHandler(window, updatableList);
	Timer timer;

	while (!window.isWindowShouldClose())
	{
		float deltaTime = timer.getDeltaTime();

		for (IUpdatable* updatable : updatableList)
			updatable->update(deltaTime);

		CollisionManager::checkCollisions(collideableList);

		Renderer::renderEntities(entityShaderProgram, camera, frustum, entityList);
		window.update();
	}

	return 0;
}


