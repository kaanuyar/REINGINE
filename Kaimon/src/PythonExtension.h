#pragma once

#include <Python.h>
#include <vector>
#include "Player.h"
#include "Obstacle.h"
#include "Target.h"

class PythonExtension
{
public:
	PythonExtension();
	~PythonExtension();

	Vector3f callPythonAI(Player& player, Target& target, bool isGameOver);
	Vector3f callPythonAI(Player& player, std::vector<Obstacle*>& walls);

private:
	void insertKeyAndValuesToPyDict(PyObject* dict, char* keyName, Vector3f valueVector);
	PyObject* m_pModule;
	PyObject* m_pFunc;
};