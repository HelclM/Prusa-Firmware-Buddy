#pragma once

#include "window.hpp"

enum class State_arrows_t : uint8_t { undef,
    up,
    down };

class WindowArrows : public window_aligned_t {
    static const uint16_t id_res_grey_up;
    static const uint16_t id_res_grey_down;
    static const uint16_t id_res_orange_up;
    static const uint16_t id_res_orange_down;

public:
    WindowArrows(window_t *parent, point_i16_t pt, padding_ui8_t padding = { 0, 0, 0, 0 });
    State_arrows_t GetState() const;
    void SetState(State_arrows_t s);

protected:
    virtual void unconditionalDraw() override;
};
