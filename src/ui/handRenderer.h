#ifndef HANDRENDER_H
#define HANDRENDER_H

#include "cardRenderer.h"

#include <memory>
#include <vector>

class CardInstance;

/**
 * @brief Rendered representation of a hand for terminal output.
 *
 * A hand may be rendered on one or two rows depending on the number of cards.
 * Each row is represented as an ASCII grid (vector of strings).
 */
struct RenderedHand
{
    std::optional<std::vector<std::string>> firstRow;
    std::optional<std::vector<std::string>> secondRow;
};

/**
 * @brief Renders a hand of cards as one or two rows of ASCII cards.
 *
 * HandRenderer uses CardRenderer to render individual cards, then horizontally
 * concatenates them with a fixed gap. A selection index line is appended below
 * each rendered row to support terminal input by card number.
 */
class HandRenderer
{
  public:
    /**
     * @brief Renders the given hand into one or two terminal rows.
     *
     * If the hand is empty, returns a RenderedHand with no rows set.
     * For large hands, the cards are split across two rows.
     *
     * @param handToRender Non-owning pointers to cards currently in hand.
     * @return RenderedHand containing one or two rendered rows.
     */
    RenderedHand renderHand(const std::vector<const CardInstance*>& handToRender);

    /**
     * @brief Renders a subrange of already-rendered cards into a single row.
     *
     * Concatenates the ASCII grids in the range [begin, end) and appends a
     * centered selection index line using indexBase for numbering.
     *
     * @param parsedHand Pre-rendered cards (each entry is a card grid).
     * @param begin First card index in parsedHand to render (inclusive).
     * @param end One-past-last card index in parsedHand to render (exclusive).
     * @param indexBase Offset used for display numbering (1-based labels are indexBase + i + 1).
     * @return A rendered row grid with an extra final line containing selection indices.
     */
    std::vector<std::string>
    renderMultipleCards(const std::vector<std::vector<std::string>>& parsedHand, size_t begin,
                        size_t end, size_t indexBase);

  private:
    CardRenderer m_cardRenderer{}; ///< Renders individual cards.

    std::string m_gap{"    "};     ///< Spacing inserted between rendered cards.
    const int m_cardLabelWidth{4}; ///< Fixed width of selection labels, e.g., "( 1)".
};

#endif // HANDRENDER_H