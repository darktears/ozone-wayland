// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_OZONE_WEB_UI_H_
#define CHROME_BROWSER_UI_OZONE_WEB_UI_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "ui/base/ime/linux/linux_input_method_context.h"
#include "ui/events/linux/text_edit_key_bindings_delegate_auralinux.h"
#include "ui/gfx/color_utils.h"
#include "ui/gfx/font_render_params.h"
#include "ui/gfx/geometry/insets.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/pango_util.h"
#include "ui/views/border.h"
#include "ui/views/controls/button/label_button.h"
#include "ui/views/controls/button/label_button_border.h"
#include "ui/views/linux_ui/linux_ui.h"
#include "ui/views/window/frame_buttons.h"

class SkBitmap;

namespace gfx {
class Image;
}

using ui::TextEditCommandAuraLinux;

namespace views {
class Border;
class LabelButton;
class View;
class NativeThemeChangeObserver;
class WindowButtonOrderObserver;
// Interface to Wayland desktop features.
//
class OzoneWebUI : public views::LinuxUI {
 public:
  OzoneWebUI();
  virtual ~OzoneWebUI();

  // ui::LinuxInputMethodContextFactory:
  scoped_ptr<ui::LinuxInputMethodContext> CreateInputMethodContext(
      ui::LinuxInputMethodContextDelegate* delegate) const override;

  // gfx::LinuxFontDelegate:
  gfx::FontRenderParams GetDefaultFontRenderParams() const override;
  scoped_ptr<gfx::ScopedPangoFontDescription>
      GetDefaultPangoFontDescription() const override;
  double GetFontDPI() const override;

  // ui::LinuxShellDialog:
  ui::SelectFileDialog* CreateSelectFileDialog(
      ui::SelectFileDialog::Listener* listener,
      ui::SelectFilePolicy* policy) const override;

  // ui::LinuxUI:
  void Initialize() override;

  // These methods are not needed
  gfx::Image GetThemeImageNamed(int id) const override;
  bool GetColor(int id, SkColor* color) const override;
  bool HasCustomImage(int id) const override;
  SkColor GetFocusRingColor() const override;
  SkColor GetThumbActiveColor() const override;
  SkColor GetThumbInactiveColor() const override;
  SkColor GetTrackColor() const override;
  SkColor GetActiveSelectionBgColor() const override;
  SkColor GetActiveSelectionFgColor() const override;
  SkColor GetInactiveSelectionBgColor() const override;
  SkColor GetInactiveSelectionFgColor() const override;
  double GetCursorBlinkInterval() const override;
  ui::NativeTheme* GetNativeTheme(aura::Window* window) const override;
  void SetNativeThemeOverride(const NativeThemeGetter& callback) override;
  bool GetDefaultUsesSystemTheme() const override;
  void SetDownloadCount(int count) const override;
  void SetProgressFraction(float percentage) const override;
  bool IsStatusIconSupported() const override;
  scoped_ptr<StatusIconLinux> CreateLinuxStatusIcon(
      const gfx::ImageSkia& image,
      const base::string16& tool_tip) const override;
  gfx::Image GetIconForContentType(const std::string& content_type,
                                   int size) const override;
  scoped_ptr<Border> CreateNativeBorder(
      views::LabelButton* owning_button,
      scoped_ptr<views::LabelButtonBorder> border) override;
  void AddWindowButtonOrderObserver(
      WindowButtonOrderObserver* observer) override;
  void RemoveWindowButtonOrderObserver(
      WindowButtonOrderObserver* observer) override;
  bool UnityIsRunning() override;
  NonClientMiddleClickAction GetNonClientMiddleClickAction() override;
  void NotifyWindowManagerStartupComplete() override;

  bool MatchEvent(const ui::Event& event,
                  std::vector<TextEditCommandAuraLinux>* commands) override;

 private:
  gfx::FontRenderParams params_;
  DISALLOW_COPY_AND_ASSIGN(OzoneWebUI);
};

}  // namespace views

views::LinuxUI* BuildWebUI();

#endif  // CHROME_BROWSER_UI_OZONE_WEB_UI_H_
