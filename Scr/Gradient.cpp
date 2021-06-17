#include "Gradient.hpp"

//------------------------------Градиент-gradient-Начало---------------------------------------
__interface_companents::gradient::gradient(const FloatRect& rt, int gd, const Color& first, const Color& second) :
	BaseInerface(0, 0, rt)
{
	rect = new sf::VertexArray;

	pos.x = fl_rect.left;
	pos.y = fl_rect.top;

	rect->setPrimitiveType(sf::Quads);

	switch (gd) {
		case __interface_companents::gradient_direction::leftOnRight:
			for (int i = 0; i < 2; i++) {
				colors.push_back(second);
				colors.push_back(first);
			}
			break;
		case __interface_companents::gradient_direction::rightOnLeft:
			for (int i = 0; i < 2; i++) {
				colors.push_back(first);
				colors.push_back(second);
			}
			break;
		case __interface_companents::gradient_direction::topOnBottom:
			colors.push_back(first);
			colors.push_back(first);
			colors.push_back(second);
			colors.push_back(second);
			break;
		case __interface_companents::gradient_direction::bottomOnTop:
			colors.push_back(second);
			colors.push_back(second);
			colors.push_back(first);
			colors.push_back(first);
			break;
		default:
			break;
	}

	rect->append(sf::Vertex(sf::Vector2f(fl_rect.left, fl_rect.top), colors[0]));
	rect->append(sf::Vertex(sf::Vector2f(fl_rect.left + fl_rect.width, fl_rect.top), colors[1]));
	rect->append(sf::Vertex(sf::Vector2f(fl_rect.left + fl_rect.width, fl_rect.top + fl_rect.height), colors[3]));
	rect->append(sf::Vertex(sf::Vector2f(fl_rect.left, fl_rect.top + fl_rect.height), colors[2]));
}

__interface_companents::gradient::~gradient() {
	delete rect;
}

void __interface_companents::gradient::setPosition(const axes_i& xy) {
	pos = xy;

	rect->clear();

	rect->append(sf::Vertex(sf::Vector2f(pos.x, pos.y), colors[0]));
	rect->append(sf::Vertex(sf::Vector2f(pos.x + fl_rect.width, pos.y), colors[1]));
	rect->append(sf::Vertex(sf::Vector2f(pos.x + fl_rect.width, pos.y + fl_rect.height), colors[3]));
	rect->append(sf::Vertex(sf::Vector2f(pos.x, pos.y + fl_rect.height), colors[2]));
}

void __fastcall __interface_companents::gradient::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;

	rect->clear();

	rect->append(sf::Vertex(sf::Vector2f(pos.x, pos.y), colors[0]));
	rect->append(sf::Vertex(sf::Vector2f(pos.x + fl_rect.width, pos.y), colors[1]));
	rect->append(sf::Vertex(sf::Vector2f(pos.x + fl_rect.width, pos.y + fl_rect.height), colors[3]));
	rect->append(sf::Vertex(sf::Vector2f(pos.x, pos.y + fl_rect.height), colors[2]));
}

void __interface_companents::gradient::render(RenderWindow& wd) noexcept {
	if (visible) {
		wd.draw(*rect);
	}
}
//-------------------------------Градиент-gradient-Конец---------------------------------------