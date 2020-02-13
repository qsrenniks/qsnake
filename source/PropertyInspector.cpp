#include "pch.h"
#include "PropertyInspector.h"
#include "Camera.h"
#include "Shader.h"
#include <filesystem>

bool PropertyInspector::beginCombo(const char *label, const char *selectedObject)
{
  return ImGui::BeginCombo(label, selectedObject, ImGuiComboFlags_None);
}

void PropertyInspector::endCombo()
{
  ImGui::EndCombo();
}

void PropertyInspector::beginMainMenuBar()
{
  ImGui::BeginMainMenuBar();
}

void PropertyInspector::endMainMenuBar()
{
  ImGui::EndMainMenuBar();
}

bool PropertyInspector::beginMenu(const char *label)
{
  return ImGui::BeginMenu(label);
}

void PropertyInspector::endMenu()
{
  ImGui::EndMenu();
}

bool PropertyInspector::beginDragDropSource()
{
  return ImGui::BeginDragDropSource(ImGuiDragDropFlags_None);
}

void PropertyInspector::endDragDropSource()
{
  ImGui::EndDragDropSource();
}

void PropertyInspector::setDragDropPayload(const char *payloadName, const void *payload, size_t payloadSize)
{
  ImGui::SetDragDropPayload(payloadName, payload, payloadSize);
}

DragAndDropPayload PropertyInspector::acceptDragDropPayload(const char *payloadName)
{
  const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(payloadName);

  DragAndDropPayload tempPayload;
  if (payload)
  {
    tempPayload.m_data = payload->Data;
    tempPayload.m_dataSize = payload->DataSize;
  }
  else
  {
    tempPayload.m_data = nullptr;
    tempPayload.m_dataSize = 0;
  }

  return tempPayload;
}

bool PropertyInspector::isItemClicked() const
{
  return ImGui::IsItemClicked();
}

bool PropertyInspector::beginDragDropTarget()
{
  return ImGui::BeginDragDropTarget();
}

void PropertyInspector::endDragDropTarget()
{
  ImGui::EndDragDropTarget();
}

void PropertyInspector::pushID(const void *id)
{
  ImGui::PushID(id);
}

void PropertyInspector::pushID(const char* stringBegin, const char* stringEnd)
{
  ImGui::PushID(stringBegin, stringEnd);
}

void PropertyInspector::popID()
{
  ImGui::PopID();
}

// bool PropertyInspector::editString(const char *label, std::string &string)
// {
//   return ImGui::InputText(label, &string);
// }

void PropertyInspector::openPopup(const char *label)
{
  ImGui::OpenPopup(label);
}

bool PropertyInspector::beginPopup(const char *label)
{
  return ImGui::BeginPopup(label);
}

void PropertyInspector::endPopup()
{
  ImGui::EndPopup();
}

bool PropertyInspector::addSelectable(const char *label, bool condition)
{
  return ImGui::Selectable(label, condition);
}

bool PropertyInspector::addSelectable(const char *label)
{
  return ImGui::Selectable(label);
}

void PropertyInspector::setSameLine()
{
  ImGui::SameLine();
}

void PropertyInspector::beginChild(const char *label, const glm::vec2 &size)
{
  ImGui::BeginChild(label, ImVec2(size.x, size.y), true, ImGuiWindowFlags_AlwaysAutoResize);
}

void PropertyInspector::endChild()
{
  ImGui::EndChild();
}

void PropertyInspector::beginGroup()
{
  ImGui::BeginGroup();
}

void PropertyInspector::endGroup()
{
  ImGui::EndGroup();
}

bool PropertyInspector::editColor(const char *label, glm::vec4 &color)
{
  return ImGui::ColorEdit4(label, &color[0]);
}

bool PropertyInspector::editColor(const char *label, glm::vec3 &color)
{
  return ImGui::ColorEdit3(label, &color[0]);
}

// void PropertyInspector::displayTexture(const char *label, Texture *texture, const glm::vec2 &size)
// {
//   if (texture == nullptr)
//   {
//     ImGui::Text("%s : null", label);
//     return;
//   }

