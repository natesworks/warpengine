#include "Object.h"
#include "../Point.h"
#include "../RGB.h"

class Line : public Object
{
public:
    Point start;
    Point end;

    Line(Point start, Point end, RGB color)
        : Object(color), start(start), end(end) {}

    std::unique_ptr<Object> clone() const override
    {
        return std::make_unique<Line>(*this);
    }
};
