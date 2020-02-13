/*!
 * \file    PropertyInspector.h
 * \author  Quinton Skinner
 * \par     Email: qsrenniks\@gmail.com
 * \par     2019/01/13
 */

#ifndef PROPERTYINSPECTOR_H
#define PROPERTYINSPECTOR_H

#include <filesystem>
#include <chrono>
#include <glm/glm.hpp>

class Camera;
class Transform;
class Shader;
class Texture;
class IInspector;

struct DragAndDropPayload
{
  void* m_data;
  int m_dataSize;
};

/*****************************************************************************/
/*!
\brief
  This class defines the interface for reflecting the properties of an object
  to imgui or other objects that might need the information.

\author q.skinner
\date January 2019
*/
/*****************************************************************************/
class PropertyInspector
{
public:

  bool beginCombo(const char* label, const char * selectedObject);
  void endCombo();

  void beginMainMenuBar();
  void endMainMenuBar();
  bool beginMenu(const char *label);
  void endMenu();

  void setNextWindowSize(const glm::vec2& scale);

  bool beginDragDropSource();
  void endDragDropSource();

  void setDragDropPayload(const char* payloadName, const void* payload, size_t payloadSize);
  DragAndDropPayload acceptDragDropPayload(const char* payloadName);

  bool isItemClicked() const;

  bool beginDragDropTarget();
  void endDragDropTarget();

  class List
  {
  public:
    List(PropertyInspector& inspector, const char* listLabel, std::string& currentlySelected);
    ~List();

    bool addSelectableItem(const std::string& item);
    bool isOpen() { return m_isOpen; };
  private:
    PropertyInspector& m_inspector;
    std::string& m_currentlySelectedItem;
    bool m_isOpen = false;
  };

  void pushID(const void* id);
  void pushID(const char* stringBegin, const char* stringEnd);
  void popID();
  // bool editString(const char* label, std::string& string);
  void openPopup(const char* label);
  bool beginPopup(const char* label);
  void endPopup();
  bool addSelectable(const char* label, bool condition);
  bool addSelectable(const char* label);
  void setSameLine();
  void beginChild(const char* label, const glm::vec2& size);
  void endChild();
  void beginGroup();
  void endGroup();
  //bool addMenuItem();
  bool editColor(const char* label, glm::vec4& color);
  bool editColor(const char* label, glm::vec3& color);
  void displayTexture(const char* label, Texture* texture, const glm::vec2& size = { 100.0f, 100.0f });
  void displayTexture(Texture* texture, const glm::vec2& size = { 100.0f, 100.0f });
  void displayTexture(unsigned int textureID, const glm::vec2& size = { 100.0f, 100.0f });
  bool addButton(const char* buttonLabel);
  bool editFloat(const char* label, float& floatR);
  bool editFloatRange(const char* label, float& floatR, float min, float max);
  bool editInteger(const char* label, int& intR);
  bool editUnsigned(const char* label, unsigned& unsignedR);
  bool editIntegerRange(const char* label, int& intR, int min, int max);
  void displayVector3(const char* label, const glm::vec3& vec3R);
  bool editVector4(const char* label, glm::vec4& vec3R);
  bool editVector3(const char* label, glm::vec3& vec3R);
  bool editVector2(const char* label, glm::vec2& vec2R);
  bool addCheckbox(const char* label, bool& boolR);
  void displayBool(const char* label, const bool& boolR);
  void addSeparator();
  void addLabel(const char* label, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
  bool addDirectoryList(const char* listLabel, const char* directoryPath, std::string& selectedFilesName);
  void displayFloat(const char* label, float floatDisplay);
  bool beginTree(const char* label, const void* id, bool isSelected = false, bool isLeaf = false);
  void endTree();
  void editTransform(Transform& transformR, bool addFieldSeparator = false, const char* label = nullptr);

  bool beginWindow(const char* windowName, bool& openCloseFlag);
  void endWindow();

  bool addCollapsingHeader(const char* label);

  template<typename ... tParmPack>
  void addLabel(const glm::vec4& color, const char* label, tParmPack... args);
  template<typename ... tParmPack>
  void addLabel(const char* label, tParmPack... args);

private:

  bool startList(const char* label, const std::string& currentSelected);
  bool selectableItem(const std::string& item, bool& isSelected);
  void endList();

};

template<typename ... tParmPack>
void PropertyInspector::addLabel(const glm::vec4& color, const char* label, tParmPack... args)
{
  ImGui::TextColored(ImVec4(color.r, color.g, color.b, color.a), label, std::forward<tParmPack>(args)...);
}

template<typename ... tParmPack>
void PropertyInspector::addLabel(const char* label, tParmPack... args)
{
  ImGui::Text(label, std::forward<tParmPack>(args)...);
}

#endif
