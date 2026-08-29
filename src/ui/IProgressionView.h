#ifndef IPROGRESSIONVIEW_H
#define IPROGRESSIONVIEW_H

#include <string_view>
#include <vector>

struct EventNode;

class IProgressionView
{
  public:
    virtual ~IProgressionView() = default;

    virtual void showProgressionTitle() const = 0;
    virtual void showCurrentNode(std::string_view previewDescription, int layer) const = 0;

    virtual void showPathOptions(const std::vector<const EventNode*>& optionsToRender) const = 0;
    virtual int askPlayerPath(int limit) = 0;

    virtual void showSelectedPath(std::string_view previewDescription) const = 0;
    virtual void showEndOfProgression() const = 0;

  private:
};

#endif // IPROGRESSIONVIEW_H