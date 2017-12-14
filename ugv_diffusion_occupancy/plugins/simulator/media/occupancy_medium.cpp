#include "occupancy_medium.h"
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

void CPheromoneMedium::Init(TConfigurationNode& t_tree){
    CMedium::Init(t_tree);

    std::string strDecayOption("linear");

    GetNodeAttributeOrDefault(t_tree, "cell_size", m_fCellSize, 0.1);

}

/****************************************/
/****************************************/

void CPheromoneMedium::PostSpaceInit(){

}

/****************************************/
/****************************************/

void CPheromoneMedium::Reset(){
    m_cPheromoneCells.clear();
}

/****************************************/
/****************************************/

void CPheromoneMedium::Destroy(){

}

/****************************************/
/****************************************/

CVector2 CPheromoneMedium::PositionToCellPosition(const CVector2& c_position) const{
    CVector2 cCellPosition;
    cCellPosition.SetX(ToCellDistance(c_position.GetX()));
    cCellPosition.SetY(ToCellDistance(c_position.GetY()));
    return cCellPosition;
}

/****************************************/
/****************************************/

void CPheromoneMedium::Update(){
    // for(auto &pair: m_cPheromoneCells){
    //     // update pheromone levels using callback chosen by Init
    //     m_cPheromoneUpdater(pair.second);
    //     // if pheromone level is 0 remove from map to make iteration quicker
    //     if(pair.second == 0){
    //         m_cPheromoneCells.erase(pair.first);
    //     }
    // }
}

/****************************************/
/****************************************/
void CPheromoneMedium::SetOccupancy(const CVector2& c_position) {
    CVector2 cell_position = PositionToCellPosition(c_position);
    m_cPheromoneCells[cell_position] = 1;
}

/****************************************/
/****************************************/

void CPheromoneMedium::SetLocalLevels(CPheromoneMedium::PheromoneMap& c_local_levels,
    const CVector2& c_cell_key,
    const CVector2& c_position)const{

    CPheromoneMedium::PheromoneMap::const_iterator fKeyPair;

    // check to see if the cell has any pheromone
    fKeyPair = m_cPheromoneCells.find(c_cell_key);
    if(fKeyPair != m_cPheromoneCells.end()){
        // set the transorm the cordinates to meters and 
        // translate it to be releative to the robot position
        CVector2 CLocalPosition = c_cell_key*m_fCellSize - c_position;
        // Set the entry in the local map
        c_local_levels[CLocalPosition] = fKeyPair->second;
    }
}

/****************************************/
/****************************************/


CPheromoneMedium::PheromoneMap CPheromoneMedium::ReadPheromone(const CVector2& c_position, 
    const Real& f_range, 
    const bool& b_circle)const{
    CPheromoneMedium::PheromoneMap cLocalLevels;
    
    // convert from meters to cell values
    //
    const CVector2 cAdjPosition(PositionToCellPosition(c_position));
    const UInt16 fAdjRange(ToCellDistance(f_range));
    
    // get 
    const CVector2 cPosOffset(cAdjPosition-PositionToCellPosition(c_position));
    const Real fRangeOffset(fabs(fAdjRange-ToCellDistance(f_range)));

    CVector2 cCellKey;

    SInt16 nX=0, nXMin=0, nXMax=0, nY=0, nYMin=0, nYMax=0, nZ=0, nZMin=0, nZMax=0;

    return cLocalLevels;
}
/****************************************/
/****************************************/

REGISTER_MEDIUM(CPheromoneMedium,
 "occupancy_medium",
 "Turner Robbins [tjrobbns@wpi.edu]",
 "0.0",
 "Medium that manages an occupancy grid.",
 "This medium develops the occupancy grid as determined by readings from occupancy_acuator\n\n"
 "REQUIRED XML CONFIGURATION\n\n"
 "<pheromone id=\"pheromone\" />\n\n"
 "OPTIONAL XML ATTRIBUTES\n\n"
 "cell_size - The size in meters of the pheromone cells, defaults to .1\n",
 "Under development"
);