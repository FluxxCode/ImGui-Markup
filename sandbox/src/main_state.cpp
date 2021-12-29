#include "sapch.h"
#include "main_state.h"

#include "imgui_layer.h"

MainState::MainState()
{
    this->Init();
}

void MainState::Update()
{
    if (!this->ignore_control_window_)
        this->UpdateControlWindow();

    for (unsigned int i = 0; i < this->tests_.size(); i++)
        this->tests_[i].Update();
}

void MainState::Render()
{ }

void MainState::Init()
{
    // NOTE: This will be removed later and changed to a proper test system.

    this->tests_.clear();

    gui::ParserResult result = gui::ParseFile(
       "tests/control_window.ills", this->control_window_);

    if (result.type_ != gui::ParserResultType::kSuccess)
    {
       std::cerr << "Unable to load control window: " << std::endl <<
           result.ToString() << std::endl;

       this->ignore_control_window_ = true;
    }

    for (auto const& entry : fs::recursive_directory_iterator(
       this->test_folder_))
    {
       if (entry.path().extension() != ".ill")
           continue;

       gui::GlobalObject obj;
       result = gui::ParseFile(entry.path().string().c_str(), obj);

       if (result.type_ != gui::ParserResultType::kSuccess)
       {
           std::cerr << "Unable to load test " << entry.path() << ":\n" <<
               result.ToString() << std::endl;

           continue;
       }

       this->tests_.push_back(obj);
    }
}

void MainState::UpdateControlWindow()
{
    // NOTE: The entire access-system of objects will be reworked.
    //       The plan is to have simple functions without having to
    //       manually cast the objects. E.g.:
    //       if (control_window.IsPressed("btn_reload"))

    gui::Button* btn = dynamic_cast<gui::Button*>(
       this->control_window_.GetChild("btn_reload").get());

    if (btn->IsPressed())
       this->Init();

    this->control_window_.Update();
}
