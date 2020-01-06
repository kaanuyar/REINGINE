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

	float callPythonAI(Player& player, Target& target, Obstacle& obstacle, bool isGameOver);

private:
	void insertKeyAndValuesToPyDict(PyObject* dict, const char* keyName, Vector3f valueVector);
	PyObject* m_pModule;
	PyObject* m_pFunc;
};