#include <string>
#include <map>

#include "occupancy_default_actuator.h"
#include <argos3/core/simulator/simulator.h>

/****************************************/
/****************************************/

void COccupancyActuator::SetRobot(CComposableEntity& c_entity){
    m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
}

/****************************************/
/****************************************/

void COccupancyActuator::Init(TConfigurationNode& t_tree){
    try {
       /* Parent class init */
       CCI_OccupancyActuator::Init(t_tree);
       /* Get pheromone medium from id specified in the XML */
       std::string strMedium;
       GetNodeAttribute(t_tree, "medium", strMedium);
       m_pCOccupancyMedium = &(CSimulator::GetInstance().GetMedium<COccupancyMedium>(strMedium));
    }
    catch(CARGoSException& ex) {
       THROW_ARGOSEXCEPTION_NESTED("Error initializing the range and bearing medium sensor", ex);
    }
}

/****************************************/
/****************************************/

void COccupancyActuator::Update(){
    auto size = m_occupancy_list.size();
    for(int i = 0; i < size; i++) {
      m_pCOccupancyMedium->SetOccupancy(m_occupancy_list.front());
      m_occupancy_list.pop_front();
    } 
}

void COccupancyActuator::SetOccupancy(Real dist) {
    LOG << "Setting occupancy for " + std::to_string(dist) << std::endl;
    //Get the position wrt the global frame
    CVector3 global_robot_location = m_pcEmbodiedEntity->GetOriginAnchor().Position;
    //Get the orientation
    CQuaternion global_robot_orientation = m_pcEmbodiedEntity->GetOriginAnchor().Orientation;

    //Make a vector in the x direction
    CVector3 local_vec = CVector3(dist, 0.0, 0.0);
    //rotate it by the quaternion
    local_vec.Rotate(global_robot_orientation);

    //add the two vectors together to get the location of the object
    global_robot_location += local_vec;

    //Make it twoD
    CVector2 obj_location = CVector2(global_robot_location.GetX(), global_robot_location.GetY());

    LOG << obj_location<< std::endl;
    m_occupancy_list.push_front(obj_location);
}

/****************************************/
/****************************************/

void COccupancyActuator::Reset(){
    bLayingPheromone = false;
}

/****************************************/
/****************************************/

void COccupancyActuator::Destroy(){

}

/****************************************/
/****************************************/

REGISTER_ACTUATOR(COccupancyActuator,
                "occupancy", "default",
                "Chris Cormier [ccormier@wpi.com]",
                "0.1",
                "A generic occupancy actuator.",
                "",
                ""
);