#include "Game.h"

Game::Game(Window& window)
	:
	m_frustum((float)window.getWindowWidth(), (float)window.getWindowHeight(), 60.0f, 0.1f, 100.0f),
	m_entityShaderProgram("src/shaders/VertexShader.vert", "src/shaders/FragmentShader.frag"),
	m_camera(Vector3f(0.0f, 21.0f, 7.0f), Vector3f(0.0f, -3.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f)),
	m_light(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.2f, 0.2f, 0.2f), Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_rawEntity(OBJLoader::loadFile("res/models/wallCube2.obj")),
	m_rawEntity2(OBJLoader::loadFile("res/models/tree.obj")),
	m_rawEntity3(Terrain::createTerrain(5, 5)),
	m_texture1("res/textures/checker128.png", 0),
	m_texture2("res/textures/gray.png", 1),
	m_texture3("res/textures/reddish.png", 2),
	m_texture4("res/textures/green.png", 3),
	m_player(this, m_rawEntity, m_texture3, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_terrain(m_rawEntity3, m_texture1, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_target(m_rawEntity, m_texture4, Vector3f(0.0f, 0.0f, -4.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 3.0f, 0.25f)),
	m_wall_1(m_rawEntity, m_texture2, Vector3f(5.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 5.0f)),
	m_wall_2(m_rawEntity, m_texture2, Vector3f(-5.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 5.0f)),
	m_wall_3(m_rawEntity, m_texture2, Vector3f(0.0f, 0.0f, 5.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 1.0f, 0.25f)),
	m_wall_4(m_rawEntity, m_texture2, Vector3f(0.0f, 0.0f, -5.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 1.0f, 0.25f)),
	m_barrier(m_rawEntity, m_texture2, Vector3f(0.0f, 0.0f, -2.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 1.0f, 0.25f)),
	m_entityList{ &m_terrain, &m_player, &m_target, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4, &m_barrier },
	m_updatableList{ &m_camera, &m_frustum, &m_player },
	m_collideableList{  &m_target, &m_player, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4, &m_barrier },
	m_rayCaster(m_camera, m_frustum),
	m_inputHandler(window, m_updatableList)
{
	m_entityShaderProgram.loadLight(m_light);
	m_player.addRayCaster(&m_rayCaster);
}

void Game::update(float deltaTime)
{
	if (m_timer.isDeltaTimeFromLastRestart(10.0f))
		this->onFailure();

	float angleInDegrees = m_pythonExtension.callPythonAI(m_player, m_target, m_barrier, false, false);
	m_player.getEventHandler().addEventToList(Event(Event::MOVE_TO_ANGLE, false, angleInDegrees));
	//uncomment previous line for AI to work

	for (IUpdatable* updatable : m_updatableList)
		updatable->update(deltaTime);

	CollisionManager::checkCollisions(m_collideableList);
	Renderer::renderEntities(m_entityShaderProgram, m_camera, m_frustum, m_entityList);
}

void Game::onSuccess()
{
	m_pythonExtension.callPythonAI(m_player, m_target, m_barrier, true, false);
	this->onRestart();
}

void Game::onFailure()
{
	m_pythonExtension.callPythonAI(m_player, m_target, m_barrier, false, true);
	this->onRestart();
}


void Game::onRestart()
{
	std::vector<ICollideable*> collideableList = { &m_player, &m_target, &m_barrier };
	do
	{
		m_player.restartPosition(TERRAIN_MIN_VEC, TERRAIN_MAX_VEC);
		m_target.restartPosition(TERRAIN_MIN_VEC, TERRAIN_MAX_VEC);
		m_barrier.restartPosition(TERRAIN_MIN_VEC, TERRAIN_MAX_VEC);
	} 
	while (CollisionManager::checkCollisionsBool(collideableList));

	m_timer.setLastRestartTimeToCurrentTime();
}
