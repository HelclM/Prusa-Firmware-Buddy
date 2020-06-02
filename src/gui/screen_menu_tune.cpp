// screen_menu_tune.cpp

#include "gui.h"
#include "screen_menu.hpp"
#include "marlin_client.h"
#include "MItem_print.hpp"
#include "MItem_tools.hpp"
#include "MItem_menus.hpp"

#pragma pack(push, 1)

/*****************************************************************************/
//parent alias
using parent = screen_menu_data_t<false, true, false, MI_RETURN, MI_SPEED, MI_NOZZLE,
    MI_HEATBED, MI_PRINTFAN, MI_FLOWFACT, MI_BABYSTEP, MI_M600, MI_LAN_SETTINGS, MI_VERSION_INFO,
#ifdef _DEBUG
    MI_TEST,
#endif //_DEBUG
    MI_MESSAGES>;

class ScreenMenuTune : public parent {
public:
    constexpr static const char *label = "TUNE";
    static void Init(screen_t *screen);
    static int CEvent(screen_t *screen, window_t *window, uint8_t event, void *param);
};
#pragma pack(pop)

/*****************************************************************************/
//static member method definition
void ScreenMenuTune::Init(screen_t *screen) {
    marlin_update_vars(MARLIN_VAR_MSK_TEMP_TARG | MARLIN_VAR_MSK(MARLIN_VAR_Z_OFFSET) | MARLIN_VAR_MSK(MARLIN_VAR_FANSPEED) | MARLIN_VAR_MSK(MARLIN_VAR_PRNSPEED) | MARLIN_VAR_MSK(MARLIN_VAR_FLOWFACT));
    Create(screen, label);
}

int ScreenMenuTune::CEvent(screen_t *screen, window_t *window, uint8_t event, void *param) {
    ScreenMenuTune *const ths = reinterpret_cast<ScreenMenuTune *>(screen->pdata);

    if (
        marlin_all_axes_homed() && marlin_all_axes_known() && (marlin_command() != MARLIN_CMD_G28) && (marlin_command() != MARLIN_CMD_G29) && (marlin_command() != MARLIN_CMD_M109) && (marlin_command() != MARLIN_CMD_M190)) {
        ths->menu.GetItem(7)->Enable();
    } else {
        ths->menu.GetItem(7)->Disable();
    }

    return ths->Event(window, event, param);
}

screen_t screen_menu_tune = {
    0,
    0,
    ScreenMenuTune::Init,
    ScreenMenuTune::CDone,
    ScreenMenuTune::CDraw,
    ScreenMenuTune::CEvent,
    sizeof(ScreenMenuTune), //data_size
    0,                      //pdata
};

extern "C" screen_t *const get_scr_menu_tune() { return &screen_menu_tune; }
