#include "Bullet.h"

void Bullet::update(bool tp) {
	livingTime += ellapsedTime;
	angularVelocity *= atrito;
	velocity *= atrito;
	rotation += angularVelocity * ellapsedTime;
	velocity += aceleration * float(ellapsedTime);
	pos += velocity * float(ellapsedTime);
	if (pos.x > projectionSize.x / 2 || pos.x < -projectionSize.x / 2 - size * texture->width || pos.y > projectionSize.y / 2 || pos.y < -projectionSize.y / 2 - size * texture->height) {
		shouldDestroy = true;

	}
}
