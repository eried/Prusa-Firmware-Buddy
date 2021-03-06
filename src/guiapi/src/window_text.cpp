// window_text.c
#include "window_text.hpp"
#include "gui.hpp"

void window_text_init(window_text_t *window) {
    window->color_back = gui_defaults.color_back;
    window->color_text = gui_defaults.color_text;
    window->font = gui_defaults.font;
    window->text = string_view_utf8::MakeNULLSTR();
    window->padding = gui_defaults.padding;
    window->alignment = gui_defaults.alignment;
}

void window_text_draw(window_text_t *window) {
    if (((window->flg & (WINDOW_FLG_INVALID | WINDOW_FLG_VISIBLE)) == (WINDOW_FLG_INVALID | WINDOW_FLG_VISIBLE))) {
        render_text_align(window->rect,
            window->text,
            window->font,
            (window->flg & WINDOW_FLG_FOCUSED) ? window->color_text : window->color_back,
            (window->flg & WINDOW_FLG_FOCUSED) ? window->color_back : window->color_text,
            window->padding,
            window->alignment);
        window->flg &= ~WINDOW_FLG_INVALID;
    }
}

const window_class_text_t window_class_text = {
    {
        WINDOW_CLS_TEXT,
        sizeof(window_text_t),
        (window_init_t *)window_text_init,
        0,
        (window_draw_t *)window_text_draw,
        0,
    },
};

void window_text_t::SetText(string_view_utf8 txt) {
    text = txt;
    Invalidate();
}

void window_text_t::SetTextColor(color_t clr) {
    color_text = clr;
    Invalidate();
}

void window_text_t::SetPadding(padding_ui8_t padd) {
    padding = padd;
    Invalidate();
}

void window_text_t::SetAlignment(uint8_t alignm) {
    alignment = alignm;
    Invalidate();
}
