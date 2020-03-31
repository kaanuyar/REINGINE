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
	Game(Window& window, bool pythonExtensionFlag);
	void update(float deltaTime);
	
	void onSuccess();
	void onFailure();
	void onRestart();
private:
	ViewFrustum m_frustum;
	Renderer m_renderer;
	Camera m_camera;
	Light m_light;
	RayCaster m_rayCaster;

	Model m_playerModel, m_wallModel, m_targetModel, m_terrainModel;
	Entity m_terrain;
	Player m_player;
	Target m_target;
	Obstacle m_border1, m_border2, m_border3, m_border4, m_barrier;

	std::vector<Entity*> m_entityList;
	std::vector<IUpdatable*> m_updatableList;

	InputHandler m_inputHandler;
	std::unique_ptr<PythonExtension> m_pythonExtension;
	Timer m_timer;

	bool m_pythonExtensionFlag;
};