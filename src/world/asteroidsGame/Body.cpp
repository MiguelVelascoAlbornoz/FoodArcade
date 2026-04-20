#include "Body.h"

void Body::update(bool tp)
{
	angularVelocity *= atrito;
	velocity *=atrito;
	rotation += angularVelocity * ellapsedTime;
	velocity += aceleration *float( ellapsedTime);
	pos += velocity * float(ellapsedTime);
	if (tp) {
		if (pos.x > projectionSize.x / 2) {
			pos.x = -projectionSize.x / 2 - size * texture->width + 1;

		}
		else if (pos.x < -projectionSize.x / 2 - size * texture->width) {
			pos.x = projectionSize.x / 2 - 1;
		}
		if (pos.y > projectionSize.y / 2) {
			pos.y = -projectionSize.y / 2 - size * texture->height + 1;

		}
		else if (pos.y < -projectionSize.y / 2 - size * texture->height) {
			pos.y = projectionSize.y / 2 - 1;
		}
	}

}

void Body::draw(VAO* squareVao)
{
	mat4 rotationMatrix = rotate(mat4(1.0f),rotation,vec3(0.0f,0.0f,1.0f));
	Shaders::shaders["asteroids"]->uniform1f("size", size);
	Shaders::shaders["asteroids"]->uniform1i("isBackground", 0);
	Shaders::shaders["asteroids"]->uniformMatrix4f("rotationMatrix", 1, GL_FALSE, value_ptr(rotationMatrix));
	Shaders::shaders["asteroids"]->uniform2f("modelPos", pos.x, pos.y);
	Shaders::shaders["asteroids"]->uniform2f("massCenter",massCenter.x,massCenter.y);
	Shaders::shaders["asteroids"]->uniform2f("textSize", texture->width, texture->height);
	texture->bindTexture(0, Shaders::shaders["asteroids"], "text");
	squareVao->draw(GL_TRIANGLES);
	if (drawFire) {
		gif.use(0, Shaders::shaders["asteroids"], "text");
		squareVao->draw(GL_TRIANGLES);
	}
	
}

void Body::calculateVertices()
{
	
    std::vector<vec2> points = { vec2(0.0f),vec2(texture->width * size,0.0f), vec2(0.0f,texture->height * size) , vec2(texture->width * size,texture->height *size) };
	for (int i = 0; i < 4; ++i) {

		vertices[i] = vec2(rotate(mat4(1.0f), rotation, vec3(0.0f, 0.0f, 1.0f)) * vec4(points[i] - massCenter, 0.0f, 1.0f)) + pos + massCenter;
	}
}
