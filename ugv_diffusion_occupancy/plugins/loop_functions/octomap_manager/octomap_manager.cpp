#include <plugins/controllers/kheperaiv_occupancy/kheperaiv_occupancy_controller.h>

#include <argos3/core/utility/datatypes/any.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>

#include "octomap_manager.h"

void CLoopOctomapManager::Init (TConfigurationNode& t_tree) {
	m_KheperaMap = GetSpace().GetEntitiesByType("kheperaiv");
	m_OcMap.setClampingThresMin(.15);
	m_OcMap.setClampingThresMax(.85);
	m_OcMap.setProbHit(.6);
	m_OcMap.setProbMiss(.35);
	m_OcMap.setOccupancyThres(0.5);

}

void CLoopOctomapManager::insertRay() {
	std::cout << "\n----insert ray called!----" << std::endl;
}

void CLoopOctomapManager::PostStep() {
	std::vector<octomap::point3d> robots;
	for(CSpace::TMapPerType::iterator it = m_KheperaMap.begin(); it != m_KheperaMap.end(); ++it) {
		/* Get the kheperaController */
		CKheperaIVEntity& kheperaEntity = *any_cast<CKheperaIVEntity*>(it->second);
		CKheperaOccupancy& kheperaController = dynamic_cast<CKheperaOccupancy&>(kheperaEntity.GetControllableEntity().GetController());
		octomap::Pointcloud localScan = kheperaController.getLocalScan();
		/* 3D representation of sensor origin */
  		octomap::point3d startp = octomap::point3d(kheperaEntity.GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
  													kheperaEntity.GetEmbodiedEntity().GetOriginAnchor().Position.GetY(), 
  													kheperaEntity.GetEmbodiedEntity().GetOriginAnchor().Position.GetZ());
  		robots.push_back(startp);
  		/* Update local map by inserting the point cloud*/
  		m_OcMap.insertPointCloud(localScan, startp);
  		kheperaController.clearLocalScan();
	}
	/* go through robot locations and clear them on the map */
	for(octomap::point3d pos : robots) {
		;
	}
}

//CLoopOctomapManager::

REGISTER_LOOP_FUNCTIONS(CLoopOctomapManager, "octomap_manager")