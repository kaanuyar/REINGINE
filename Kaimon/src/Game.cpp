#include "Game.h"

Game::Game(Window& window, bool pythonExtensionFlag)
	:
	m_pythonExtensionFlag(pythonExtensionFlag),
	m_frustum((float)window.getWindowWidth(), (float)window.getWindowHeight(), 60.0f, 0.1f, 100.0f),
	m_camera(Vector3f(0.0f, 15.0f, 5.0f), Vector3f(0.0f, -3.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f)),
	m_light(Vector3f(0.0f, 10.0f, 0.0f), Vector3f(0.2f, 0.2f, 0.2f), Vector3f(1.0f, 1.0f, 1.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_rayCaster(m_camera, m_frustum),

	m_terrainModel(Terrain::createTerrain(5, 5, std::make_unique<Texture>("res/textures/checker128.png", Texture::Type::TEXTURE_DIFFUSE))),
	m_playerModel("res/models/nanosuit/nanosuit.obj"),
	m_wallModel("res/models/wall/wall.obj"),
	m_targetModel("res/models/target/target.obj"),
	m_player(this, m_playerModel, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.35f, 0.35f, 0.35f), &m_rayCaster),
	m_terrain(m_terrainModel, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)),
	m_border1(m_wallModel, Vector3f(5.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 5.0f)),
	m_border2(m_wallModel, Vector3f(-5.25f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 1.0f, 5.0f)),
	m_border3(m_wallModel, Vector3f(0.0f, 0.0f, 5.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 1.0f, 0.25f)),
	m_border4(m_wallModel, Vector3f(0.0f, 0.0f, -5.25f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(5.0f, 1.0f, 0.25f)),
	m_barrier(m_wallModel, Vector3f(0.0f, 0.0f, -2.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(2.0f, 1.0f, 0.25f)),
	m_target(m_targetModel, Vector3f(0.0f, 0.0f, -4.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.25f, 3.0f, 0.25f)),

	m_entityList { &m_player, &m_terrain, &m_border1, &m_border2, &m_border3, &m_border4, &m_barrier, &m_target },
	m_updatableList { &m_camera, &m_frustum, &m_player },
	m_inputHandler(window, m_updatableList)
{
	if (m_pythonExtensionFlag)
		m_pythonExtension = std::make_unique<PythonExtension>();
}

void Game::update(float deltaTime)
{
	if (m_timer.isDeltaTimeFromLastRestart(5.0f))
		this->onFailure();

	if (m_pythonExtensionFlag)
	{
		float angleInDegrees = m_pythonExtension->callPythonAI(m_player, m_target, m_barrier, false, false);
		m_player.getEventHandler().addEventToList(Event(Event::MOVE_TO_ANGLE, false, angleInDegrees));
	}

	for (IUpdatable* updatable : m_updatableList)
		updatable->update(deltaTime);

	// do it properly with virtual functions not dynamic_cast XD good luck (SAME WITH RENDERER) (AND MAKE TEXTURELOADER)
	CollisionManager::checkEntityCollisions(m_entityList);
	m_renderer.renderEntities(m_camera, m_frustum, m_light, m_entityList);
}

void Game::onSuccess()
{
	if (m_pythonExtensionFlag)
		m_pythonExtension->callPythonAI(m_player, m_target, m_barrier, true, false);

	this->onRestart();
}

void Game::onFailure()
{
	if (m_pythonExtensionFlag)
		m_pythonExtension->callPythonAI(m_player, m_target, m_barrier, false, true);

	this->onRestart();
}

void Game::onRestart()
{
	std::vector<ICollideable*> collideableList = { &m_player, &m_target, &m_barrier };
	do
	{
		m_player.restartPosition(Terrain::MIN_BOUNDARY_VEC, Terrain::MAX_BOUNDARY_VEC);
		m_target.restartPosition(Terrain::MIN_BOUNDARY_VEC, Terrain::MAX_BOUNDARY_VEC);
		m_barrier.restartPosition(Terrain::MIN_BOUNDARY_VEC, Terrain::MAX_BOUNDARY_VEC);
	} 
	while (CollisionManager::checkCollisionsBool(collideableList));

	m_timer.setLastRestartTimeToCurrentTime();
}
