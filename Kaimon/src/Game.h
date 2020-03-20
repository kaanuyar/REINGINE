#pragma once
#include <vector>
#include "EntityShaderProgram.h"
#include "Entity.h"
#include "Renderer.h"
#include "Window.h"
#include "Texture.h"
#include "Vector3f.h"
#include "Terrain.h"
#include "Camera.h"
#include "InputHandler.h"
#include "InteractableEntity.h"
#include "Light.h"
#include "ViewFrustum.h"
#include "IUpdatable.h"
#include "RayCaster.h"
#include "CollideableEntity.h"
#include "CollisionManager.h"
#include "Obstacle.h"
#include "Player.h"
#include "PythonExtension.h"
#include "Target.h"
#include "Timer.h"
#include "Model.h"
#include "Mesh.h"

class Game
{
public:
	Game(Window& window);
	void update(float deltaTime);
	
	void onSuccess();
	void onFailure();
	void onRestart();
private:
	ViewFrustum m_frustum;
	EntityShaderProgram m_entityShaderProgram;
	Camera m_camera;
	Light m_light;

	Model m_playerModel, m_terrainModel, m_wallModel, m_targetModel;
	Player m_player;
	Entity m_terrain;
	Target m_target;
	Obstacle m_wall_1, m_wall_2, m_wall_3, m_wall_4, m_barrier;

	std::vector<Entity*> m_entityList;
	std::vector<IUpdatable*> m_updatableList;
	std::vector<ICollideable*> m_collideableList;

	RayCaster m_rayCaster;
	InputHandler m_inputHandler;
	//PythonExtension m_pythonExtension;
	Timer m_timer;

	// Constants
	const Vector3f TERRAIN_MAX_VEC { -5.0f, 0.0f, -5.0f };
	const Vector3f TERRAIN_MIN_VEC { 5.0f, 0.0f, 5.0f };
};