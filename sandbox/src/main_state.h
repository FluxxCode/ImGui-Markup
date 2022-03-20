#ifndef SANDBOX_SRC_MAIN_STATE_H_
#define SANDBOX_SRC_MAIN_STATE_H_

#include "imgui_markup.h"

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
    const char* test_folder_ = "tests";
    const char* control_window_path_ = "tests/control_window.igms";

    size_t control_window_;
    std::vector<size_t> tests_;

    // Functions
    void Init();

    void UpdateControlWindow();
};

#endif  // SANDBOX_SRC_MAIN_STATE_H_
