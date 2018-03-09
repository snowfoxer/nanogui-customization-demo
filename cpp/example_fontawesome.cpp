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

/* Developer note: need to make a change to this file?
 * Please raise an Issue on GitHub describing what needs to change.  This file
 * was generated, so the scripts that generated it need to update as well.
 */

#include <nanogui/nanogui.h>
#include <nanogui/resources.h>
#include <nanogui/fontawesome.h>
using namespace nanogui;

// Custom theme for loading the fontawesome font
class FontawesomeTheme : public nanogui::Theme {
public:
    // This override informs NanoGUI to use this as the icon font.
    virtual std::string defaultIconFont() const override { return "fontawesome"; }

    FontawesomeTheme(NVGcontext *ctx) : nanogui::Theme(ctx) {
        // load the fontawesome font into memory
        mFontawesomeFont = nanogui::createFontMem(ctx, "fontawesome", "fontawesome.ttf");
        if (mFontawesomeFont == -1)
            throw std::runtime_error("Could not load the fontawesome font!");

        // TODO: you need to override the following default icon choices in your
        //       own application!  See documentation for nanogui::Theme.
        // mCheckBoxIcon             = ENTYPO_ICON_CHECK;
        // mCheckBoxIconExtraScale   = defaultCheckBoxIconExtraScale();
        // mMessageInformationIcon   = ENTYPO_ICON_INFO_WITH_CIRCLE;
        // mMessageQuestionIcon      = ENTYPO_ICON_HELP_WITH_CIRCLE;
        // mMessageWarningIcon       = ENTYPO_ICON_WARNING;
        // mMessageAltButtonIcon     = ENTYPO_ICON_CIRCLE_WITH_CROSS;
        // mMessagePrimaryButtonIcon = ENTYPO_ICON_CHECK;
        // mPopupChevronRightIcon    = ENTYPO_ICON_CHEVRON_RIGHT;
        // mPopupChevronLeftIcon     = ENTYPO_ICON_CHEVRON_LEFT;
        // mPopupIconExtraScale      = defaultPopupIconExtraScale();
        // mTabHeaderLeftIcon        = ENTYPO_ICON_ARROW_BOLD_LEFT;
        // mTabHeaderRightIcon       = ENTYPO_ICON_ARROW_BOLD_RIGHT;
        // mTextBoxUpIcon            = ENTYPO_ICON_CHEVRON_UP;
        // mTextBoxDownIcon          = ENTYPO_ICON_CHEVRON_DOWN;
        // mTextBoxIconExtraScale    = defaultTextBoxIconExtraScale();
    }

    virtual ~FontawesomeTheme() { /* nothing to free */ }

protected:
    int mFontawesomeFont = -1;
};

class FontawesomeScreen : public nanogui::Screen {
public:
    FontawesomeScreen(const Vector2i &size, const std::string &title, bool resizable)
        : nanogui::Screen(size, title, resizable) {

        mFontawesomeTheme = new FontawesomeTheme(this->mNVGContext);
        this->setTheme(mFontawesomeTheme);
    }

    virtual ~FontawesomeScreen() { /* nothing to free */ }

    // allow <ESCAPE> to exit
    virtual bool keyboardEvent(int key, int scancode, int action, int modifiers) override {
        if (key == GLFW_KEY_ESCAPE && modifiers == 0) {
            setVisible(false);
            return true;
        }

        return Screen::keyboardEvent(key, scancode, action, modifiers);
    }

protected:
    nanogui::ref<FontawesomeTheme> mFontawesomeTheme;
};


