#pragma once
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

class Game
{
public:
	Game(Window& window);
	void update(float deltaTime);
	
	void onSuccess(Player& player, Target& target);
	void onRestart(Player& player, Target& target);
private:
	ViewFrustum m_frustum;
	EntityShaderProgram m_entityShaderProgram;
	Camera m_camera;
	Light m_light;

	RawEntity m_rawEntity, m_rawEntity2, m_rawTerrain;
	Texture m_texture1, m_texture2, m_texture3, m_texture4;

	Entity m_terrain;
	Player m_player;
	Obstacle m_wall_1, m_wall_2, m_wall_3, m_wall_4;
	Target m_target;

	std::vector<Entity*> m_entityList;
	std::vector<IUpdatable*> m_updatableList;
	std::vector<ICollideable*> m_collideableList;

	//std::vector<Obstacle*> m_obstacleList;

	RayCaster m_rayCaster;
	InputHandler m_inputHandler;
	PythonExtension m_pythonExtension;
	Timer m_timer;
};