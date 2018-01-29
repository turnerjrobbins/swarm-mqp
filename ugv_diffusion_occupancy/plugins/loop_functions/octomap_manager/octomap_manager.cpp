#include "octomap_manager.h"

void CLoopOctomapManager::Init (TConfigurationNode& t_tree) {
	;
}

void CLoopOctomapManager::insertRay() {
	std::cout << "\n----insert ray called!----" << std::endl;
}

//CLoopOctomapManager::

REGISTER_LOOP_FUNCTIONS(CLoopOctomapManager, "octomap_manager")