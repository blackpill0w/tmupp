#include <functional>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

int main() {
  using namespace ftxui;
  auto screen = ScreenInteractive::Fullscreen();

  std::vector<std::string> left_menu_entries = {
      "0%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%",
  };
  std::vector<std::string> right_menu_entries = {
      "0%", "1%", "2%", "3%", "4%", "5%", "6%", "7%", "8%", "9%", "10%",
  };

  auto menu_option     = MenuOption();
  menu_option.on_enter = screen.ExitLoopClosure();

  int left_menu_selected  = 0;
  int right_menu_selected = 0;
  Component left_menu_    = Menu(&left_menu_entries, &left_menu_selected, menu_option);
  Component right_menu_   = Menu(&right_menu_entries, &right_menu_selected, menu_option);

  Component container = Container::Horizontal({
      left_menu_,
      right_menu_,
  });

  Component *r = nullptr;

  container |= CatchEvent([&](Event e) {
    if (e.is_character()) {
      if (e.character() == "a") {
        left_menu_entries[0] = "Ayy!";
        return true;
      } else if (e.character() == "m") {
        container = Container::Vertical({left_menu_, right_menu_});
        screen.Exit();
        screen.Loop(*r);
      } else if (e.character() == "q") {
        screen.Exit();
        return true;
      }
    }
    return false;
  });

  auto music_view_renderer = Renderer(container, [&] {
    int sum = left_menu_selected * 10 + right_menu_selected;
    return vbox({
               // -------- Top panel --------------
               hbox({
                   // -------- Left Menu --------------
                   vbox({
                       hcenter(bold(text("Percentage by 10%"))),
                       separator(),
                       left_menu_->Render(),
                   }) | flex_shrink,
                   separator(),
                   // -------- Right Menu --------------
                   vbox({
                       hcenter(bold(text("Percentage by 1%"))),
                       separator(),
                       right_menu_->Render(),
                   }) | flex,
                   separator(),
               }) | flex_grow,
               separator(),
               // -------- Bottom panel --------------
               vbox({
                   hbox({
                       text(" gauge : "),
                       gauge(sum / 100.0),
                   }),
                   hbox({
                       text("  text : "),
                       text(std::to_string(sum) + " %"),
                   }),
               }),
           }) |
           border;
  });

  auto add_mdir_button = Button("Add Music Directory", [&] {});

  auto settings_layout = Container::Vertical({add_mdir_button});
  auto settings_view_renderer =
    Renderer(settings_layout, [&] { return center(vbox(add_mdir_button->Render())); });

  auto music_view_button = Button("Music", [&] { screen.Loop(music_view_renderer); });
  auto settings_button   = Button("Settings", [&] { screen.Loop(settings_view_renderer); });
  auto quit_button       = Button("Quit", screen.ExitLoopClosure());

  auto layout             = Container::Vertical({music_view_button, settings_button, quit_button});
  auto main_menu_renderer = Renderer(layout, [&] {
    return center(vbox(music_view_button->Render(), settings_button->Render(), quit_button->Render()));
  });

  screen.Loop(main_menu_renderer);
}
