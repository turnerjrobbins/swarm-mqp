#ifndef CI_PHEROMONE_ACTUATOR_H
#define CI_PHEROMONE_ACTUATOR_H

#include <argos3/core/control_interface/ci_actuator.h>

using namespace argos;

class CCI_PheromoneActuator : public CCI_Actuator{
public:

    CCI_PheromoneActuator();

    inline void SetStrength(const UInt16 un_strength){
        m_unStrength = un_strength;
    }

    inline UInt16 GetStrength(const UInt16 un_strength){
        return m_unStrength;
    }

    inline void SetLaying(const bool& b_laying){
        bLayingPheromone = b_laying;
    }

    inline bool GetLaying() const{
        return bLayingPheromone;
    }

    inline void SetOccupancy(Real dist, Real angle){}

    #ifdef ARGOS_WITH_LUA
        void CreateLuaState(lua_State* pt_lua_state) override;
    #endif

protected:
    bool bLayingPheromone;
    UInt16 m_unStrength;

};

#endif