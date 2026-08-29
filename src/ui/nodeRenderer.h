#ifndef NODERENDERER_H
#define NODERENDERER_H

#include "cardRenderer.h" // Slot, SlotAlignment

#include <string>
#include <string_view>
#include <vector>

struct EventNode;

/**
 * @brief Renders a single EventNode as a fixed-size ASCII grid.
 *
 * Mirrors CardRenderer: slot-based layout into a bordered template of
 * constant width and height.
 */
class NodeRenderer
{
  public:
    NodeRenderer() = default;

    std::vector<std::string> renderNode(const EventNode& nodeToRender) const;

    /// @brief Returns the fixed width of the rendered node template.
    int getNodeTemplateWidth() const { return m_width; }
    /// @brief Returns the fixed height of the rendered node template.
    int getNodeTemplateHeight() const { return m_height; }

  private:
    void drawTemplate(std::vector<std::string>& grid) const;
    std::string fitText(Slot slot, std::string_view text) const;
    void writeSlot(std::vector<std::string>& grid, Slot slot, std::string_view formattedText) const;

    const int m_width{26};
    const int m_height{10};

    const char m_verticalBorder{'|'};
    const char m_horizontalBorder{'-'};

    Slot m_layerSlot{1, 2, m_width - 4, SlotAlignment::Center};

    std::vector<Slot> m_descriptionSlots{{4, 2, m_width - 4, SlotAlignment::Left},
                                         {5, 2, m_width - 4, SlotAlignment::Left},
                                         {6, 2, m_width - 4, SlotAlignment::Left},
                                         {7, 2, m_width - 4, SlotAlignment::Left}};
};

#endif // NODERENDERER_H