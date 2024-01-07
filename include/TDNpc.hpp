#include "KinematicBody.hpp"

class TDNpc : public KinematicBody
{
private:
    // Variables
    Direction movementDir;
    NpcType npcType;

    // Methods
    // npc movement
    void control();
    
public:
    // Structors
    TDNpc();
    ~TDNpc();
    // methods
    // set type of npc
    void setType(NpcType newType);
};