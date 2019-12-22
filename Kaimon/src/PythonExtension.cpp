#include "PythonExtension.h"


PythonExtension::PythonExtension()
{
	Py_Initialize();

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('py_src')");

	PyObject* pName = PyUnicode_DecodeFSDefault("training");

	m_pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (m_pModule != NULL)
		m_pFunc = PyObject_GetAttrString(m_pModule, "step");
	else
		PyErr_Print();
}

PythonExtension::~PythonExtension()
{
	Py_XDECREF(m_pFunc);
	Py_DECREF(m_pModule);

	Py_FinalizeEx();
}

/*Vector3f PythonExtension::callPythonAI(Player& player, Target& target, bool isGameOver)
{
	Vector3f vec;
	if (m_pFunc && PyCallable_Check(m_pFunc))
	{
		PyObject* playerDict = PyDict_New();
		PyObject* targetDict = PyDict_New();

		insertKeyAndValuesToPyDict(playerDict, "playerMax", player.getAABB().getWorldMaxVertex());
		insertKeyAndValuesToPyDict(playerDict, "playerMin", player.getAABB().getWorldMinVertex());

		insertKeyAndValuesToPyDict(targetDict, "targetMax", target.getAABB().getWorldMaxVertex());
		insertKeyAndValuesToPyDict(targetDict, "targetMin", target.getAABB().getWorldMinVertex());

		PyObject* finalTuple = Py_BuildValue("{s:O,s:O,s:O}", "player", playerDict, "target", targetDict, "isGameOver", isGameOver ? Py_True : Py_False);
		Py_DECREF(playerDict);
		Py_DECREF(targetDict);

		PyObject* argList = Py_BuildValue("(O)", finalTuple);
		PyObject* pValue = PyObject_CallObject(m_pFunc, argList);
		Py_DECREF(finalTuple);

		if (pValue != NULL && PyList_Check(pValue) && PyList_Size(pValue) == 3)
		{
			float x = float(PyFloat_AsDouble(PyList_GetItem(pValue, 0)));
			float y = float(PyFloat_AsDouble(PyList_GetItem(pValue, 1)));
			float z = float(PyFloat_AsDouble(PyList_GetItem(pValue, 2)));

			vec = Vector3f(x, y, z);
			//printf("Result of call: %lf %lf %lf\n", vec.x, vec.y, vec.z);
			Py_DECREF(pValue);
		}
		else
			PyErr_Print();
	}
	else
		PyErr_Print();

	return vec;
}*/

float PythonExtension::callPythonAI(Player& player, Target& target, bool isGameOver)
{
	float angleInDegrees = -1.0f;
	if (m_pFunc && PyCallable_Check(m_pFunc))
	{
		PyObject* playerDict = PyDict_New();
		PyObject* targetDict = PyDict_New();

		insertKeyAndValuesToPyDict(playerDict, "playerMax", player.getAABB().getWorldMaxVertex());
		insertKeyAndValuesToPyDict(playerDict, "playerMin", player.getAABB().getWorldMinVertex());

		insertKeyAndValuesToPyDict(targetDict, "targetMax", target.getAABB().getWorldMaxVertex());
		insertKeyAndValuesToPyDict(targetDict, "targetMin", target.getAABB().getWorldMinVertex());

		PyObject* finalTuple = Py_BuildValue("{s:O,s:O,s:O}", "player", playerDict, "target", targetDict, "isGameOver", isGameOver ? Py_True : Py_False);
		Py_DECREF(playerDict);
		Py_DECREF(targetDict);

		PyObject* argList = Py_BuildValue("(O)", finalTuple);
		PyObject* pValue = PyObject_CallObject(m_pFunc, argList);
		Py_DECREF(argList);
		Py_DECREF(finalTuple);

		if (pValue != NULL)
		{
			angleInDegrees = (float) PyFloat_AsDouble(pValue);
			//printf("Result of call: %lf %lf %lf\n", vec.x, vec.y, vec.z);
			Py_DECREF(pValue);
		}
		else
			PyErr_Print();
	}
	else
		PyErr_Print();

	return angleInDegrees;
}

void PythonExtension::insertKeyAndValuesToPyDict(PyObject* dict, const char* keyName, Vector3f valueVector)
{
	PyObject *pArgs = Py_BuildValue("[fff]", double(valueVector.x), double(valueVector.y), double(valueVector.z));
	PyDict_SetItemString(dict, keyName, pArgs);
	Py_DECREF(pArgs);
}
