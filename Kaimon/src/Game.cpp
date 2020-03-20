#include "Game.h"

Game::Game(Window& window)
	:
	m_frustum((float)window.getWindowWidth(), (float)window.getWindowHeight(), 60.0f, 0.1f, 100.0f),
	m_entityShaderProgram("src/shaders/VertexShader.vert", "src/shaders/FragmentShader.frag"),
	m_camera(Vector3f(0.0f, 15.0f, 5.0f), Vector3f(0.0f, -3.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f)),
	m_light(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.2f, 0.2f, 0.2f), Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f)),

	m_playerModel("res/models/nanosuit/nanosuit.obj"),
	m_terrainModel(Terrain::createTerrain(5, 5, std::make_unique<Texture>("res/textures/checker128.png", Texture::Type::TEXTURE_DIFFUSE))),
	m_wallModel("res/models/wall/wall.obj"),
	m_targetModel("res/models/target/target.obj"),
	m_player(this, m_playerModel, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.35f, 0.35f, 0.35f)),
	m_terrain(m_terrainModel, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_wall_1(m_wallModel, Vector3f(5.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 5.0f)),
	m_wall_2(m_wallModel, Vector3f(-5.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 5.0f)),
	m_wall_3(m_wallModel, Vector3f(0.0f, 0.0f, 5.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 1.0f, 0.25f)),
	m_wall_4(m_wallModel, Vector3f(0.0f, 0.0f, -5.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 1.0f, 0.25f)),
	m_barrier(m_wallModel, Vector3f(0.0f, 0.0f, -2.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 1.0f, 0.25f)),
	m_target(m_targetModel, Vector3f(0.0f, 0.0f, -4.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 3.0f, 0.25f)),

	m_entityList { &m_player, &m_terrain, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4, &m_barrier, &m_target },
	m_updatableList { &m_camera, &m_frustum, &m_player },
	m_collideableList { &m_player, &m_wall_1, &m_wall_2, &m_wall_3, &m_wall_4, &m_barrier, &m_target },
	m_rayCaster(m_camera, m_frustum),
	m_inputHandler(window, m_updatableList)
{
	m_entityShaderProgram.loadLight(m_light);
	m_player.addRayCaster(&m_rayCaster);
}

void Game::update(float deltaTime)
{
	if (m_timer.isDeltaTimeFromLastRestart(5.0f))
		this->onFailure();

	//float angleInDegrees = m_pythonExtension.callPythonAI(m_player, m_target, m_barrier, false, false);
	//m_player.getEventHandler().addEventToList(Event(Event::MOVE_TO_ANGLE, false, angleInDegrees));
	//uncomment previous line for AI to work

	for (IUpdatable* updatable : m_updatableList)
		updatable->update(deltaTime);

	CollisionManager::checkCollisions(m_collideableList);
	Renderer::renderEntities(m_entityShaderProgram, m_camera, m_frustum, m_entityList);
}

void Game::onSuccess()
{
	//m_pythonExtension.callPythonAI(m_player, m_target, m_barrier, true, false);
	this->onRestart();
}

void Game::onFailure()
{
	//m_pythonExtension.callPythonAI(m_player, m_target, m_barrier, false, true);
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
