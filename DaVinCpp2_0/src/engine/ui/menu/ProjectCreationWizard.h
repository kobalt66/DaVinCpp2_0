#pragma once
#include <ui/menu/MenuPage.h>
#include <gameprojects/ProjectConfig.h>

namespace davincpp
{
    class ProjectCreationWizard : public MenuPage
    {
    public:
        template<MenuElementPtr ...Args> explicit ProjectCreationWizard(std::string_view title, Args... args)
            : MenuPage(title, args...)
        { }

        void onSwitchPage(SelectionMenu* selectionMenu) override;
        void onUpdate(SelectionMenu* selectionMenu, int input) override;

        [[nodiscard]] std::pair<std::filesystem::path, ProjectConfig> castProjectData() const;

    public:
        static const char* PROJECT_DIRECTORY;
        static const char* PROJECT_NAME;
        static const char* PROJECT_SUPPORTED_VERSION;
        static const char* PROJECT_VSYNC;
        static const char* PROJECT_SHOW_CURSOR;
        static const char* PROJECT_RESOLUTION_WIDTH;;
        static const char* PROJECT_RESOLUTION_HEIGHT;
        static const char* PROJECT_PIXEL_WIDTH;
        static const char* PROJECT_PIXEL_HEIGHT;
    };
};
