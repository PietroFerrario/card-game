#ifndef IOTEXT_H
#define IOTEXT_H

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class RenderedHand;

/**
 * @brief Text-based input/output interface for terminal interaction.
 *
 * IOText provides an abstraction over input and output streams used by the terminal UI.
 * It is responsible only for printing text and rendered grids, and for reading user input.
 *
 * IOText does not implement any game logic or rendering logic;
 */
class IOText
{

  public:
    /**
     * @brief Constructs an IOText interface using the given streams.
     *
     * @param out Output stream used for printing.
     * @param in Input stream used for reading user input.
     */
    IOText(std::ostream& out, std::istream& in) : m_out{out}, m_in{in} {}

    /// @brief Prints a line followed by a newline.
    void println(std::string_view msg);
    /// @brief Prints a line (with newline).
    void print(std::string_view msg) const;

    /// @brief Reads a line of input into the given string.
    void getln(std::string& line);

    /**
     * @brief Prints a prompt and reads a line of input.
     *
     * @param line Output string receiving the input.
     * @param prompt Prompt text printed before reading input.
     */
    void promptln(std::string& line, std::string_view prompt);

    /**
     * @brief Prints a rendered card grid to the output.
     *
     * @param cardToPrintGrid ASCII grid representing a single card or row of cards.
     */
    void printCards(const std::vector<std::string>& cardToPrintGrid);

    /**
     * @brief Prints a rendered hand to the output.
     *
     * One or two rows are printed depending on the contents of RenderedHand.
     *
     * @param handToPrint Rendered hand structure to print.
     */
    void printHand(const RenderedHand& handToPrint);

  private:
    std::ostream& m_out; ///< Output stream used for printing.
    std::istream& m_in;  ///< Input stream used for reading input.
};

#endif // IOTEXT_H