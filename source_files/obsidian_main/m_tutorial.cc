//------------------------------------------------------------------------
//  Tutorial Window
//------------------------------------------------------------------------
//
//  OBSIDIAN Level Maker
//
//  Copyright (C) 2022 The OBSIDIAN Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#include "fmt/format.h"
#include "hdr_fltk.h"
#include "hdr_ui.h"
#include "headers.h"
#include "lib_util.h"
#include "main.h"

class UI_Tutorial_Window : public Fl_Window {
   public:
    bool want_quit;

   public:
    UI_Tutorial_Window(int W, int H, const char *label = NULL);

    virtual ~UI_Tutorial_Window() {}

    bool WantQuit() const { return want_quit; }

   public:
    // FLTK virtual method for handling input events.
    int handle(int event) {
        if (event == FL_KEYDOWN || event == FL_SHORTCUT) {
            int key = Fl::event_key();

            if (key == FL_Escape) {
                want_quit = true;
                return 1;
            }

            // eat all other function keys
            if (FL_F + 1 <= key && key <= FL_F + 12) {
                return 1;
            }
        }

        return Fl_Window::handle(event);
    }

   private:
    static void callback_Quit(Fl_Widget *w, void *data) {
        UI_Tutorial_Window *that = (UI_Tutorial_Window *)data;

        that->want_quit = true;
    }

    Fl_Wizard *tutorial_wiz;

    static void wiz_back(Fl_Widget*, void *data) {
        Fl_Wizard *that = (Fl_Wizard *)data;
        that->prev();
        that->redraw();
    }

     static void wiz_next(Fl_Widget*, void *data) {
        Fl_Wizard *that = (Fl_Wizard *)data;
        that->next();
        that->redraw();
    }
};

