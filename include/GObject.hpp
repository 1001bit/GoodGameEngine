#include <SFML/Graphics.hpp>
#include <vector>

class GObject
{
public:
    std::vector<std::unique_ptr<GObject>> children;
    sf::Vector2f realtivePos;
    GObject();
    ~GObject();
};