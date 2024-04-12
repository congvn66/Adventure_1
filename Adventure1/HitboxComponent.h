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

	const Vector2f& GetPosition() const;
	void SetPosition(Vector2f& position);
	void SetPosition(const float x, const float y);
	bool Intersect(const FloatRect& frect);
	void Update();
	void Render(RenderTarget& target);
};

