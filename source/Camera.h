/*!
 * \file    Camera.h
 * \author  Quinton Skinner
 * \par     Email: qsrenniks\@gmail.com
 * \par     2019/03/17
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera
{
public:
  void recalculateMatrices();
  void setUpDirection(const glm::vec3 &upDir);
  void setPosition(const glm::vec3 &position);

  void addTranslation(const glm::vec3 &translation);
  void addRelativeTranslation(const glm::vec3 &translation);

  const glm::vec3 &getPosition() const { return m_position; };
  const glm::vec3 &getUp() const { return m_up; };

  //! sets pitch and yaw based on cameras position and target position
  void setViewTarget(const glm::vec3 &target);

  void setViewDirection(const glm::vec2 &pitchYaw);
  void setViewDirectionInRadians(const glm::vec2 &pitchYaw);
  void setPitch(float degrees);
  void setYaw(float degrees);

  void setPitchInRadians(float radians);
  void setYawInRadians(float radians);

  float getPitch() const;
  float getYaw() const;

  float getPitchInRadians() const;
  float getYawInRadians() const;

  void addPitch(float degrees);
  void addYaw(float degrees);

  void addPitchInRadians(float radians);
  void addYawInRadians(float radians);

  float getNearClipPlane() const { return m_nearClipPlane; };
  float getFarClipPlane() const { return m_farClipPlane; };

  float getAspectRatio() const { return float(m_screenWidth) / float(m_screenHeight); };

  void setNearClipPlane(float near);
  void setFarClipPlane(float far);

  void setFov(float fov);
  float getFov() const { return m_fov; };

  glm::vec3 getForwardVector();
  glm::vec3 getUpVector();
  glm::vec3 getRightVector();

  const glm::mat4 &getViewMatrix();
  const glm::mat4 &getProjectionMatrix();

  void setScreenRes(int width, int height);

  void setPerspective(bool isPerspective = true);
  bool getIsPerspective() const { return m_usePerspectiveMatrix; };

  void setOrthographicZoom(float zoom);
  float getOrthographicZoom() const { return m_orthographicZoom; };

  void setOrientation(const glm::quat& quat);
  void addRotation(const glm::quat& quatToAdd);

private:
  void calculateViewVector();

  int m_screenWidth = 1920;
  int m_screenHeight = 1080;
  float m_nearClipPlane = 0.1f;
  float m_farClipPlane = 100.0f;
  float m_fov = 50.0f;
  float m_orthographicZoom = 10.0f;
  bool m_usePerspectiveMatrix = true;

  glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
  glm::vec3 m_viewVector = {0.0f, 0.0f, -1.0f};
  glm::vec3 m_viewTarget = {0.0f, 0.0f, 0.0f};
  glm::vec3 m_up = {0.0f, 1.0f, 0.0f};
  glm::mat4 m_viewMatrix = glm::mat4(1.0f);
  glm::mat4 m_projectionMatrix = glm::mat4(1.0f);

  glm::quat m_orientation = {0.0f, 0.0f, 0.0f, 1.0f};

  bool m_isDirty = true;
};

#endif
