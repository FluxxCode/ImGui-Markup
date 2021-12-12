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
    this->control_window_.Reset();
    this->tests_.clear();

    if (!gui::FileManager::LoadFromFile("tests/control_window.ills",
        this->control_window_))
    {
        std::cerr << "Unable to load control window: " << std::endl <<
            gui::FileManager::GetLastError().ToString() << std::endl;

        this->ignore_control_window_ = true;
    }

    for (auto const& entry : fs::recursive_directory_iterator(
        this->test_folder_))
    {
        if (entry.path().extension() != ".ill")
            continue;

        gui::GlobalObject obj;
        if (!gui::FileManager::LoadFromFile(entry.path().string(), obj))
        {
            std::cerr << "Unable to load test " << entry.path() << ":\n" <<
                gui::FileManager::GetLastError().ToString() << std::endl;

            continue;
        }

        this->tests_.push_back(obj);
    }
}

void MainState::UpdateControlWindow()
{
    gui::Button* btn = dynamic_cast<gui::Button*>(
        this->control_window_.GetChild("btn_reload").get());

    if (btn->IsPressed())
        this->Init();

    this->control_window_.Update();
}
