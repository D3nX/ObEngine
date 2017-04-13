/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_SCROLLBAR_HPP
#define TGUI_SCROLLBAR_HPP


#include <TGUI/Widget.hpp>
#include <TGUI/Renderers/ScrollbarRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Scrollbar widget
    ///
    /// Signals:
    ///     - ValueChanged (The value of the scrollbar has changed)
    ///         * Optional parameter int: New value
    ///         * Uses Callback member 'value'
    ///
    ///     - Inherited signals from Widget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Scrollbar : public Widget
    {
    public:

        typedef std::shared_ptr<Scrollbar> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Scrollbar> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new scrollbar widget
        ///
        /// @return The new scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Scrollbar::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another scrollbar
        ///
        /// @param scrollbar  The other scrollbar
        ///
        /// @return The new scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Scrollbar::Ptr copy(Scrollbar::ConstPtr scrollbar);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Pointer to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ScrollbarRenderer* getRenderer() const
        {
            return aurora::downcast<ScrollbarRenderer*>(m_renderer.get());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the scrollbar
        ///
        /// @param size  The new size of the scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum value
        ///
        /// @param maximum  The new maximum value
        ///
        /// When the value is bigger than (maximum - low value), the value is set to maximum - low value.
        /// The default maximum value is 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(unsigned int maximum);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum value
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value is 10.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximum() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the current value
        ///
        /// @param value  The new value
        ///
        /// The value has to be smaller than maximum - low value.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setValue(unsigned int value);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value
        ///
        /// @return The current value
        ///
        /// The default value is 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the 'low value'
        ///
        /// @param lowValue  The new low value.
        ///                  In e.g. a list box, this value is the amount of items that fit inside the list box
        ///
        /// Until the maximum is bigger than this value, no scrollbar will be drawn.
        /// You can however choose to always draw the scrollbar by calling setAutoHide(false).
        /// The default low value is 6.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLowValue(unsigned int lowValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the low value
        ///
        /// @see setLowValue
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getLowValue() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes how much the value changes when scrolling or pressing one of the arrows of the scrollbar
        ///
        /// @param scrollAmount  How far should the scrollbar scroll when an arrow is clicked?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollAmount(unsigned int scrollAmount);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns how much the value changes when scrolling or pressing one of the arrows of the scrollbar
        ///
        /// @return How far should the scrollbar scroll when an arrow is clicked?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getScrollAmount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the scrollbar should hide automatically or not
        ///
        /// When true (default), the scrollbar will not be drawn when the maximum is smaller than the low value.
        ///
        /// @param autoHide  Should the scrollbar be invisible when you can't scroll?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAutoHide(bool autoHide);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the scrollbar is hiding automatically or not
        ///
        /// When true (default), the scrollbar will not be drawn when the maximum is smaller than the low value.
        /// So when you can't scroll, the scrollbar won't be drawn.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getAutoHide() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(sf::Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelScrolled(float delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position of the thumb based on the current value of the slider
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateThumbPosition();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<Scrollbar>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        enum class Part
        {
            Track,
            Thumb,
            ArrowUp,
            ArrowDown
        };

        // Keep track on which part of the scrollbar the mouse is standing
        Part m_mouseHoverOverPart = Part::Thumb;

        // When the mouse went down, did it go down on top of the thumb? If so, where?
        bool m_mouseDownOnThumb = false;
        sf::Vector2f m_mouseDownOnThumbPos;

        unsigned int m_maximum = 10;
        unsigned int m_value = 0;

        // Maximum should be above this value before the scrollbar is needed
        unsigned int m_lowValue = 6;

        // Is the scrollbar draw vertically?
        bool m_verticalScroll = true;

        // Does the image lie vertically?
        bool m_verticalImage = true;

        // How far should the value change when pressing one of the arrows?
        unsigned int m_scrollAmount = 1;

        // When no scrollbar is needed, should the scrollbar be drawn or stay hidden?
        bool m_autoHide = true;

        // Did the mouse went down on one of the arrows?
        bool m_mouseDownOnArrow = false;

        sf::FloatRect m_track;
        sf::FloatRect m_thumb;
        sf::FloatRect m_arrowUp;
        sf::FloatRect m_arrowDown;

        Sprite m_spriteTrack;
        Sprite m_spriteTrackHover;
        Sprite m_spriteThumb;
        Sprite m_spriteThumbHover;
        Sprite m_spriteArrowUp;
        Sprite m_spriteArrowUpHover;
        Sprite m_spriteArrowDown;
        Sprite m_spriteArrowDownHover;

        // Cached renderer properties
        Color m_thumbColorCached;
        Color m_thumbColorHoverCached;
        Color m_trackColorCached;
        Color m_trackColorHoverCached;
        Color m_arrowColorCached;
        Color m_arrowColorHoverCached;
        Color m_arrowBackgroundColorCached;
        Color m_arrowBackgroundColorHoverCached;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Wrapper around scrollbar to be used inside widgets that need a scrollbar
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ScrollbarChildWidget : public Scrollbar
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse is on top of the scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isMouseDown() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse is on top of the thumb of the scrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isMouseDownOnThumb() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the scrollbar is currently visible
        ///
        /// The scrollbar is visible when auto hide is disabled or when the maximum is higher than the low value
        ///
        /// @return Is the scrollbar visible?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isShown() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SCROLLBAR_HPP