//   ImGui::Text(label);
//   //ImGui::Image((void*)(intptr_t)texture->getTextureID(), ImVec2(float(texture->getTextureWidth()), float(texture->getTextureHeight())));
//   ImGui::Image((void *)(intptr_t)texture->getTextureID(), ImVec2(size.x, size.y));
// }

// void PropertyInspector::displayTexture(Texture *texture, const glm::vec2 &size /*= {100.0f, 100.0f}*/)
// {
//   ImGui::Image((void *)(intptr_t)texture->getTextureID(), ImVec2(size.x, size.y));
// }

void PropertyInspector::displayTexture(unsigned int textureID, const glm::vec2 &size /*= { 100.0f, 100.0f }*/)
{
  ImGui::Image((void *)(intptr_t)textureID, ImVec2(size.x, size.y), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
}

bool PropertyInspector::addButton(const char *buttonLabel)
{
  return ImGui::Button(buttonLabel);
}

bool PropertyInspector::editFloat(const char *label, float &floatR)
{
  return ImGui::DragFloat(label, &floatR, 0.02f);
}

bool PropertyInspector::editFloatRange(const char *label, float &floatR, float min, float max)
{
  return ImGui::SliderFloat(label, &floatR, min, max);
}

bool PropertyInspector::editInteger(const char *label, int &intR)
{
  return ImGui::InputInt(label, &intR);
}

bool PropertyInspector::editUnsigned(const char *label, unsigned &unsignedR)
{
  return ImGui::InputInt(label, (int *)&unsignedR);
}

bool PropertyInspector::editIntegerRange(const char *label, int &intR, int min, int max)
{
  return ImGui::SliderInt(label, &intR, min, max);
}

bool PropertyInspector::editVector4(const char *label, glm::vec4 &vec3R)
{
  return ImGui::DragFloat4(label, &vec3R[0], 0.2f);
}

void PropertyInspector::displayVector3(const char *label, const glm::vec3 &vec3R)
{
  ImGui::LabelText(label, "x: %2.2f  y: %2.2f  z: %2.2f", vec3R.x, vec3R.y, vec3R.z);
}

bool PropertyInspector::editVector3(const char *label, glm::vec3 &vec3R)
{
  return ImGui::DragFloat3(label, &vec3R[0], 0.2f);
}

bool PropertyInspector::editVector2(const char *label, glm::vec2 &vec2R)
{
  return ImGui::DragFloat2(label, &vec2R[0]);
}

bool PropertyInspector::addCheckbox(const char *label, bool &boolR)
{
  return ImGui::Checkbox(label, &boolR);
}

void PropertyInspector::displayBool(const char *label, const bool &boolR)
{
  ImGui::RadioButton(label, boolR);
}

bool PropertyInspector::beginTree(const char *label, const void *id, bool isSelected, bool isLeaf)
{
  return ImGui::TreeNodeEx(id, ImGuiTreeNodeFlags_FramePadding | (isSelected ? ImGuiTreeNodeFlags_Selected : 0) | (isLeaf ? ImGuiTreeNodeFlags_Leaf : 0), label);
}

void PropertyInspector::endTree()
{
  ImGui::TreePop();
}

// void PropertyInspector::editTransform(const Tool &operation, glm::mat4 &drawPose)
// {
//   Camera &cam = Engine::getGraphics()->getActiveCamera();

//   const glm::mat4 &projection = cam.getProjectionMatrix();
//   const glm::mat4 &view = cam.getViewMatrix();

//   ImGuizmo::OPERATION op;
//   switch (Engine::getGameplay()->getEditorManager().getOperation())
//   {
//   case Tool::eTranslate:
//     op = ImGuizmo::OPERATION::TRANSLATE;
//     break;
//   case Tool::eRotate:
//     op = ImGuizmo::OPERATION::ROTATE;
//     break;
//   case Tool::eScale:
//     op = ImGuizmo::OPERATION::SCALE;
//     break;
//   }

//   if (op == ImGuizmo::OPERATION::SCALE)
//   {
//     ImGuizmo::Manipulate(&view[0][0], &projection[0][0], op, ImGuizmo::MODE::LOCAL, &drawPose[0][0]);
//   }
//   else
//   {
//     ImGuizmo::Manipulate(&view[0][0], &projection[0][0], op, ImGuizmo::MODE::WORLD, &drawPose[0][0]);
//   }
// }

bool PropertyInspector::beginWindow(const char *windowName, bool &openCloseFlag)
{
  if (openCloseFlag == false)
  {
    return false;
  }

  if (!ImGui::Begin(windowName, &openCloseFlag, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::End();
    return false;
  }
  else
    return true;
}

void PropertyInspector::endWindow()
{
  ImGui::End();
}

bool PropertyInspector::addCollapsingHeader(const char *label)
{
  return ImGui::CollapsingHeader(label);
}

void PropertyInspector::addSeparator()
{
  ImGui::Separator();
}

void PropertyInspector::addLabel(const char *label, const glm::vec4 &color)
{
  ImGui::TextColored(ImVec4(color.r, color.g, color.b, color.a), label);
}

static bool addDirectoryList_rec(PropertyInspector &inspector, const char *directoryPath, std::string &selectedFilesName)
{
  for (auto &dirEnt : std::filesystem::directory_iterator(directoryPath))
  {
    if (dirEnt.is_directory())
    {
      std::string dirEntName = dirEnt.path().filename().string();
      inspector.pushID(dirEntName.c_str(), dirEntName.c_str() + dirEntName.size());

      if (inspector.beginTree(dirEntName.c_str(), nullptr))
      {
        bool hit = addDirectoryList_rec(inspector, dirEnt.path().string().c_str(), selectedFilesName);
        if (hit)
        {
          return true;
        }

        inspector.endTree();
      }
      inspector.popID();
    }
    else
    {
      const std::string fileName = dirEnt.path().filename().string();
      if (inspector.addSelectable(fileName.c_str()))
      {
        selectedFilesName = fileName;
        inspector.endPopup();
        return true;
      }
    }
  }

  return false;
}

bool PropertyInspector::addDirectoryList(const char *listLabel, const char *directoryPath, std::string &selectedFilesName)
{
  if (addButton(listLabel))
  {
    openPopup(listLabel);
  }

  if (beginPopup(listLabel))
  {
    bool hit = addDirectoryList_rec(*this, directoryPath, selectedFilesName);
    if (hit)
    {
      return true;
      endPopup();
    }
    endPopup();
  }

  return false;
}

bool PropertyInspector::startList(const char *label, const std::string &currentSelected)
{
  return ImGui::BeginCombo(label, currentSelected.c_str());
}

bool PropertyInspector::selectableItem(const std::string &item, bool &isSelected)
{
  return ImGui::Selectable(item.c_str(), &isSelected);
}

void PropertyInspector::endList()
{
  ImGui::EndCombo();
}

void PropertyInspector::displayFloat(const char *label, float displayFloat)
{
  ImGui::Text(label, displayFloat);
}

PropertyInspector::List::List(PropertyInspector &inspector, const char *listLabel, std::string &currentlySelected)
    : m_inspector(inspector), m_currentlySelectedItem(currentlySelected)
{
  m_isOpen = m_inspector.startList(listLabel, currentlySelected);
}

PropertyInspector::List::~List()
{
  if (m_isOpen)
  {
    m_inspector.endList();
  }
}

bool PropertyInspector::List::addSelectableItem(const std::string &item)
{
  assert(m_isOpen && "make sure the list is open before adding items to it!");
  bool isSelected = (m_currentlySelectedItem == item);
  if (ImGui::Selectable(item.c_str(), isSelected))
  {
    m_currentlySelectedItem = item;
    if (isSelected)
    {
      ImGui::SetItemDefaultFocus();
    }
    return true;
  }

  return false;
}
