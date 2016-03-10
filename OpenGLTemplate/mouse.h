#pragma once

namespace input {

    class Mouse
    {
    public:
        Mouse();
        ~Mouse();
        static void getPosition(double *x, double *y);
        static bool getButtonPressed(int button);
    };

} // namespace input

