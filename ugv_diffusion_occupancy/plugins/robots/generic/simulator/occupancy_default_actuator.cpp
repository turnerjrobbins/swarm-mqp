#include <string>
#include <map>

#include "occupancy_default_actuator.h"
#include <argos3/core/simulator/simulator.h>

/****************************************/
/****************************************/

void CPheromoneActuator::SetRobot(CComposableEntity& c_entity){
    m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
}

/****************************************/
/****************************************/

void CPheromoneActuator::Init(TConfigurationNode& t_tree){
    try {
       /* Parent class init */
       CCI_PheromoneActuator::Init(t_tree);
       /* Get pheromone medium from id specified in the XML */
       std::string strMedium;
       GetNodeAttribute(t_tree, "medium", strMedium);
       m_pCPheromoneMedium = &(CSimulator::GetInstance().GetMedium<CPheromoneMedium>(strMedium));
    }
    catch(CARGoSException& ex) {
       THROW_ARGOSEXCEPTION_NESTED("Error initializing the range and bearing medium sensor", ex);
    }
}

/****************************************/
/****************************************/

void CPheromoneActuator::Update(){
    if(!m_occupancy_list.empty()) {
        for(CVector2 occupancy_location : m_occupancy_list) {
            m_pCPheromoneMedium->SetOccupancy(occupancy_location);
        }
        m_occupancy_list.clear();
    }
}

void CPheromoneActuator::SetOccupancy(Real dist, Real angle) {
    CRadians angle_radians = CRadians();
    angle_radians.FromValueInDegrees(angle);
    CVector2 local_to_obj = CVector2();
    local_to_obj.FromPolarCoordinates(dist, angle_radians);
    CVector3 global_robot_location = m_pcEmbodiedEntity->GetOriginAnchor().Position;
    CVector2 global_robot_location_2d = CVector2(global_robot_location.GetX(), global_robot_location.GetY());
    CVector2 global_to_obj = global_robot_location_2d + local_to_obj;
    m_occupancy_list.push_front(global_to_obj);

}

/****************************************/
/****************************************/

void CPheromoneActuator::Reset(){
    bLayingPheromone = false;
}

/****************************************/
/****************************************/

void CPheromoneActuator::Destroy(){

}

/****************************************/
/****************************************/

REGISTER_ACTUATOR(CPheromoneActuator,
                "occupancy", "default",
                "Chris Cormier [ccormier@wpi.com]",
                "0.1",
                "A generic pheromone actuator.",
                "This actuator allows robots to lay a trail of pheromone.\n"
                "This implementation of the pheromone actuator is associated to the\n"
                "pheromone medium. To be able to use this actuator, you must add a\n"
                "pheromone medium to the <media> section.\n"
                "This actuator allows a robot to lay a pheromone trail. To lay \n"
                "pheromone, you need the pheromone sensor.\n"
                "To use this actuator, in controllers you must include the\n"
                "ci_pheromone_actuator.h header.\n\n"
                "REQUIRED XML CONFIGURATION\n\n"
                "  <controllers>\n"
                "    ...\n"
                "    <my_controller ...>\n"
                "      ...\n"
                "      <sensors>\n"
                "        ...\n"
                "        <pheromone implementation=\"default\"\n"
                "                           medium=\"pheromone\" />\n"
                "        ...\n"
                "      </sensors>\n"
                "      ...\n"
                "    </my_controller>\n"
                "    ...\n"
                "  </controllers>\n\n",
                "In Development"
);