//
// Constructor
//
UI_Tutorial_Window::UI_Tutorial_Window(int W, int H, const char *label)
    : Fl_Window(W, H, label), want_quit(false) {
    // non-resizable
    size_range(W, H, W, H);

    callback(callback_Quit, this);

    tutorial_wiz = new Fl_Wizard(0, 0, W, H);

    // Wizard: page 1
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Help_View *out = new Fl_Help_View(10,H/2,W-20,H/2-80);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Welcome to OBSIDIAN Level Maker! This quick tutorial will teach you\
 the basics of navigating the user interface.</center>");
        out->box(FL_FLAT_BOX);
        g->end();
    }
    // Wizard: page 2
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial1);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Game Settings, in the upper left area of the program window, contains all you \
need to build your very first WAD. Select the Game you would like to build a WAD for, the Engine that \
it will be played on, the Length (number of maps) of the WAD, and the Theme that you would like it to have. \
Once you press 'Build', you will be prompted to choose a location and filename for your WAD. After that, your \
WAD will be generated and saved to the location that you specified.\n\nNOTE: If you select 'Vanilla Doom' for the \
engine, an alternate map generator will be used to create your WAD. Although this WAD will be compatible \
with all versions of Doom, it is much simpler in nature than the maps made by Obsidian's main generator.</center>");
        g->end();
    }
    // Wizard: page 3
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial2);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>At some point, you will want to have more control over the contents of the \
WADs that you generate. This is where modules come into play. Modules are groups of options that can be \
changed to fine-tune your experience. Most modules are optional, and will need to be enabled or disabled \
accordingly.</center>");
        g->end();
    }
    // Wizard: page 3
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial3);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Some modules do not have any additional options to configure, \
and only need to be enabled or disabled. To enable them, simply click the checkbox to the \
left of their name. To disable them, clear the same checkbox by clicking it again.</center>");
        g->end();
    }
    // Wizard: page 3
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial4);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Other modules will have options that you can adjust after you enable them. These modules will \
have a + symbol next to their name instead of a checkbox. To enable them, click the + symbol. The + will turn into a - \
and the module will expand to show its options. Once you have adjusted these options, you MUST LEAVE THE MODULE EXPANDED for them \
to take effect. To disable the module, click the - symbol. It will collapse and the - will turn back into a +</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial5);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Module options come in three different flavors: Checkboxes, drop-down menus, and sliders. Checkboxes and drop-down menus \
are fairly self-explanatory, but we will cover some of the more advanced slider functions.</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial6);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Some sliders will have an inverted triangle icon in the top right corner. Clicking this will show a menu \
with various choices. With the exception of 'Use Slider Value', these will ignore the number that the slider is set to in favor of a different \
means of determining the related value.</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial7);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>All sliders will have a pair of brackets in the top right corner. Clicking these will open a dialog box where you \
can enter a value manually instead of using the slider handle or arrow buttons.</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial8);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>All module options will have a tooltip that is shown by hovering your cursor over the option title. In addition, there \
is a question mark icon in the top right corner of each option that can be clicked to open a window with a more detailed explanation.</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial9);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>Addons are a way to enhance the Obsidian experience further by adding new content, modules, and options. They come in the \
form of *.pk3 files that must be placed in the /addons folder of your Obsidian install. Once there, open the Addons window by pressing F3 or choosing \
File->Addon List from the program menu. A list of available addon files will be shown, and can be enabled or disabled via checkbox.\n\nGood sources for \
new addons are either <A HREF='https://github.com/GTD-Carthage/Obsidian-Addons'>the public Obsidian-Addons repo</A> or the #addon-files channel of our Discord.</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *next = new Fl_Button(W - 110, H - 35, 100, 25, "Next");
        next->box(button_style);
        next->visible_focus(0);
        next->color(BUTTON_COLOR);
        next->labelfont(font_style);
        next->labelcolor(FONT2_COLOR);
        next->callback(wiz_next, this->tutorial_wiz);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Box *pic = new Fl_Box(10,30,W-20,H/2-80);
        pic->box(FL_FLAT_BOX);
        pic->image(tutorial10);
        Fl_Help_View *out = new Fl_Help_View(10,30 + H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>If, for whatever reason, you receive an error while building, you can view Obsidian's logs by pressing F6 or \
selecting Help->View Logs from the program menu. From here, you can view and save the log contents to a file of your choosing. In addition, \
there is a LOGS.txt file with the same information that is stored in the same folder as obsidian.exe. This file is overwritten each time you \
start the program, so be sure to save this information elsewhere if you need to refer to it later! These logs are extremely important when \
seeking help or filing bug reports!</center>");
        g->end();
    }
    {
        Fl_Group *g = new Fl_Group(0,0,W,H);
        g->box(box_style);
        Fl_Button *done = new Fl_Button(W - 110, H - 35, 100, 25, "Finish");
        done->box(button_style);
        done->visible_focus(0);
        done->color(BUTTON_COLOR);
        done->labelfont(font_style);
        done->labelcolor(FONT2_COLOR);
        done->callback(callback_Quit, this);
        Fl_Button *back = new Fl_Button(W - 220, H - 35, 100, 25,"Back");
        back->box(button_style);
        back->visible_focus(0);
        back->color(BUTTON_COLOR);
        back->labelfont(font_style);
        back->labelcolor(FONT2_COLOR);
        back->callback(wiz_back, this->tutorial_wiz);
        Fl_Help_View *out = new Fl_Help_View(10, H/2,W-20,H/2-80);
        out->box(FL_FLAT_BOX);
        out->textfont(font_style);
        out->textsize(FL_NORMAL_SIZE + 2);
        out->value("<center>There are more options to explore within Obsidian, but this should be enough to get you started. \
The tutorial can be viewed again at any time by choosing Help->Tutorial from the program menu.\n\nIf you need more help, please ask in our \
Discord (invite link <A HREF='https://discord.gg/dfqCt9v'>https://discord.gg/dfqCt9v</A>) or check our wiki at \
<A HREF='https://github.com/dashodanger/Obsidian/wiki'>https://github.com/dashodanger/Obsidian/wiki</A>.\n\nGood luck in the \
infinite Hells!</center>");
        g->end();
    }
    tutorial_wiz->end();

    end();
}

void DLG_Tutorial(void) {
    int tutorial_w = kf_w(640);
    int tutorial_h = kf_h(480) + KF * 20;

    UI_Tutorial_Window *tutorial_window =
        new UI_Tutorial_Window(tutorial_w, tutorial_h, _("OBSIDIAN Tutorial"));

    tutorial_window->want_quit = false;
    tutorial_window->show();

    // run the GUI until the user closes
    while (!tutorial_window->WantQuit()) {
        Fl::wait();
    }

    delete tutorial_window;
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
