#include <SFML/Graphics.hpp>
#include "Common.hpp"

class Trail : public sf::VertexArray {
private:
	sf::Color calculateColor(float vel);
public:
	Trail() { this->setPrimitiveType(sf::LinesStrip); };

	void update(sf::Vector2<float> pos, float vel);
};