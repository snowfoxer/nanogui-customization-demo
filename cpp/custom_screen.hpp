/***************************************************************************************
 * This is free and unencumbered software released into the public domain.             *
 *                                                                                     *
 * Anyone is free to copy, modify, publish, use, compile, sell, or                     *
 * distribute this software, either in source code form or as a compiled               *
 * binary, for any purpose, commercial or non-commercial, and by any                   *
 * means.                                                                              *
 *                                                                                     *
 * In jurisdictions that recognize copyright laws, the author or authors               *
 * of this software dedicate any and all copyright interest in the                     *
 * software to the public domain. We make this dedication for the benefit              *
 * of the public at large and to the detriment of our heirs and                        *
 * successors. We intend this dedication to be an overt act of                         *
 * relinquishment in perpetuity of all present and future rights to this               *
 * software under copyright law.                                                       *
 *                                                                                     *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,                     *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                  *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.              *
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR                   *
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,               *
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR               *
 * OTHER DEALINGS IN THE SOFTWARE.                                                     *
 *                                                                                     *
 * For more information, please refer to <http://unlicense.org>                        *
 **************************************************************************************/
#pragma once

#include "custom_theme.hpp"
#include "gl_texture.hpp"

#include <nanogui/screen.h>

class CustomScreen : public nanogui::Screen {
public:
    CustomScreen(const nanogui::Vector2i &size)
        : nanogui::Screen(size, "NanoGUI Customization Demo") {

        /* Important! before you can use the custom fonts, even if you are not
         * setting the theme of a widget directly, you need to instantiate one
         * so that the fonts are actually loaded.  Alternatively, load the
         * custom font you want here in the constructor.  You would do this
         * instead if you don't desire to change the default fonts, but just
         * want a specific font face available to set for selected widgets.
         */
        mCustomTheme = new CustomTheme(mNVGContext);
        mFontawesomeTheme = new FontawesomeTheme(mNVGContext);

        // load an image for creating the image view in makeCompareWindow,
        // loadTexture() defined in gl_texture.hpp
        loadTexture("./icons/icon1.png", mImagesData);
    }

    /// Allow <ESCAPE> to close application.
    bool keyboardEvent(int key, int scancode, int action, int modifiers) override {
        if (Screen::keyboardEvent(key, scancode, action, modifiers))
            return true;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            setVisible(false);
            return true;
        }

        return false;
    }

    // leaving these public so that makeCompareWindow can access them, typically you
    // would want to mark things like this as protected...
    using imagesDataType = std::vector<std::pair<GLTexture, GLTexture::handleType>>;
    imagesDataType mImagesData;
    nanogui::ref<CustomTheme> mCustomTheme = nullptr;
    nanogui::ref<FontawesomeTheme> mFontawesomeTheme = nullptr;
};
