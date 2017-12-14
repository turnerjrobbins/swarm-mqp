#include "ci_occupancy_actuator.h"

CCI_OccupancyActuator::CCI_OccupancyActuator():
    m_unStrength(255),
    bLayingPheromone(false){}

#ifdef ARGOS_WITH_LUA
    void CCI_OccupancyActuator::CreateLuaState(lua_State* pt_lua_state){ }
#endif