#include "Game.h"

#include <iostream>

Game::Game(Window& window)
	:
	m_frustum((float)window.getWindowWidth(), (float)window.getWindowHeight(), 60.0f, 0.1f, 100.0f),
	m_entityShaderProgram("src/shaders/VertexShader.vert", "src/shaders/FragmentShader.frag"),
	m_camera(Vector3f(0.0f, 21.0f, 7.0f), Vector3f(0.0f, -3.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f)),
	m_light(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.2f, 0.2f, 0.2f), Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_rawEntity(OBJLoader::loadFile("res/models/wallCube2.obj")),
	m_rawEntity2(OBJLoader::loadFile("res/models/tree.obj")),
	m_rawTerrain(Terrain::createTerrain(10, 10)),
	m_texture1("res/textures/checker128.png", 0),
	m_texture2("res/textures/gray.png", 1),
	m_texture3("res/textures/reddish.png", 2),
	m_texture4("res/textures/black.png", 3),
	m_terrain(m_rawTerrain, m_texture1, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_player(this, m_rawEntity, m_texture3, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_target(m_rawEntity, m_texture4, Vector3f(MathCalc::generateRandomFloat(-9.75f, 9.75f), 0.0f, MathCalc::generateRandomFloat(-9.75f, 9.75f)), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 3.0f, 0.25f)),
	m_wall_1(m_rawEntity, m_texture2, Vector3f(10.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 10.0f)),
	m_wall_2(m_rawEntity, m_texture2, Vector3f(-10.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 10.0f)),
	m_wall_3(m_rawEntity, m_texture2, Vector3f(0.0f, 0.0f, 10.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(10.0f, 1.0f, 0.25f)),
	m_wall_4(m_rawEntity, m_texture2, Vector3f(0.0f, 0.0f, -10.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(10.0f, 1.0f, 0.25f)),
	m_entityList{ &m_terrain, &m_player, &m_target, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4 },
	m_updatableList{ &m_camera, &m_frustum, &m_player },
	m_collideableList{ &m_player, &m_target, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4 },
	m_rayCaster(m_camera, m_frustum),
	m_inputHandler(window, m_updatableList)
{
	m_entityShaderProgram.loadLight(m_light);
	m_player.addRayCaster(&m_rayCaster);
}

void Game::update(float deltaTime)
{
	for (IUpdatable* updatable : m_updatableList)
		updatable->update(deltaTime);

	CollisionManager::checkCollisions(m_collideableList);

	Renderer::renderEntities(m_entityShaderProgram, m_camera, m_frustum, m_entityList);
}

void Game::onSuccess()
{
	std::cout << "congratz you won" << std::endl;
}
