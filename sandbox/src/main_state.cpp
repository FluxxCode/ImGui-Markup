#include "sapch.h"
#include "main_state.h"

MainState::MainState()
{
    this->Init();
}

void MainState::Update()
{
    this->UpdateControlWindow();

    for (unsigned int i = 0; i < this->tests_.size(); i++)
        igm::Update(this->tests_[i]);
}

void MainState::Render()
{ }

void MainState::Init()
{
    // NOTE: This will be removed later and changed to a proper test system.

    this->tests_.clear();

    bool result = false;

    this->control_window_ = igm::ParseFile(this->control_window_path_, &result);
    if (!result)
    {
       std::cerr << "Unable to load control window: " << std::endl <<
           igm::GetLastResult(this->control_window_).message << std::endl;
    }

    for (auto const& entry : fs::directory_iterator(
       this->test_folder_))
    {
       if (entry.path().extension() != ".igm")
           continue;

       this->tests_.emplace_back(
           igm::ParseFile(entry.path().string().c_str(), &result));

       if (!result)
       {
            std::cerr << "Unable to load test " << entry.path() << ":\n" <<
                igm::GetLastResult(this->tests_.back()).message << std::endl;

           continue;
       }
    }
}

void MainState::UpdateControlWindow()
{
    if (igm::IsItemPressed(this->control_window_, "btn_reload"))
        this->Init();

    igm::Update(this->control_window_);
}
