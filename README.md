# GoodGameEngine
>"Game engine" of my own, so I can make games with SFML and C++ more easily.

## Main game engine parts:

* **Game** - main container for game loop, init, level, etc.
* **GObject** - unit of some in-game object. For example level, camera or player
* **Manager** - main container for all the non-objects like dialogues, controls, cooldowns, instructions, etc.
* **Level** - main container for all the GObjects, dialogues, etc.
* **Instructions**:
  - **TriggerManager** - contains all the triggers, runs "check" method to check if trigger event has happened
  - **Trigger** - checks for event to activate action
  - **Action** - does the thing if trigger has told to do it
 
### Developer can create their own Levels, Intructions, GObjects in GGECustom directory  
