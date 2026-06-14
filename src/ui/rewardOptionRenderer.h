#ifndef REWARDOPTIONRENDERER_H
#define REWARDOPTIONRENDERER_H

#include "cardRenderer.h"
#include "cards/cardInstance.h"
#include "factories/ICardFactory.h"
#include "game_events/rewards/rewardOption.h"

#include <string>

class RewardOptionRenderer
{
  public:
    RewardOptionRenderer(ICardFactory& cardFactory);

    std::vector<std::string> renderRewardOption(const RewardOption& optionToRender) const;

    /// @brief Returns the fixed width of the rendered reward template.
    int getRewardOptionTemplateWidth() const { return m_width; }

  private:
    CardRenderer m_cardRenderer;
    ICardFactory& m_cardFactory;

    /// @brief Draws the static reward option template (borders, labels) into the grid.
    void drawTemplate(std::vector<std::string>& grid) const;

    /**
     * @brief Fits text into a slot width using the slot alignment.
     *
     * If the text exceeds the slot width, it is truncated. If it is shorter,
     * it is padded with spaces according to the alignment.
     *
     * @param currentSlot Slot describing width and alignment.
     * @param text Input text to format.
     * @return String of currentSlot.maxWidth characters.
     */
    std::string fitText(Slot currentSlot, std::string_view text) const;

    /**
     * @brief Writes pre-formatted text into the specified slot in the grid.
     *
     * @param grid Target grid to modify.
     * @param slot Destination slot coordinates and width.
     * @param formattedText Text already formatted to slot.maxWidth characters.
     */
    void writeSlot(std::vector<std::string>& grid, Slot slot, std::string_view formattedText) const;

    void writeCardInRewardOptionSlot(std::vector<std::string>& grid, Slot slot,
                                     const CardInstance& cardToRender) const;
    /**
     * @brief Appends a word to a line, inserting a single space if needed.
     */
    static void appendWord(std::string& line, std::string_view word);

    /**
     * @brief Appends a word to a line, inserting a separator if needed.
     */
    static void appendSeparator(std::string& line, std::string_view word);

    /**
     * @brief Splits input text into one or two lines that fit the given slot width.
     *
     * Words are kept intact when possible; overflow is placed on the second line.
     *
     * @param rewardOptionName Input text to split (e.g., reward option name or description).
     * @param currentSlot Slot providing the maximum width.
     * @return NameLayout containing the first line and optional second line.
     */
    NameLayout drawLayout(std::string_view rewardOptionName, Slot currentSlot) const;
    std::vector<std::string> drawDescriptionLayout(std::string_view rewardOptionDescription,
                                                   Slot currentSlot) const;

    const int m_width{44};
    const int m_height{23};

    const int m_nameWidth{16};
    const int m_nameColumn{m_width / 2 - m_nameWidth / 2};

    const int m_cardWidth{m_cardRenderer.getCardTemplateWidth()};
    const int m_cardColumn{m_width / 2 - m_cardWidth / 2};

    const char m_padding{' '};
    const char m_verticalBorder{'|'};
    const char m_horizontalBorder{'-'};

    const int m_descriptionMaxLines{4};

    Slot m_firstNameSlot{1, m_nameColumn, m_nameWidth, SlotAlignment::Center};
    Slot m_secondNameSlot{2, m_nameColumn, m_nameWidth, SlotAlignment::Center};

    Slot m_cardSlot{9, m_cardColumn, m_cardWidth, SlotAlignment::Center};

    // Slot m_effectsSumSlot{7, 3, 18, SlotAlignment::Center};

    std::vector<Slot> m_descriptionSlots{{5, 2, m_width - 4, SlotAlignment::Left},
                                         {6, 2, m_width - 4, SlotAlignment::Left},
                                         {7, 2, m_width - 4, SlotAlignment::Left},
                                         {8, 2, m_width - 4, SlotAlignment::Left}};
};

#endif // REWARDOPTIONRENDERER_H
