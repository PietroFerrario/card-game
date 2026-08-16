#ifndef CARDRENDERER_H
#define CARDRENDERER_H

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

class CardInstance;
struct CardParams;

/**
 * @brief Text alignment used when fitting content into a fixed-width slot.
 */
enum class SlotAlignment
{
    Left,
    Center,
    Right
};

/**
 * @brief Defines a rectangular text slot within a rendered card grid.
 *
 * A Slot identifies a row/column position and a fixed width. Text written to the slot
 * is pre-formatted to maxWidth characters using the specified alignment.
 */
struct Slot
{
    int rowIndex;
    int columnIndex;
    int maxWidth;
    SlotAlignment alignment;
};

/**
 * @brief Two-line text layout produced by splitting a string to fit a slot width.
 *
 * The second line is present only when the input text does not fit on one line.
 */
struct NameLayout
{
    std::string firstName;
    std::optional<std::string> secondName;
};

/**
 * @brief Renders a CardInstance as a fixed-size ASCII grid.
 *
 * CardRenderer produces a vector of strings representing a bordered card template
 * populated with the card's name, stats, and description. Layout is slot-based:
 * text is fit to fixed-width slots and written into the grid.
 *
 * The output grid has a constant width and height defined by the renderer.
 */
class CardRenderer
{
  public:
    CardRenderer() = default;

    /**
     * @brief Renders the given card into an ASCII grid.
     *
     * @param cardToRender Card instance to render.
     * @return Vector of strings where each entry is one row of the card.
     */
    std::vector<std::string> renderCard(const CardInstance& cardToRender) const;

    /// @brief Returns the fixed width of the rendered card template.
    int getCardTemplateWidth() const { return m_width; }

  private:
    /// @brief Draws the static card template (borders, labels) into the grid.
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
     * @param cardName Input text to split (e.g., card name or description).
     * @param currentSlot Slot providing the maximum width.
     * @return NameLayout containing the first line and optional second line.
     */
    NameLayout drawLayout(std::string_view cardName, Slot currentSlot) const;

    std::string drawEffects(const CardParams& cardParams) const;

    const int m_width{26};
    const int m_height{15};

    const int m_nameWidth{16};
    const int m_nameColumn{m_width / 2 - m_nameWidth / 2};

    const char m_padding{' '};
    const char m_verticalBorder{'|'};
    const char m_horizontalBorder{'-'};

    Slot m_firstNameSlot{1, m_nameColumn, m_nameWidth, SlotAlignment::Center};
    Slot m_secondNameSlot{2, m_nameColumn, m_nameWidth, SlotAlignment::Center};

    Slot m_atkLabelSlot{5, 2, 6, SlotAlignment::Left};
    Slot m_defLabelSlot{5, m_width - 10, 6, SlotAlignment::Left};

    Slot m_damageValueSlot{5, 8, 2, SlotAlignment::Right};
    Slot m_armorValueSlot{5, m_width - 4, 2, SlotAlignment::Right};
    Slot m_effectsSumSlot{7, 3, 18, SlotAlignment::Center};
    std::vector<Slot> m_descriptionSlot{{9, 2, m_width - 4, SlotAlignment::Left},
                                        {10, 2, m_width - 4, SlotAlignment::Left},
                                        {11, 2, m_width - 4, SlotAlignment::Left},
                                        {12, 2, m_width - 4, SlotAlignment::Left}};
};

#endif // CARDRENDERER_H
