#pragma once

#include "VAO.h"


class Camera
{
public:
	Camera(vec3 initialPos, float initialZoom, const vec2& windowSize, float fov);

	~Camera();

	vec3 getPos() { return pos; }
	void setZoom(float zoom);
	float getZoom() { return zoom; };

	void bindShader();
	void setPos(vec3& newPos);


	void updateModelMatrix();
	void updateProjection(float width, float height, float near, float far);
	void unBindShader();
	float getFov() { return fov; };
	float getNear() { return nearPlane; };
	float getFar() { return farPlane; };
	//const vec2& windowSize;

	mat4 modelMatrix = mat4(1.0f);
	private :


	float fov;
	mat4 scaleMatrix;
	mat4 perspectiveMatrix;
	mat4 rotationMatrix;
	
	float nearPlane = 0.1;
	float farPlane = 100.0f;
	static const vec2& defaultSize;

	vec3 pos;
	float zoom;

};

