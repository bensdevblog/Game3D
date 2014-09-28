#include "stdafx.h"
#include "camera.h"

using namespace std;

void Camera::computePos(float deltaMove)
{
	cam_x += deltaMove * x_vector * 0.1f;
	cam_z += deltaMove * z_vector * 0.1f;
}

void Camera::computeDir(float deltaAngle)
{
	angle_of_rotation += deltaAngle;
	x_vector = sin(angle_of_rotation);
	z_vector = -cos(angle_of_rotation);
}

void Camera::computePitch(float deltaPitch)
{
	pitch = deltaPitch;
}

void Camera::computeHeight(float deltaHeight)
{
	if (developer_view) //Only allow free movement on the y axis in developer mode.
		cam_y += deltaHeight;
}

void Camera::jump(void)
{
	if (jumping && getYvector() < 2.25f)
	{
		setYvector(getYvector() + 0.15f);
		if (getYvector() == 2.25f)
		{
			jumping = false;
		}
	}

	if (!jumping && getYvector() >= 0)
	{
		setYvector(getYvector() - 0.15f);
	}
}

void Camera::setAngleOfRot(float aor)
{
	angle_of_rotation = aor;
}
float Camera::getAngleOfRot(void)
{
	return angle_of_rotation;
}
void Camera::setCamX(float x)
{
	cam_x = x;
}
float Camera::getCamX(void)
{
	return cam_x;
}
void Camera::setCamY(float y)
{
	cam_y = y;
}
float Camera::getCamY(void)
{
	return cam_y;
}
void Camera::setCamZ(float z)
{
	cam_z = z;
}
float Camera::getCamZ(void)
{
	return cam_z;
}
void Camera::setXvector(float x_vec)
{
	x_vector = x_vec;
}
float Camera::getXvector(void)
{
	return x_vector;
}
void Camera::setYvector(float y_vec)
{
	y_vector = y_vec;
}
float Camera::getYvector(void)
{
	return y_vector;
}
void Camera::setZvector(float z_vec)
{
	z_vector = z_vec;
}
float Camera::getZvector(void)
{
	return z_vector;
}
void Camera::setDeltaAngle(float d_angle)
{
	delta_angle = d_angle;
}
float Camera::getDeltaAngle(void)
{
	return delta_angle;
}
void Camera::setDeltaMove(float d_move)
{
	delta_move = d_move;
}
float Camera::getDeltaMove(void)
{
	return delta_move;
}
void Camera::setDeltaHeight(float d_height)
{
	delta_height = d_height;
}
float Camera::getDeltaHeight(void)
{
	return delta_height;
}
void Camera::setPitch(float d_pitch)
{
	pitch = d_pitch;
}
float Camera::getPitch(void)
{
	return pitch;
}
void Camera::setXorigin(float x)
{
	x_origin = x;
}

float Camera::getXorigin(void)
{
	return x_origin;
}

void Camera::setYorigin(float y)
{
	y_origin = y;
}

float Camera::getYorigin(void)
{
	return y_origin;
}

void Camera::jumpState(boolean isJumping)
{
	jumping = isJumping;
}

boolean Camera::isJumping(void)
{
	return jumping;
}

void Camera::devState(boolean dev_view)
{
	developer_view = dev_view;
}

boolean Camera::isDevView(void)
{
	return developer_view;
}
