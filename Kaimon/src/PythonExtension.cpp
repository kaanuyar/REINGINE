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

Vector3f PythonExtension::callPythonAI(Player& player, std::vector<Obstacle*>& walls)
{
	Vector3f vec;
	if (m_pFunc && PyCallable_Check(m_pFunc))
	{
		PyObject* playerDict = PyDict_New();
		PyObject* wallList = PyList_New(walls.size());

		insertKeyAndValuesToPyDict(playerDict, "playerMax", player.getAABB().getWorldMaxVertex());
		insertKeyAndValuesToPyDict(playerDict, "playerMin", player.getAABB().getWorldMinVertex());

		for (int i = 0; i < walls.size(); i++)
		{
			Obstacle* obstacle = walls[i];

			PyObject *temp = PyDict_New();
			insertKeyAndValuesToPyDict(temp, "wallMax", obstacle->getAABB().getWorldMaxVertex());
			insertKeyAndValuesToPyDict(temp, "wallMin", obstacle->getAABB().getWorldMinVertex());
			PyList_SetItem(wallList, i, temp); 
		}


		PyObject* finalTuple = Py_BuildValue("{s:O,s:O}", "player", playerDict, "walls", wallList);
		Py_DECREF(playerDict);
		Py_DECREF(wallList);

		PyObject *arglist = Py_BuildValue("(O)", finalTuple);
		PyObject* pValue = PyObject_CallObject(m_pFunc, arglist);
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
}

void PythonExtension::insertKeyAndValuesToPyDict(PyObject * dict, char * keyName, Vector3f valueVector)
{
	PyObject *pArgs = Py_BuildValue("(fff)", double(valueVector.x), double(valueVector.y), double(valueVector.z));
	PyDict_SetItemString(dict, keyName, pArgs);
	Py_DECREF(pArgs);
}
