#include <argos3/core/utility/datatypes/any.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>

#include <plugins/controllers/kheperaiv_exploration/kheperaiv_exploration_controller.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_measures.h>

#include "octomap_manager.h"

void CLoopOctomapManager::Init (TConfigurationNode& t_tree) {
	m_KheperaMap = GetSpace().GetEntitiesByType("kheperaiv");
	m_OcMap.setClampingThresMin(.1);
	m_OcMap.setClampingThresMax(.9);
	m_OcMap.setProbHit(.7);
	m_OcMap.setProbMiss(.3);
	//m_OcMap.setOccupancyThres(0.5);

}

void CLoopOctomapManager::insertRay() {
	std::cout << "\n----insert ray called!----" << std::endl;
}

void CLoopOctomapManager::PostStep() {
}

//CLoopOctomapManager::

REGISTER_LOOP_FUNCTIONS(CLoopOctomapManager, "octomap_manager")