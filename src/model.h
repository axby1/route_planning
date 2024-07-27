#pragma once  //to prevent multiple inclusions of same header files

#include <vector>
#include <unordered_map>
#include <string>
#include <cstddef> //for std::byte

// this class Model server as a data structure for reprsenting geo-info. it organizes entities(nodes,ways,roads) and provides methods to access them   
class Model
{
public:
    struct Node {
        double x = 0.f; //coordinates
        double y = 0.f;
    };
    
    struct Way {
        std::vector<int> nodes; //IDs of nodes
    };
    
    struct Road {
        enum Type { Invalid, Unclassified, Service, Residential,
            Tertiary, Secondary, Primary, Trunk, Motorway, Footway };
        int way;
        Type type;
    };
    
    struct Railway {
        int way; 
    };    
    
    struct Multipolygon {
        std::vector<int> outer; //outer boundary of polygon 
        std::vector<int> inner; 
    };
    //structure inheritance (representing different lands)
    struct Building : Multipolygon {};
    
    struct Leisure : Multipolygon {};
    
    struct Water : Multipolygon {};
    
    struct Landuse : Multipolygon {
        enum Type { Invalid, Commercial, Construction, Grass, Forest, Industrial, Railway, Residential };
        Type type;
    };
    //constructor referencing a XML byte vector 
    Model( const std::vector<std::byte> &xml ); //defined in model.cpp
    
	//getter functions
    auto MetricScale() const noexcept { return m_MetricScale; }    
    
    auto &Nodes() const noexcept { return m_Nodes; }
    auto &Ways() const noexcept { return m_Ways; }
    auto &Roads() const noexcept { return m_Roads; }
    auto &Buildings() const noexcept { return m_Buildings; }
    auto &Leisures() const noexcept { return m_Leisures; }
    auto &Waters() const noexcept { return m_Waters; }
    auto &Landuses() const noexcept { return m_Landuses; }
    auto &Railways() const noexcept { return m_Railways; }
    
private:
	//not defined here
    void AdjustCoordinates(); 
    void BuildRings( Multipolygon &mp );
    void LoadData(const std::vector<std::byte> &xml); //loads data from provided XML byte vector 
    
    std::vector<Node> m_Nodes;
    std::vector<Way> m_Ways;
    std::vector<Road> m_Roads;
    std::vector<Railway> m_Railways;
    std::vector<Building> m_Buildings;
    std::vector<Leisure> m_Leisures;
    std::vector<Water> m_Waters;
    std::vector<Landuse> m_Landuses;
    
	//default values for geographic bounds and metric scale
    double m_MinLat = 0.;
    double m_MaxLat = 0.;
    double m_MinLon = 0.;
    double m_MaxLon = 0.;
    double m_MetricScale = 1.f;
};
