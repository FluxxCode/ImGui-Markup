#ifndef SANDBOX_SRC_MAIN_STATE_H_
#define SANDBOX_SRC_MAIN_STATE_H_

#include "imgui_layer.h"

class MainState
{
public:
    // Constructor
    MainState();

    // Functions
    void Update();
    void Render();

private:
    // Variables
    const std::string test_folder_ = "tests";

    gui::GlobalObject control_window_;
    bool ignore_control_window_ = false;

    std::vector<gui::GlobalObject> tests_;

    // Functions
    void Init();

    void UpdateControlWindow();
};

#endif  // SANDBOX_SRC_MAIN_STATE_H_
