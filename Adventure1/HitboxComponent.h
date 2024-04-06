#pragma once

using namespace sf;

class HitboxComponent
{
private:
	Sprite& sprite;
	RectangleShape hitbox;
	float offsetX;
	float offsetY;
public:
	HitboxComponent(Sprite& sprite, float offsetX,float offsetY, float width, float height);
	~HitboxComponent();

	bool CheckIntersect(const FloatRect& frect);
	void Update();
	void Render(RenderTarget& target);
};

