#include "sapch.h"
#include "main_state.h"

// NOTE: Implementation currently removed on api_rework branch.
//       New implementation will be added later to this branch.

MainState::MainState()
{
    // this->Init();
}

void MainState::Update()
{
    // if (!this->ignore_control_window_)
    //     this->UpdateControlWindow();

    // for (unsigned int i = 0; i < this->tests_.size(); i++)
    //     this->tests_[i].Update();
}

void MainState::Render()
{ }

void MainState::Init()
{
    // NOTE: This will be removed later and changed to a proper test system.

    // this->tests_.clear();

    // gui::ParserResult result = gui::ParseFile(
    //    "tests/control_window.ills", this->control_window_);

    // if (result.type_ != gui::ParserResultType::kSuccess)
    // {
    //    std::cerr << "Unable to load control window: " << std::endl <<
    //        result.ToString() << std::endl;

    //    this->ignore_control_window_ = true;
    // }

    // for (auto const& entry : fs::directory_iterator(
    //    this->test_folder_))
    // {
    //    if (entry.path().extension() != ".ill")
    //        continue;

    //    this->tests_.emplace_back(gui::GlobalObject());
    //    result = gui::ParseFile(entry.path().string().c_str(), this->tests_.back());

    //    if (result.type_ != gui::ParserResultType::kSuccess)
    //    {
    //         std::cerr << "Unable to load test " << entry.path() << ":\n" <<
    //             result.ToString() << std::endl;

    //         this->tests_.pop_back();

    //        continue;
    //    }
    // }
}

void MainState::UpdateControlWindow()
{
    // if (this->control_window_.IsPressed("btn_reload"))
    //     this->Init();

    // this->control_window_.Update();
}
