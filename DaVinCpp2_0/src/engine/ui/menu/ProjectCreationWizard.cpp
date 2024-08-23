#include "ProjectCreationWizard.h"
#include <ui/menu/SelectionMenu.h>
#include <ui/menu/SwitchElement.h>
#include <ui/menu/ScrollSelectionElement.h>
#include <ui/menu/TextFieldElement.h>
#include <ui/menu/NumberFieldElement.h>
#include <ui/menu/SelectFilepathButton.h>

namespace davincpp
{
    const char* ProjectCreationWizard::PROJECT_DIRECTORY            = "project_directory";
    const char* ProjectCreationWizard::PROJECT_NAME                 = "project_name";
    const char* ProjectCreationWizard::PROJECT_SUPPORTED_VERSION    = "project_supported_version";
    const char* ProjectCreationWizard::PROJECT_VSYNC                = "project_vsync";
    const char* ProjectCreationWizard::PROJECT_SHOW_CURSOR          = "project_show_cursor";
    const char* ProjectCreationWizard::PROJECT_RESOLUTION_WIDTH     = "project_resolution_width";
    const char* ProjectCreationWizard::PROJECT_RESOLUTION_HEIGHT    = "project_resolution_height";
    const char* ProjectCreationWizard::PROJECT_PIXEL_WIDTH          = "project_pixel_width";
    const char* ProjectCreationWizard::PROJECT_PIXEL_HEIGHT         = "project_pixel_height";

    void ProjectCreationWizard::onSwitchPage(SelectionMenu* selectionMenu)
    {
        for (const std::shared_ptr<MenuElement>& menuElement : m_MenuElements) {
            menuElement->onSwitchPage(selectionMenu);
        }
    }

    void ProjectCreationWizard::onUpdate(SelectionMenu* selectionMenu, int input)
    {
        m_SelectedElement->onUpdate(selectionMenu, input);
    }


    std::pair<std::filesystem::path, ProjectConfig> ProjectCreationWizard::castProjectData() const
    {
        try {
            return {
                    getMenuElementByTag<SelectFilepathButton>(PROJECT_NAME)->getFilePath(), {
                    {},
                    {},
                    getMenuElementByTag<ScrollSelectionElement>(PROJECT_SUPPORTED_VERSION)->getSelectionOption(),
                    getMenuElementByTag<TextFieldElement>(PROJECT_NAME)->getEnteredText(),
                    glm::uvec2(
                        getMenuElementByTag<NumberFieldElement>(PROJECT_RESOLUTION_WIDTH)->getValue(),
                        getMenuElementByTag<NumberFieldElement>(PROJECT_RESOLUTION_HEIGHT)->getValue()
                    ),
                    glm::uvec2(
                        getMenuElementByTag<NumberFieldElement>(PROJECT_PIXEL_WIDTH)->getValue(),
                        getMenuElementByTag<NumberFieldElement>(PROJECT_PIXEL_HEIGHT)->getValue()
                    ),
                    getMenuElementByTag<SwitchElement>(PROJECT_VSYNC)->getState(),
                    getMenuElementByTag<SwitchElement>(PROJECT_SHOW_CURSOR)->getState(),
                }
            };
        }
        catch (std::runtime_error&) {
            return {};
        }
    }
}
