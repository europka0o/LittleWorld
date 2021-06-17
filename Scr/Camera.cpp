#include "Camera.hpp"

//----------------------------------Камера-Camera-Начало------------------------------
Camera::Camera(int x, int y, int screen_width, int screen_height) :
	screen_H(screen_height),
	screen_W(screen_width)
{
	pos.x = x;
	pos.y = y;
	Vid = new View;
	Vid->reset(FloatRect(0, 0, screen_W, screen_H));
}

Camera::Camera() :
	screen_H(600),
	screen_W(800)
{
	pos.x = 0;
	pos.y = 0;
	Vid = new View;
	Vid->reset(FloatRect(0, 0, screen_W, screen_H));
}

Camera::~Camera() {
	Vid->~View();
	delete Vid;
}

void __fastcall Camera::move(int x, int y) {
	pos.x = x;
	pos.y = y;
	Vid->setCenter(pos.x, pos.y);
}

void Camera::setZoom(float zoom) {
	Vid->zoom(zoom);
}

const axes_i& Camera::getPosition() const noexcept {
	return pos;
}

int Camera::getScreenWidth() const noexcept {
	return screen_W;
}
int Camera::getScreenHeight() const noexcept {
	return screen_H;
}

const FloatRect& Camera::getBounds() const noexcept {
	return Vid->getViewport();
}

void Camera::setView(RenderWindow& wd) {
	wd.setView(*Vid);
}

//----------------------------------Камера-Camera-Конец-------------------------------