#ifndef OCTOMAP_MANAGER_H
#define OCTOMAP_MANAGER_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>
#include <argos3/core/simulator/space/space.h>

#include <octomap/octomap.h>
#include <octomap/OcTree.h>

#define OCTCELLSIZE 0.04

using namespace argos;
using namespace octomap;

class CLoopOctomapManager : public CLoopFunctions {
public:
	//Constructor
	CLoopOctomapManager() : CLoopFunctions(), m_OcMap(OcTree(OCTCELLSIZE)) {} //Argument is resolution?

	//Destructor
	~CLoopOctomapManager() {}

	virtual void Init(TConfigurationNode& t_tree);

	virtual void Reset() {}

	virtual void Destroy() {
		m_OcMap.writeBinary("diffusion_tree.bt");
	}

	virtual void PreStep() {}

	virtual void PostStep();

	void insertRay();
private:
	octomap::OcTree m_OcMap;
	CSpace::TMapPerType m_KheperaMap;
};
#endif