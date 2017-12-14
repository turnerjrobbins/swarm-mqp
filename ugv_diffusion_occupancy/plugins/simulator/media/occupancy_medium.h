#ifndef OCCUPANCY_MEDIUM_H
#define OCCUPANCY_MEDIUM_H

#include <map>
#include <functional>
#include <cmath>

#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/simulator/medium/medium.h>
#include <argos3/core/utility/datatypes/datatypes.h>

using namespace argos;


// used for PheromoneMap allowing vectors to be indicies
struct VectorCompare
{
   bool operator() (const CVector2& lhs, const CVector2& rhs) const
   {
       if(lhs.GetX() == rhs.GetX()){
            return lhs.GetY() < rhs.GetY();
       }
       return lhs.GetX() < rhs.GetX();
   }
};

class COccupancyMedium : public CMedium {

public:
    typedef std::map<CVector2, UInt16, VectorCompare> PheromoneMap;

    typedef std::function<void(UInt16&)> PheromoneUpdater;

    void Init(TConfigurationNode& t_tree) override;

    void PostSpaceInit() override;
    
    void Reset() override;
    
    void Destroy() override;
    
    void Update() override;


    /**
     * Converts a real position to the cell position, this can be 
     * used for inserting elements into m_cPheromoneCells
     * @param  c_position   The real position.
     * @param  b_ceil       The coordinates rounds up.
     * @return The cell position.
     */
    CVector2 PositionToCellPosition(const CVector2& c_position) const;

    /**
     * Lays pheromone at the given position.
     * Internally PositionToCellPosition will be called, so the real position can be given.
     * @param c_position  The position where you want to lay pheromone.
     */
    void SetOccupancy(const CVector2& c_position);

    // TODO: use true and false for bool params
    /**
     * Reads the pheromone levels around the given position.
     * Internally PositionToCellPosition will be called, so the real position can be given.
     * @param c_position    The position around which to measure pheromone.
     * @param f_range       The distance of cells to be returned  
     * @param b_circle      If enabled, a circle filter is used. Not yet implemented.
     * @returned            A PheromoneMap of the local pheromone levels, with relative positions.
     */
    PheromoneMap ReadPheromone(const CVector2& c_position, const Real& f_range, 
                               const bool& b_circle=false) const;


    /**
     * @return The size of the cells
     */
    inline Real GetCellSize(){
        return m_fCellSize;
    }

    inline PheromoneMap GetPheromoneMap(){
        return m_cPheromoneCells;
    }

    /**
     * [SetLocalLevels description]
     * @param c_local_levels [description]
     * @param c_cell_key     [description]
     * @param c_position     [description]
     */
    void SetLocalLevels(COccupancyMedium::PheromoneMap& c_local_levels,
                                      const CVector2& c_cell_key,
                                      const CVector2& c_position)const;

    /**
     * Converts an real coordinate to a cell coordinate.
     * @param  f_original_coordinate The original coordinate.
     * @param  b_ceil                Indicates that the coordinates should round up.
     * @return                       The cell coordinate.
     */
    inline Real ToCellDistance(const Real& f_original_coordinate, 
                                 const bool& b_floor = true) const{
        if(b_floor)
            return floor(f_original_coordinate/m_fCellSize);
        return f_original_coordinate/m_fCellSize;
    }


private:


    /** The dimension of the occupancy grid cell size */
    Real m_fCellSize;

    /** Function to update pheromone levels for a cell value*/
    PheromoneUpdater m_cPheromoneUpdater;

    /** 
     * Keeps track of the occupancy values at certain positions. 
     * Do not write to the map directly, first use 
     * PositionToCellPosition to get valid cell positions.
     */
    PheromoneMap m_cPheromoneCells;
};

#endif