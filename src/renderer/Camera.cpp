#include "Camera.h"

const vec2 defaultSize = vec2(1000, 1000);
Camera::Camera(vec3 initialPos, float initialZoom,const vec2& windowSize, float initialFov) : pos(initialPos), zoom(initialZoom),fov(initialFov){
	
	scaleMatrix = mat4(1.0f);

	modelMatrix = mat4(1.0f);


	updateProjection(windowSize.x,windowSize.y,nearPlane, farPlane);
	setZoom(zoom);

	setPos(initialPos);
}

void Camera::unBindShader()
{
	Shaders::shaders["cards"]->unBind();
}
void Camera::bindShader()
{
	Shaders::shaders["cards"]->bind();
}
Camera::~Camera()
{

}
void Camera::setZoom(float zoom) {
	this->zoom = zoom;
	scaleMatrix = scale(mat4(1.0f), vec3(zoom, zoom, zoom));
	updateModelMatrix();
	

}
void Camera::setPos(vec3& newPos) {
	pos = newPos;
	updateModelMatrix();
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
void Camera::updateModelMatrix() {
	modelMatrix = perspectiveMatrix * translate(mat4(1.0f), - pos) * scaleMatrix;
	for (int i = 0; i < Shaders::shadersToSendProjection.size(); ++i) {
		Shaders::shadersToSendProjection[i]->bind();
		Shaders::shadersToSendProjection[i]->uniformMatrix4f("model", 1, GL_FALSE, value_ptr(modelMatrix));

	}
	if (Shaders::shadersToSendProjection.size() > 0) {
		Shaders::shadersToSendProjection[Shaders::shadersToSendProjection.size() - 1]->unBind();
	}

}
void Camera::updateProjection(float width, float height,float mnear, float mfar)
{

	windowSize = vec2(width, height);
	projectionSize = vec2(960,540);
    perspectiveMatrix = glm::ortho(-960.0f/2, 960.0f/2, -540.0f/2, 540.0f/2, mfar, mnear);

	updateModelMatrix();
}
