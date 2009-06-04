//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
#ifndef _TGUIWINDOW_H_
#define _TGUIWINDOW_H_

namespace Tubras
{
    //-----------------------------------------------------------------------
    //                          T G U I W i n d o w
    //-----------------------------------------------------------------------
    class TGUIWindow : public IGUIWindow
    {
    protected:
		core::position2d<s32> DragStart;

        TGUIButton* CloseButton;
        IGUIButton* MinButton;
        IGUIButton* RestoreButton;
        IGUIElement* ModalScreen;
        bool    Dragging, IsDraggable;
        bool    DrawBackground;
        bool    DrawTitlebar;
        bool    Modal;

    public:
        TGUIWindow(IGUIEnvironment* environment, IGUIElement* parent,
            s32 id, core::rect<s32> rectangle,
            bool modal=false, bool centered=true, bool draggable=true);
        virtual ~TGUIWindow();

        //! called if an event happened.
        virtual bool OnEvent(const SEvent& event);

        //! update absolute position
        virtual void updateAbsolutePosition();

        //! draws the element and its children
        virtual void draw();

        //! Returns pointer to the close button
        virtual IGUIButton* getCloseButton() const {return CloseButton;}

        //! Returns pointer to the minimize button
        virtual IGUIButton* getMinimizeButton() const {return MinButton;}

        //! Returns pointer to the maximize button
        virtual IGUIButton* getMaximizeButton() const {return RestoreButton;}

		//! Returns true if the window can be dragged with the mouse, false if not
        virtual bool isDraggable() const {return IsDraggable;}

		//! Sets whether the window can be dragged by the mouse
        virtual void setDraggable(bool draggable) {IsDraggable = draggable;}

        //! Set if the window background will be drawn
        virtual void setDrawBackground(bool draw) {DrawBackground = draw;}

        //! Get if the window background will be drawn
        virtual bool getDrawBackground() const {return DrawBackground;}

        //! Set if the window titlebar will be drawn
        //! Note: If the background is not drawn, then the titlebar is automatically also not drawn
        virtual void setDrawTitlebar(bool draw) {DrawTitlebar = draw;}

        //! Get if the window titlebar will be drawn
        virtual bool getDrawTitlebar() const {return DrawTitlebar;}


    };

}

#endif
