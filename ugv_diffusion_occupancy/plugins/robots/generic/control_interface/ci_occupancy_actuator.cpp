#include "ci_occupancy_actuator.h"

CCI_PheromoneActuator::CCI_PheromoneActuator():
    m_unStrength(255),
    bLayingPheromone(false){}

#ifdef ARGOS_WITH_LUA
    void CCI_PheromoneActuator::CreateLuaState(lua_State* pt_lua_state){ }
#endif