// Convenience macro for creating an IconBox. Make sure you put a semicolon after the call to this macro!
#define ADD_ICON(parent, icon, boxWidth) \
    new IconBox(parent, #icon, icon, boxWidth)

class IconBox : public Widget {
public:
    IconBox(Widget *parent, const std::string &name, int icon, int width)
        : Widget(parent) {

        this->setLayout(new BoxLayout(Orientation::Horizontal));

        auto *b = new Button(this, "", icon);
        b->setFixedWidth(40);

        auto *text = new TextBox(this, name);
        text->setDefaultValue(name);
        text->setEditable(true);
        /* Return false essentially makes it not possible to actually edit this text
         * box, but keeping it editable=true allows selection for copy-paste.  If the
         * text box is not editable, then the user cannot highlight it.
         */
        text->setCallback([](const std::string &) { return false; });
        text->setFont("mono-bold");
        text->setFixedWidth(width - 40);
    }
};


int main(int /* argc */, char ** /* argv */) {
    nanogui::init();

    /* scoped variables */ {
        static constexpr int width      = 1000;
        static constexpr int half_width = width / 2;
        static constexpr int height     = 800;

        // create a fixed size screen with one window
        FontawesomeScreen *screen = new FontawesomeScreen({width, height}, "NanoGUI Fontawesome Icons", false);

        // create the custom theme now so that all children will inherit it
        Window *window = new Window(screen, "");
        window->setPosition({0, 0});
        window->setFixedSize({width, height});

        // attach a vertical scroll panel
        auto vscroll = new VScrollPanel(window);
        vscroll->setFixedSize({width, height});

        // vscroll should only have *ONE* child. this is what `wrapper` is for
        auto wrapper = new Widget(vscroll);
        wrapper->setFixedSize({width, height});
        wrapper->setLayout(new GridLayout());// defaults: 2 columns

        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        ADD_ICON(wrapper, FONTAWESOME_ICON_ADDRESS_BOOK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ADDRESS_CARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ARROW_ALT_CIRCLE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ARROW_ALT_CIRCLE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ARROW_ALT_CIRCLE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ARROW_ALT_CIRCLE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BELL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BELL_SLASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BOOKMARK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_500PX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ACCESSIBLE_ICON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ACCUSOFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ADN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ADVERSAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AFFILIATETHEME, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ALGOLIA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AMAZON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AMAZON_PAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AMILIA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ANDROID, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ANGELLIST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ANGRYCREATIVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ANGULAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_APP_STORE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_APP_STORE_IOS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_APPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_APPLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_APPLE_PAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ASYMMETRIK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AUDIBLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AUTOPREFIXER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AVIANEX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AVIATO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_AWS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BANDCAMP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BEHANCE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BEHANCE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BIMOBJECT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BITBUCKET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BITCOIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BITY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BLACK_TIE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BLACKBERRY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BLOGGER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BLOGGER_B, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BLUETOOTH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BLUETOOTH_B, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BTC, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BUROMOBELEXPERTE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_BUYSELLADS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_AMAZON_PAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_AMEX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_APPLE_PAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_DINERS_CLUB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_DISCOVER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_JCB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_MASTERCARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_PAYPAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_STRIPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CC_VISA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CENTERCODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CHROME, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CLOUDSCALE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CLOUDSMITH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CLOUDVERSIFY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CODEPEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CODIEPIE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CONNECTDEVELOP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CONTAO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CPANEL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CREATIVE_COMMONS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CSS3, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CSS3_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_CUTTLEFISH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_D_AND_D, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DASHCUBE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DELICIOUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DEPLOYDOG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DESKPRO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DEVIANTART, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DIGG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DIGITAL_OCEAN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DISCORD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DISCOURSE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DOCHUB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DOCKER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DRAFT2DIGITAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DRIBBBLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DRIBBBLE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DROPBOX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DRUPAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_DYALOG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_EARLYBIRDS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_EDGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ELEMENTOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_EMBER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_EMPIRE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ENVIRA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ERLANG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ETHEREUM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ETSY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_EXPEDITEDSSL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FACEBOOK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FACEBOOK_F, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FACEBOOK_MESSENGER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FACEBOOK_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FIREFOX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FIRST_ORDER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FIRSTDRAFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FLICKR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FLIPBOARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FLY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FONT_AWESOME, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FONT_AWESOME_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FONT_AWESOME_FLAG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FONTICONS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FONTICONS_FI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FORT_AWESOME, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FORT_AWESOME_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FORUMBEE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FOURSQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FREE_CODE_CAMP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_FREEBSD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GET_POCKET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GG_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GIT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GIT_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GITHUB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GITHUB_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GITHUB_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GITKRAKEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GITLAB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GITTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GLIDE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GLIDE_G, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOFORE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOODREADS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOODREADS_G, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE_DRIVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE_PLAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE_PLUS_G, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE_PLUS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GOOGLE_WALLET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GRATIPAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GRAV, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GRIPFIRE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GRUNT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_GULP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HACKER_NEWS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HACKER_NEWS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HIPS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HIRE_A_HELPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HOOLI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HOTJAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HOUZZ, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HTML5, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_HUBSPOT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_IMDB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_INSTAGRAM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_INTERNET_EXPLORER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_IOXHOST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ITUNES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ITUNES_NOTE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_JENKINS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_JOGET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_JOOMLA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_JS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_JS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_JSFIDDLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_KEYCDN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_KICKSTARTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_KICKSTARTER_K, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_KORVUE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LARAVEL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LASTFM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LASTFM_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LEANPUB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LESS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LINE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LINKEDIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LINKEDIN_IN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LINODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LINUX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_LYFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MAGENTO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MAXCDN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MEDAPPS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MEDIUM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MEDIUM_M, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MEDRT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MEETUP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MICROSOFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MIX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MIXCLOUD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MIZUNI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MODX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_MONERO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NAPSTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NINTENDO_SWITCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NODE_JS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NPM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NS8, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_NUTRITIONIX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ODNOKLASSNIKI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ODNOKLASSNIKI_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_OPENCART, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_OPENID, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_OPERA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_OPTIN_MONSTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_OSI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PAGE4, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PAGELINES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PALFED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PATREON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PAYPAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PERISCOPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PHABRICATOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PHOENIX_FRAMEWORK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PHP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PIED_PIPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PIED_PIPER_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PIED_PIPER_PP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PINTEREST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PINTEREST_P, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PINTEREST_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PLAYSTATION, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PRODUCT_HUNT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PUSHED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_PYTHON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_QQ, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_QUINSCAPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_QUORA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_RAVELRY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_REACT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_REBEL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_RED_RIVER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_REDDIT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_REDDIT_ALIEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_REDDIT_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_RENDACT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_RENREN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_REPLYD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_RESOLVING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ROCKETCHAT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_ROCKRMS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SAFARI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SASS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SCHLIX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SCRIBD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SEARCHENGIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SELLCAST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SELLSY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SERVICESTACK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SHIRTSINBULK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SIMPLYBUILT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SISTRIX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SKYATLAS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SKYPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SLACK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SLACK_HASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SLIDESHARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SNAPCHAT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SNAPCHAT_GHOST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SNAPCHAT_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SOUNDCLOUD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SPEAKAP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SPOTIFY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STACK_EXCHANGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STACK_OVERFLOW, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STAYLINKED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STEAM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STEAM_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STEAM_SYMBOL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STICKER_MULE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STRAVA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STRIPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STRIPE_S, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STUDIOVINARI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STUMBLEUPON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_STUMBLEUPON_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SUPERPOWERS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_SUPPLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TELEGRAM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TELEGRAM_PLANE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TENCENT_WEIBO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_THEMEISLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TRELLO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TRIPADVISOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TUMBLR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TUMBLR_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TWITCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TWITTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TWITTER_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_TYPO3, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_UBER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_UIKIT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_UNIREGISTRY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_UNTAPPD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_USB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_USSUNNAH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VAADIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIACOIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIADEO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIADEO_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIBER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIMEO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIMEO_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VIMEO_V, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VINE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VNV, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_VUEJS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WEIBO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WEIXIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WHATSAPP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WHATSAPP_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WHMCS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WIKIPEDIA_W, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WINDOWS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WORDPRESS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WORDPRESS_SIMPLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WPBEGINNER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WPEXPLORER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_WPFORMS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_XBOX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_XING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_XING_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_Y_COMBINATOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YAHOO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YANDEX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YANDEX_INTERNATIONAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YELP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YOAST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YOUTUBE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BRANDS_YOUTUBE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_BUILDING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CALENDAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CALENDAR_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CALENDAR_CHECK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CALENDAR_MINUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CALENDAR_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CALENDAR_TIMES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CARET_SQUARE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CARET_SQUARE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CARET_SQUARE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CARET_SQUARE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CHART_BAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CHECK_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CHECK_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CLIPBOARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CLOCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CLONE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CLOSED_CAPTIONING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_COMMENT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_COMMENT_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_COMMENTS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_COMPASS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_COPY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_COPYRIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_CREDIT_CARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_DOT_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_EDIT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ENVELOPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ENVELOPE_OPEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_EYE_SLASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_ARCHIVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_AUDIO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_CODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_EXCEL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_IMAGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_PDF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_POWERPOINT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_VIDEO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FILE_WORD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FLAG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FOLDER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FOLDER_OPEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FROWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_FUTBOL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_GEM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_LIZARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_PAPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_PEACE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_POINT_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_POINT_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_POINT_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_POINT_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_POINTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_ROCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_SCISSORS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HAND_SPOCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HANDSHAKE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HDD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HEART, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HOSPITAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_HOURGLASS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ID_BADGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_ID_CARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_IMAGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_IMAGES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_KEYBOARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_LEMON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_LIFE_RING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_LIGHTBULB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_LIST_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_MAP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_MEH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_MINUS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_MONEY_BILL_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_MOON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_NEWSPAPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_OBJECT_GROUP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_OBJECT_UNGROUP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_PAPER_PLANE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_PAUSE_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_PLAY_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_PLUS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_QUESTION_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_REGISTERED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SAVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SHARE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SMILE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SNOWFLAKE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ADDRESS_BOOK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ADDRESS_CARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ADJUST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ALIGN_CENTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ALIGN_JUSTIFY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ALIGN_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ALIGN_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_AMBULANCE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_AMERICAN_SIGN_LANGUAGE_INTERPRETING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANCHOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_DOUBLE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_DOUBLE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_DOUBLE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_DOUBLE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ANGLE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARCHIVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_ALT_CIRCLE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_ALT_CIRCLE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_ALT_CIRCLE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_ALT_CIRCLE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_CIRCLE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_CIRCLE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_CIRCLE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_CIRCLE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROW_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROWS_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROWS_ALT_H, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ARROWS_ALT_V, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ASSISTIVE_LISTENING_SYSTEMS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ASTERISK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_AT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_AUDIO_DESCRIPTION, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BACKWARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BALANCE_SCALE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BAN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BARCODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BARS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BASEBALL_BALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BASKETBALL_BALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BATH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BATTERY_EMPTY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BATTERY_FULL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BATTERY_HALF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BATTERY_QUARTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BATTERY_THREE_QUARTERS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BEER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BELL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BELL_SLASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BICYCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BINOCULARS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BIRTHDAY_CAKE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BLIND, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BOLD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BOLT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BOMB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BOOK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BOOKMARK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BOWLING_BALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BRAILLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BRIEFCASE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BUG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BUILDING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BULLHORN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BULLSEYE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_BUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALCULATOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALENDAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALENDAR_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALENDAR_CHECK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALENDAR_MINUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALENDAR_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CALENDAR_TIMES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CAMERA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CAMERA_RETRO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_SQUARE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_SQUARE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_SQUARE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_SQUARE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CARET_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CART_ARROW_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CART_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CERTIFICATE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHART_AREA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHART_BAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHART_LINE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHART_PIE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHECK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHECK_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHECK_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_BISHOP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_BOARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_KING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_KNIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_PAWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_QUEEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHESS_ROOK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_CIRCLE_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_CIRCLE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_CIRCLE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_CIRCLE_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHEVRON_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CHILD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CIRCLE_NOTCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLIPBOARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLOCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLONE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLOSED_CAPTIONING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLOUD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLOUD_DOWNLOAD_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CLOUD_UPLOAD_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CODE_BRANCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COFFEE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COGS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COLUMNS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COMMENT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COMMENT_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COMMENTS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COMPASS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COMPRESS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COPY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_COPYRIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CREDIT_CARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CROP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CROSSHAIRS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CUBE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CUBES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_CUT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_DATABASE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_DEAF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_DESKTOP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_DOLLAR_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_DOT_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_DOWNLOAD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EDIT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EJECT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ELLIPSIS_H, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ELLIPSIS_V, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ENVELOPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ENVELOPE_OPEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ENVELOPE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ERASER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EURO_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXCHANGE_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXCLAMATION, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXCLAMATION_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXCLAMATION_TRIANGLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXPAND, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXPAND_ARROWS_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXTERNAL_LINK_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EXTERNAL_LINK_SQUARE_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EYE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EYE_DROPPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_EYE_SLASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FAST_BACKWARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FAST_FORWARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FAX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FEMALE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FIGHTER_JET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_ARCHIVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_AUDIO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_CODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_EXCEL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_IMAGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_PDF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_POWERPOINT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_VIDEO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILE_WORD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FILTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FIRE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FIRE_EXTINGUISHER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FLAG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FLAG_CHECKERED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FLASK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FOLDER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FOLDER_OPEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FONT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FOOTBALL_BALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FORWARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FROWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_FUTBOL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GAMEPAD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GAVEL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GEM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GENDERLESS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GIFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GLASS_MARTINI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GLOBE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GOLF_BALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_GRADUATION_CAP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_H_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_LIZARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_PAPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_PEACE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_POINT_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_POINT_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_POINT_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_POINT_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_POINTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_ROCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_SCISSORS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HAND_SPOCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HANDSHAKE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HASHTAG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HDD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HEADING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HEADPHONES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HEART, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HEARTBEAT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HISTORY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOCKEY_PUCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOME, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOSPITAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOURGLASS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOURGLASS_END, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOURGLASS_HALF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_HOURGLASS_START, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_I_CURSOR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ID_BADGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ID_CARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_IMAGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_IMAGES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_INBOX, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_INDENT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_INDUSTRY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_INFO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_INFO_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ITALIC, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_KEY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_KEYBOARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LANGUAGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LAPTOP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LEAF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LEMON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LEVEL_DOWN_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LEVEL_UP_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIFE_RING, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIGHTBULB, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LINK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIRA_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIST_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIST_OL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LIST_UL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LOCATION_ARROW, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LOCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LOCK_OPEN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LONG_ARROW_ALT_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LONG_ARROW_ALT_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LONG_ARROW_ALT_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LONG_ARROW_ALT_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_LOW_VISION, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAGIC, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAGNET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MALE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAP_MARKER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAP_MARKER_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAP_PIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MAP_SIGNS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MARS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MARS_DOUBLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MARS_STROKE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MARS_STROKE_H, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MARS_STROKE_V, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MEDKIT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MEH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MERCURY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MICROCHIP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MICROPHONE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MICROPHONE_SLASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MINUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MINUS_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MINUS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MOBILE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MOBILE_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MONEY_BILL_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MOON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MOTORCYCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MOUSE_POINTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_MUSIC, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_NEUTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_NEWSPAPER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_OBJECT_GROUP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_OBJECT_UNGROUP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_OUTDENT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PAINT_BRUSH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PAPER_PLANE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PAPERCLIP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PARAGRAPH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PASTE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PAUSE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PAUSE_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PAW, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PEN_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PENCIL_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PERCENT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PHONE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PHONE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PHONE_VOLUME, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLANE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLAY_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLUG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLUS_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PLUS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PODCAST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_POUND_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_POWER_OFF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PRINT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_PUZZLE_PIECE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_QRCODE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_QUESTION, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_QUESTION_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_QUIDDITCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_QUOTE_LEFT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_QUOTE_RIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RANDOM, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RECYCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_REDO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_REDO_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_REGISTERED, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_REPLY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_REPLY_ALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RETWEET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ROAD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_ROCKET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RSS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RSS_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RUBLE_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_RUPEE_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SAVE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SEARCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SEARCH_MINUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SEARCH_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SERVER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHARE_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHARE_ALT_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHARE_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHEKEL_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHIELD_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHIP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHOPPING_BAG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHOPPING_BASKET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHOPPING_CART, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SHOWER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SIGN_IN_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SIGN_LANGUAGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SIGN_OUT_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SIGNAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SITEMAP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SLIDERS_H, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SMILE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SNOWFLAKE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_ALPHA_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_ALPHA_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_AMOUNT_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_AMOUNT_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_NUMERIC_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_NUMERIC_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SORT_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SPACE_SHUTTLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SPINNER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SQUARE_FULL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STAR_HALF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STEP_BACKWARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STEP_FORWARD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STETHOSCOPE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STICKY_NOTE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STOP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STOP_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STOPWATCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STREET_VIEW, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_STRIKETHROUGH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SUBSCRIPT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SUBWAY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SUITCASE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SUN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SUPERSCRIPT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SYNC, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_SYNC_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TABLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TABLE_TENNIS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TABLET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TABLET_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TACHOMETER_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TAG, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TAGS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TASKS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TAXI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TERMINAL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TEXT_HEIGHT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TEXT_WIDTH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TH_LARGE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TH_LIST, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THERMOMETER_EMPTY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THERMOMETER_FULL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THERMOMETER_HALF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THERMOMETER_QUARTER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THERMOMETER_THREE_QUARTERS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THUMBS_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THUMBS_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_THUMBTACK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TICKET_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TIMES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TIMES_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TINT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TOGGLE_OFF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TOGGLE_ON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRADEMARK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRAIN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRANSGENDER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRANSGENDER_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRASH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRASH_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TREE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TROPHY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TRUCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TTY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_TV, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UMBRELLA, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNDERLINE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNDO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNDO_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNIVERSAL_ACCESS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNIVERSITY, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNLINK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNLOCK, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UNLOCK_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UPLOAD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USER_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USER_MD, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USER_PLUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USER_SECRET, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USER_TIMES, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_USERS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UTENSIL_SPOON, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_UTENSILS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VENUS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VENUS_DOUBLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VENUS_MARS, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VIDEO, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VOLLEYBALL_BALL, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VOLUME_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VOLUME_OFF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_VOLUME_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WHEELCHAIR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WIFI, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WINDOW_CLOSE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WINDOW_MAXIMIZE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WINDOW_MINIMIZE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WINDOW_RESTORE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WON_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_WRENCH, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SOLID_YEN_SIGN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SQUARE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_STAR, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_STAR_HALF, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_STICKY_NOTE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_STOP_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_SUN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_THUMBS_DOWN, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_THUMBS_UP, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_TIMES_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_TRASH_ALT, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_USER, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_USER_CIRCLE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_WINDOW_CLOSE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_WINDOW_MAXIMIZE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_WINDOW_MINIMIZE, half_width);
        ADD_ICON(wrapper, FONTAWESOME_ICON_WINDOW_RESTORE, half_width);
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////

        screen->performLayout();
        screen->setVisible(true);

        nanogui::mainloop();
    }

    nanogui::shutdown();
    return 0;
}
