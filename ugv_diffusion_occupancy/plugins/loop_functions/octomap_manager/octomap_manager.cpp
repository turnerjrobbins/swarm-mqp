#include <argos3/core/utility/datatypes/any.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_measures.h>

#include "plugins/controllers/kheperaiv_occupancy/kheperaiv_occupancy_controller.h"

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
		for(Real i = 0.0; i < KHEPERAIV_BASE_RADIUS * 1.1; i += OCTCELLSIZE) {
			for(Real j = 0.0; j < KHEPERAIV_BASE_RADIUS * 1.1; j += OCTCELLSIZE) {
				point3d pos (i, j,  KHEPERAIV_ULTRASOUND_SENSORS_RING_ELEVATION);
				point3d neg (-i, -j, KHEPERAIV_ULTRASOUND_SENSORS_RING_ELEVATION);
        		m_OcMap.updateNode(pos, false);  // integrate 'free' measurement
        		m_OcMap.updateNode(neg, false);
			}
		}
	}
}

//CLoopOctomapManager::

REGISTER_LOOP_FUNCTIONS(CLoopOctomapManager, "octomap_manager")