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
                "pheromone", "default",
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