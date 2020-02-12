#include "pch.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/glm.hpp"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine.h"
#include "GraphicsManager.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

void Camera::recalculateMatrices()
{
  if (m_isDirty)
  {
    calculateViewVector();
    m_viewMatrix = glm::lookAt(m_position, m_position + m_viewVector, m_up);
    float aspect = (m_screenHeight == 0.0f) ? 0.0f : getAspectRatio();
    if (m_usePerspectiveMatrix)
    {
      m_projectionMatrix = glm::perspective(glm::radians(m_fov), aspect, m_nearClipPlane, m_farClipPlane);
    }
    else
    {
      float screenWidth = m_orthographicZoom;
      float screenHeight = screenWidth / aspect;
      m_projectionMatrix = glm::ortho(-screenWidth / 2.0f, screenWidth / 2.0f, -screenHeight / 2.0f, screenHeight / 2.0f, m_nearClipPlane, m_farClipPlane);
    }

    m_isDirty = false;
  }
}

void Camera::setUpDirection(const glm::vec3 &upDir)
{
  m_up = upDir;
  m_isDirty = true;
}

void Camera::setPosition(const glm::vec3 &position)
{
  glm::vec3 offset = position - m_position;
  m_position = position;
  m_isDirty = true;
}

void Camera::addTranslation(const glm::vec3 &translation)
{
  m_position += translation;
  m_viewTarget += translation;
  m_isDirty = true;
}

void Camera::addRelativeTranslation(const glm::vec3 &translation)
{
  recalculateMatrices();
  glm::vec3 relTranslation = glm::inverse(m_viewMatrix) * glm::vec4(translation, 0.0f);
  addTranslation(relTranslation);
}

void Camera::setViewTarget(const glm::vec3 &target)
{
  glm::vec3 viewVector = target - m_position;
  float length = glm::length(viewVector);
  glm::vec3 cross = glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), viewVector);
  m_orientation.x = cross.x;
  m_orientation.y = cross.y;
  m_orientation.z = cross.z;
  m_orientation.w = glm::sqrt(length * length) + glm::dot(viewVector, glm::vec3(0.0f, 0.0f, -1.0f));
  m_orientation = glm::normalize(m_orientation);
  m_isDirty = true;
}

void Camera::setViewDirection(const glm::vec2 &pitchYaw)
{
  setViewDirectionInRadians(glm::radians(pitchYaw));
}

void Camera::setViewDirectionInRadians(const glm::vec2 &pitchYaw)
{
  setPitchInRadians(pitchYaw.x);
  setYawInRadians(pitchYaw.y);
}

void Camera::setPitch(float degrees)
{
  setPitchInRadians(glm::radians(degrees));
}

static void normalizePlane(glm::vec4 &plane)
{
  float mag;
  mag = glm::sqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);

  plane.x = plane.x / mag;
  plane.y = plane.y / mag;
  plane.z = plane.z / mag;
  plane.w = plane.w / mag;
}

static bool isSphereInPlane(const glm::vec4 &plane, const glm::vec4 &sphereCenter, float sphereRadius)
{
  glm::vec4 normalizedPlane = plane;
  normalizePlane(normalizedPlane);

  float eval = glm::dot(glm::vec3(sphereCenter), glm::vec3(normalizedPlane)) + normalizedPlane.w + sphereRadius;
  if (eval < 0)
  {
    return false;
  }

  return true;
}

void Camera::setYaw(float degrees)
{
  setYawInRadians(glm::radians(degrees));
}

void Camera::setOrientation(const glm::quat& quat)
{
  m_orientation = glm::normalize(quat);
  m_isDirty = true;
}

void Camera::addRotation(const glm::quat& quatToAdd)
{
  m_orientation = quatToAdd * m_orientation;
  m_isDirty = true;
}

void Camera::setPitchInRadians(float radians)
{
  glm::vec3 euler = glm::eulerAngles(m_orientation);
  euler.x = radians;
  m_orientation = euler;
  m_isDirty = true;
}

void Camera::setYawInRadians(float radians)
{
  glm::vec3 euler = glm::eulerAngles(m_orientation);
  euler.y = radians;
  m_orientation = euler;
  m_isDirty = true;
}

float Camera::getPitch() const
{
  return glm::degrees(getPitchInRadians());
}

float Camera::getYaw() const
{
  return glm::degrees(getYawInRadians());
}

float Camera::getPitchInRadians() const
{
  return glm::eulerAngles(m_orientation).x;
}

float Camera::getYawInRadians() const
{
  return glm::eulerAngles(m_orientation).y;
}

const glm::mat4 &Camera::getViewMatrix()
{
  recalculateMatrices();
  return m_viewMatrix;
}

const glm::mat4 &Camera::getProjectionMatrix()
{
  recalculateMatrices();
  return m_projectionMatrix;
}

void Camera::setScreenRes(int width, int height)
{
  m_screenWidth = width;
  m_screenHeight = height;
  m_isDirty = true;
}

void Camera::setPerspective(bool isPerspective /*= true*/)
{
  m_usePerspectiveMatrix = isPerspective;
  m_isDirty = true;
}

void Camera::setOrthographicZoom(float zoom)
{
  m_orthographicZoom = zoom;
  m_isDirty = true;
}

void Camera::calculateViewVector()
{
  m_viewVector = m_orientation * glm::vec3(0.0f, 0.0f, -1.0f);
}


glm::vec3 Camera::getRightVector()
{
  recalculateMatrices();
  return glm::inverse(m_viewMatrix)[0];
}

glm::vec3 Camera::getUpVector()
{
  recalculateMatrices();
  return glm::inverse(m_viewMatrix)[1];
}

glm::vec3 Camera::getForwardVector()
{
  recalculateMatrices();
  return glm::inverse(m_viewMatrix)[2];
}

void Camera::addPitch(float degrees)
{
  addPitchInRadians(glm::radians(degrees));
}

void Camera::addYaw(float degrees)
{
  addYawInRadians(glm::radians(degrees));
}

void Camera::addPitchInRadians(float radians)
{
  setPitchInRadians(getPitchInRadians() + radians);
}

void Camera::addYawInRadians(float radians)
{
  setYawInRadians(getYawInRadians() + radians);
}

void Camera::setNearClipPlane(float near)
{
  m_nearClipPlane = near;
  m_isDirty = true;
}

void Camera::setFarClipPlane(float far)
{
  m_farClipPlane = far;
  m_isDirty = true;
}

void Camera::setFov(float fov)
{
  m_fov = fov;
  m_isDirty = true;
}

