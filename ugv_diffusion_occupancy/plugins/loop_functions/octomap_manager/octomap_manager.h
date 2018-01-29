#ifndef OCTOMAP_MANAGER_H
#define OCTOMAP_MANAGER_H
#include <argos3/core/simulator/loop_functions.h>
#include <octomap/octomap.h>
#include <octomap/OcTree.h>

using namespace argos;
using namespace octomap;

class CLoopOctomapManager : public CLoopFunctions {
public:
	//Constructor
	CLoopOctomapManager() : CLoopFunctions(), m_OcTree(OcTree(0.1)) {} //Argument is resolution?

	//Destructor
	~CLoopOctomapManager() {}

	virtual void Init(TConfigurationNode& t_tree);

	virtual void Reset() {}

	virtual void Destroy() {}

	virtual void PreStep() {}

	virtual void PostStep() {}

	void insertRay();
private:
	octomap::OcTree m_OcTree;
};
#endif