//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2008 Tubras Software, Ltd
// Also see acknowledgements in docs/Readme.html
//
// This software is licensed under the zlib/libpng license. See the file
// "docs/license.html" for detailed information.
//-----------------------------------------------------------------------------
// A modified version of Klasker's CImageGUISkin implemenation. 
//-----------------------------------------------------------------------------
#include "tubras.h"

namespace Tubras
{
    //! Workaround for a bug in IVideoDriver::draw2DImage( ITexture* tex, rect<s32> dstRect, 
    //! rect<s32> srcRect, rect<s32>* clip, SColor* colors, bool alpha )
    //! It modifies dstRect and srcRect so the resulting dstRect is entirely inside the clipping rect.
    //! srcRect is scaled so the same part of the image is displayed.
    //! Returns false if dstRect is entirely outside clip, or true if at least some of it is inside.
    inline bool clipRects( core::rect<s32>& dstRect, core::rect<s32>& srcRect, 
        const core::rect<s32>& clip )
    {
        // Clip left side
        if ( dstRect.UpperLeftCorner.X < clip.UpperLeftCorner.X )
        {
            s32 w = clip.UpperLeftCorner.X - dstRect.UpperLeftCorner.X;

            f32 percentRemoved = (f32)w / (f32)dstRect.getWidth();

            dstRect.UpperLeftCorner.X = clip.UpperLeftCorner.X;

            srcRect.UpperLeftCorner.X += (s32)(percentRemoved * srcRect.getWidth());
        }

        // Clip top side
        if ( dstRect.UpperLeftCorner.Y < clip.UpperLeftCorner.Y )
        {
            s32 w = clip.UpperLeftCorner.Y - dstRect.UpperLeftCorner.Y;

            f32 percentRemoved = (f32)w / (f32)dstRect.getHeight();

            dstRect.UpperLeftCorner.Y = clip.UpperLeftCorner.Y;

            srcRect.UpperLeftCorner.Y += (s32)(percentRemoved * srcRect.getHeight());
        }

        // Clip right side
        if ( dstRect.LowerRightCorner.X > clip.LowerRightCorner.X )
        {
            s32 w = dstRect.LowerRightCorner.X - clip.LowerRightCorner.X;

            f32 percentRemoved = (f32)w / (f32)dstRect.getWidth();

            dstRect.LowerRightCorner.X = clip.LowerRightCorner.X;

            srcRect.LowerRightCorner.X -= (s32)(percentRemoved * srcRect.getWidth());
        }

        // Clip bottom side
        if ( dstRect.LowerRightCorner.Y > clip.LowerRightCorner.Y )
        {
            s32 w = dstRect.LowerRightCorner.Y - clip.LowerRightCorner.Y;

            f32 percentRemoved = (f32)w / (f32)dstRect.getHeight();

            dstRect.LowerRightCorner.Y = clip.LowerRightCorner.Y;

            srcRect.LowerRightCorner.Y -= (s32)(percentRemoved * srcRect.getHeight());
        }

        return ( dstRect.getWidth() > 0 && dstRect.getHeight() > 0 );
    }


    //-----------------------------------------------------------------------
    //                            T G U I S k i n
    //-----------------------------------------------------------------------
    TGUISkin2::TGUISkin2( TString skinName ) : m_skinName(skinName)
    {
    }

    //-----------------------------------------------------------------------
    //                           ~ T G U I S k i n
    //-----------------------------------------------------------------------
    TGUISkin2::~TGUISkin2()
    {
        m_defSkin->drop();
    }

    //-----------------------------------------------------------------------
    //                           c a l c E l e m e n t
    //-----------------------------------------------------------------------
    static void calcElement(TImageGUIElementStyle& el)
    {
        u32 lw,rw,th,bh;

        //
        // if outer/inner defined, then calc corners & sides.  if not 
        // defined (window background), then corners & sides are supplied.
        //
        if((el.outer.UpperLeftCorner.X != 0) ||
           (el.outer.LowerRightCorner.X != 0))
        {
            lw = el.inner.UpperLeftCorner.X - el.outer.UpperLeftCorner.X;
            rw = el.outer.LowerRightCorner.X - el.inner.LowerRightCorner.X;
            th = el.inner.UpperLeftCorner.Y - el.outer.UpperLeftCorner.Y;
            bh = el.outer.LowerRightCorner.Y - el.inner.LowerRightCorner.Y;

            el.ulc.UpperLeftCorner = el.outer.UpperLeftCorner;
            el.ulc.LowerRightCorner = el.inner.UpperLeftCorner;

            el.urc.UpperLeftCorner.X = el.inner.LowerRightCorner.X;
            el.urc.UpperLeftCorner.Y = el.outer.UpperLeftCorner.Y;
            el.urc.LowerRightCorner.X = el.outer.LowerRightCorner.X;
            el.urc.LowerRightCorner.Y = el.inner.UpperLeftCorner.Y;

            el.top.UpperLeftCorner.X = el.inner.UpperLeftCorner.X;
            el.top.UpperLeftCorner.Y = el.outer.UpperLeftCorner.Y;
            el.top.LowerRightCorner.X = el.inner.LowerRightCorner.X;
            el.top.LowerRightCorner.Y = el.inner.UpperLeftCorner.Y;

            el.left.UpperLeftCorner.X = el.outer.UpperLeftCorner.X;
            el.left.UpperLeftCorner.Y = el.inner.UpperLeftCorner.Y;
            el.left.LowerRightCorner.X = el.inner.UpperLeftCorner.X;
            el.left.LowerRightCorner.Y = el.inner.LowerRightCorner.Y;

            el.right.UpperLeftCorner.X = el.inner.LowerRightCorner.X;
            el.right.UpperLeftCorner.Y = el.inner.UpperLeftCorner.Y;
            el.right.LowerRightCorner.X = el.outer.LowerRightCorner.X;
            el.right.LowerRightCorner.Y = el.inner.LowerRightCorner.Y;

            el.llc.UpperLeftCorner.X = el.outer.UpperLeftCorner.X;
            el.llc.UpperLeftCorner.Y = el.inner.LowerRightCorner.Y;
            el.llc.LowerRightCorner.X = el.inner.UpperLeftCorner.X;
            el.llc.LowerRightCorner.Y = el.outer.LowerRightCorner.Y;

            el.lrc.UpperLeftCorner = el.inner.LowerRightCorner;
            el.lrc.LowerRightCorner = el.outer.LowerRightCorner;

            el.bottom.UpperLeftCorner.X = el.inner.UpperLeftCorner.X;
            el.bottom.UpperLeftCorner.Y = el.inner.LowerRightCorner.Y;
            el.bottom.LowerRightCorner.X = el.inner.LowerRightCorner.X;
            el.bottom.LowerRightCorner.Y = el.outer.LowerRightCorner.Y;
                
        }

        el.ulcw = el.ulc.getWidth();
        el.ulch = el.ulc.getHeight();
        el.urcw = el.urc.getWidth();
        el.urch = el.urc.getHeight();
        el.llcw = el.llc.getWidth();
        el.llch = el.llc.getHeight();
        el.lrcw = el.lrc.getWidth();
        el.lrch = el.lrc.getHeight();
        el.leftw = el.left.getWidth();
        el.rightw = el.right.getWidth();
        el.toph = el.top.getHeight();
        el.bottomh = el.bottom.getHeight();

        el.minWidth = el.leftw + el.rightw;
        el.minHeight = el.toph + el.bottomh;

        el.client.UpperLeftCorner.X = el.left.UpperLeftCorner.X + el.leftw;
        el.client.UpperLeftCorner.Y = el.top.UpperLeftCorner.Y + el.toph;
        el.client.LowerRightCorner.X = el.right.UpperLeftCorner.X;
        el.client.LowerRightCorner.Y = el.right.LowerRightCorner.Y;       
    }

    //-----------------------------------------------------------------------
    //                           l o a d E l e m e n t
    //-----------------------------------------------------------------------
    static void loadElement(TXMLConfig* config, TImageGUIElementStyle& style, 
        const char* elementName, const char* section)
    {
        char pname[100];

        sprintf(pname,"%s.outer",elementName);
        style.outer = config->getRectd(pname,section);

        sprintf(pname,"%s.inner",elementName);
        style.inner = config->getRectd(pname,section);
        sprintf(pname,"%s.ulc",elementName);
        style.ulc = config->getRectd(pname,section);
        sprintf(pname,"%s.urc",elementName);
        style.urc = config->getRectd(pname,section);
        sprintf(pname,"%s.top",elementName);
        style.top = config->getRectd(pname,section);
        sprintf(pname,"%s.llc",elementName);
        style.llc = config->getRectd(pname,section);
        sprintf(pname,"%s.lrc",elementName);
        style.lrc = config->getRectd(pname,section);
        sprintf(pname,"%s.bottom",elementName);
        style.bottom = config->getRectd(pname,section);
        sprintf(pname,"%s.left",elementName);
        style.left = config->getRectd(pname,section);
        sprintf(pname,"%s.right",elementName);
        style.right = config->getRectd(pname,section);
        sprintf(pname,"%s.client",elementName);
        style.client = config->getRectd(pname,section);
        sprintf(pname,"%s.hashilight",elementName);
        style.hasHilight = config->getBool(pname,section,false);
        sprintf(pname,"%s.useouter",elementName);
        style.useOuter = config->getBool(pname,section,false);
        sprintf(pname,"%s.colour",elementName);
        style.Color = config->getColour(pname,section,TColour());
        calcElement(style);
    }

    //-----------------------------------------------------------------------
    //                           i n i t i a l i z e
    //-----------------------------------------------------------------------
    int  TGUISkin2::initialize()
    {
        TString cfgName;

        int result=0;

        //
        // load skin config
        //

        if(!m_skinName.size())
        {
            getApplication()->logMessage("Error: Missing GUI Skin Configuration");
            return 1;
        }

        TXMLConfig* config = new TXMLConfig();
        if(!config->load(m_skinName))
            return 1;

        TString baseName = config->getString("base512","textures");
        TString baseName2 = config->getString("base256","textures");
        TString hilightName = config->getString("hilight512","textures");
        TString hilightName2 = config->getString("hilight256","textures");

        loadElement(config,m_skinConfig.Window,"window","layout");

        //
        // for the remainder of the def's, only outer/inner are defined but
        // we try and grab the complete def anyway for future skins.
        //
        loadElement(config,m_skinConfig.Button,"button","layout");
        loadElement(config,m_skinConfig.MenuBar,"menubar","layout");

        IrrlichtDevice* dev = getApplication()->getRenderer()->getDevice();
        m_videoDriver = dev->getVideoDriver();
        m_baseTex = m_videoDriver->getTexture(baseName.c_str());
        if(!m_baseTex)
        {
            config->drop();
            return 1;
        }

        m_baseTex2 = m_videoDriver->getTexture(baseName2.c_str());
        if(!m_baseTex2)
        {
            config->drop();
            return 1;
        }

        m_hilightTex = m_videoDriver->getTexture(hilightName.c_str());
        if(!m_hilightTex)
        {
            config->drop();
            return 1;
        }

        m_hilightTex2 = m_videoDriver->getTexture(hilightName2.c_str());
        if(!m_hilightTex2)
        {
            config->drop();
            return 1;
        }

        m_defSkin = getApplication()->getRenderer()->getGUIManager()->getSkin();
        m_defSkin->grab();


        //
        // load default colours
        //
        SColor col;
        col = config->getColour("egdc_3d_face","colours");
        setColor(EGDC_3D_FACE,col);

        col = config->getColour("egdc_window","colours");
        setColor(EGDC_WINDOW,col);
        m_windowColour = col;

        col = config->getColour("egdc_active_caption","colours");
        setColor(EGDC_ACTIVE_CAPTION,col);

        col = config->getColour("egdc_button_text","colours");
        setColor(EGDC_BUTTON_TEXT,col);

        col = config->getColour("egdc_gray_text","colours");
        setColor(EGDC_GRAY_TEXT,col);

        m_dialogColour = config->getColour("tgdc_dialog_window","colours");

        config->drop();

        return result;
    }

    //-----------------------------------------------------------------------
    //                            g e t C o l o r
    //-----------------------------------------------------------------------
    video::SColor TGUISkin2::getColor(EGUI_DEFAULT_COLOR color) const
    {
        return m_defSkin->getColor(color);
    }

    //-----------------------------------------------------------------------
    //                            s e t C o l o r
    //-----------------------------------------------------------------------
    void TGUISkin2::setColor( EGUI_DEFAULT_COLOR which, video::SColor newColor )
    {
        m_defSkin->setColor(which, newColor);
    }

    //-----------------------------------------------------------------------
    //                            g e t S i z e
    //-----------------------------------------------------------------------
    s32 TGUISkin2::getSize(EGUI_DEFAULT_SIZE size) const
    {
        return m_defSkin->getSize(size);
    }

    //-----------------------------------------------------------------------
    //                            s e t S i z e
    //-----------------------------------------------------------------------
    void TGUISkin2::setSize(EGUI_DEFAULT_SIZE which, s32 size)
    {
        m_defSkin->setSize(which, size);
    }

    //-----------------------------------------------------------------------
    //                      g e t D e f a u l t T e x t
    //-----------------------------------------------------------------------
    const wchar_t* TGUISkin2::getDefaultText(EGUI_DEFAULT_TEXT text) const
    {
        return m_defSkin->getDefaultText(text);
    }

    //-----------------------------------------------------------------------
    //                      s e t D e f a u l t T e x t
    //-----------------------------------------------------------------------
    void TGUISkin2::setDefaultText(EGUI_DEFAULT_TEXT which, const wchar_t* newText)
    {
        m_defSkin->setDefaultText(which, newText);
    }


    //-----------------------------------------------------------------------
    //                            g e t F o n t
    //-----------------------------------------------------------------------
    IGUIFont* TGUISkin2::getFont(EGUI_DEFAULT_FONT defaultFont) const
    {
        return m_defSkin->getFont(defaultFont);
    }

    //-----------------------------------------------------------------------
    //                            s e t F o n t
    //-----------------------------------------------------------------------
    void TGUISkin2::setFont(IGUIFont* font, EGUI_DEFAULT_FONT defaultFont)
    {
        m_defSkin->setFont(font, defaultFont);
    }

    //-----------------------------------------------------------------------
    //                      g e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    IGUISpriteBank* TGUISkin2::getSpriteBank() const
    {
        return m_defSkin->getSpriteBank();
    }

    //-----------------------------------------------------------------------
    //                      s e t S p r i t e B a n k
    //-----------------------------------------------------------------------
    void TGUISkin2::setSpriteBank( IGUISpriteBank* bank )
    {
        m_defSkin->setSpriteBank(bank);
    }

    //-----------------------------------------------------------------------
    //                            g e t I c o n
    //-----------------------------------------------------------------------
    u32 TGUISkin2::getIcon( EGUI_DEFAULT_ICON icon ) const
    {
        return m_defSkin->getIcon(icon);
    }

    //-----------------------------------------------------------------------
    //                            s e t I c o n
    //-----------------------------------------------------------------------
    void TGUISkin2::setIcon( EGUI_DEFAULT_ICON icon, u32 index )
    {
        m_defSkin->setIcon(icon, index);
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D B u t t o n P a n e S t a n d a r d 
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DButtonPaneStandard( IGUIElement* element, 
        const core::rect<s32>& rect, const core::rect<s32>* clip )
    {

        drawElementStyle( element, m_skinConfig.Button, rect, clip );
    }

    //-----------------------------------------------------------------------
    //              d r a w 3 D B u t t o n P a n e P r e s s e d 
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DButtonPanePressed( IGUIElement* element, 
        const core::rect<s32>& rect, const core::rect<s32>* clip )
    {
        drawElementStyle( element, m_skinConfig.Button, rect, clip );
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D S u n k e n P a n e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DSunkenPane(IGUIElement* element,
        video::SColor bgcolor, bool flat, bool fillBackGround,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DSunkenPane(element, bgcolor, flat, 
            fillBackGround, rect, clip);
    }

    //-----------------------------------------------------------------------
    //               d r a w 3 D W i n d o w B a c k g r o u n d
    //-----------------------------------------------------------------------
    core::rect<s32> TGUISkin2::draw3DWindowBackground(IGUIElement* element,
        bool drawTitleBar, video::SColor titleBarColor,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        drawElementStyle( element, m_skinConfig.Window, rect, clip );
        return core::rect<s32>( rect.UpperLeftCorner.X + m_skinConfig.Window.leftw,rect.UpperLeftCorner.Y+4,
            rect.LowerRightCorner.X, rect.UpperLeftCorner.Y + m_skinConfig.Window.toph );
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D M e n u P a n e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DMenuPane(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {
        m_defSkin->draw3DMenuPane(element,rect,clip);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T o o l B a r
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DToolBar(IGUIElement* element,
        const core::rect<s32>& rect,
        const core::rect<s32>* clip)
    {

        SColor col(255,250,250,250);
        SColor vcol[4]={col,col,col,col};
        if(element->getType() == EGUIET_MENU)
        {
            drawElementStyle(element,m_skinConfig.MenuBar,rect,clip);
        }
        else
        {
            m_defSkin->draw3DToolBar(element, rect, clip);
        }

    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T a b B u t t o n
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DTabButton(IGUIElement* element, bool active,
            const core::rect<s32>& rect, const core::rect<s32>* clip, 
            gui::EGUI_ALIGNMENT alignment)
    {
        m_defSkin->draw3DTabButton(element, active, rect, clip, alignment);
    }

    //-----------------------------------------------------------------------
    //                     d r a w 3 D T a b B o d y
    //-----------------------------------------------------------------------
    void TGUISkin2::draw3DTabBody(IGUIElement* element, bool border, bool background,
            const core::rect<s32>& rect, const core::rect<s32>* clip, s32 tabHeight, 
            gui::EGUI_ALIGNMENT alignment)
    {
        m_defSkin->draw3DTabBody(element, border, background, rect, clip, tabHeight, alignment);
    }

    //-----------------------------------------------------------------------
    //                          d r a w I c o n
    //-----------------------------------------------------------------------
    void TGUISkin2::drawIcon(IGUIElement* element, EGUI_DEFAULT_ICON icon,
        const core::position2di position, u32 starttime, u32 currenttime, 
        bool loop, const core::rect<s32>* clip)
    {
        m_defSkin->drawIcon(element,icon,position,starttime,currenttime,loop,clip);
    }

    //-----------------------------------------------------------------------
    //              d r a w H o r i z o n t a l P r o g r e s s B a r
    //-----------------------------------------------------------------------
    void TGUISkin2::drawHorizontalProgressBar( IGUIElement* element, 
        const core::rect<s32>& rectangle, const core::rect<s32>* clip,
        f32 filledRatio, video::SColor fillColor )
    {
    }

    //-----------------------------------------------------------------------
    //                    d r a w E l e m e n t S t y l e
    //-----------------------------------------------------------------------
    void TGUISkin2::drawElementStyle( IGUIElement* element,
        const TImageGUIElementStyle& style, 
        const core::rect<s32>& rect, 
        const core::rect<s32>* clip, 
        const ITexture* texture,
        video::SColor* pcolor  )
    {
        core::rect<s32> r=rect;
        TRectd dstRect,srcRect,capRect;
        EGUI_ELEMENT_TYPE etype=element->getType();
        const ITexture* tex = texture;
        if(!tex)
            tex = m_baseTex;

        SColor col=style.Color;
        if(pcolor)
            col = *pcolor;

        if(etype == EGUIET_BUTTON)
        {
            if(((IGUIButton*)element)->isPressed())
            {
                f32 ipl=0.7f;
                col.setRed((s32)(col.getRed() * ipl));
                col.setGreen((s32)(col.getGreen() * ipl));
                col.setBlue((s32)(col.getBlue() * ipl));
            }
        }

        SColor vcol[4]={col,col,col,col};

        
        if(style.useOuter || 
            (rect.getHeight() < style.minHeight) ||
            (rect.getWidth() < style.minWidth))
        {
            dstRect = rect;
            srcRect = style.outer;
            m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);
            return;
        }
        

        //
        // upper left corner
        //
        srcRect = style.ulc;
        dstRect = rect;
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + style.ulcw;
        dstRect.LowerRightCorner.Y = dstRect.UpperLeftCorner.Y + style.ulch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // upper middle
        //
        srcRect = style.top;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.UpperLeftCorner.X + style.ulcw;
        dstRect.LowerRightCorner.X = rect.LowerRightCorner.X - style.urcw;
        dstRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + style.ulch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // upper right corner
        //
        srcRect = style.urc;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.LowerRightCorner.X - style.urcw;
        dstRect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + style.urch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // lower left
        //
        srcRect = style.llc;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y = rect.LowerRightCorner.Y - style.llch;
        dstRect.LowerRightCorner.X = rect.UpperLeftCorner.X + style.llcw;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // lower right
        //
        srcRect = style.lrc;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.LowerRightCorner.X - style.lrcw;
        dstRect.UpperLeftCorner.Y = rect.LowerRightCorner.Y - style.lrch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // lower middle
        //
        srcRect = style.bottom;
        dstRect = rect;
        dstRect.UpperLeftCorner.X = rect.UpperLeftCorner.X + style.llcw;
        dstRect.LowerRightCorner.X = rect.LowerRightCorner.X - style.lrcw;
        dstRect.UpperLeftCorner.Y = rect.LowerRightCorner.Y - style.llch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // left side
        //
        srcRect = style.left;
        dstRect = rect;
        dstRect.UpperLeftCorner.Y  = dstRect.UpperLeftCorner.Y + style.ulch;
        dstRect.LowerRightCorner.X = dstRect.UpperLeftCorner.X + style.leftw;
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - style.llch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);

        //
        // right side
        //
        srcRect = style.right;
        dstRect = rect;
        dstRect.UpperLeftCorner.X  = dstRect.LowerRightCorner.X - style.rightw;
        dstRect.UpperLeftCorner.Y = dstRect.UpperLeftCorner.Y + style.urch;
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - style.llch;
        m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);


        //
        // client/middle area
        //
        srcRect = style.client;
        dstRect = rect;
        dstRect.UpperLeftCorner.X  = dstRect.UpperLeftCorner.X + style.leftw;
        dstRect.UpperLeftCorner.Y = dstRect.UpperLeftCorner.Y + style.toph;
        dstRect.LowerRightCorner.X = dstRect.LowerRightCorner.X - style.rightw;
        dstRect.LowerRightCorner.Y = dstRect.LowerRightCorner.Y - style.bottomh;

        //
        // client rect 
        //
        switch(etype)
        {
        case EGUIET_WINDOW:
            m_videoDriver->draw2DRectangle(m_windowColour,dstRect);
            break;
        case TGUI_GRAPHICSDLG:
            m_videoDriver->draw2DRectangle(m_dialogColour,dstRect);
            break;
        default:
            m_videoDriver->draw2DImage(tex,dstRect,srcRect,clip,vcol,true);
        }


        if(!texture && style.hasHilight)
            drawElementStyle(element,style,rect,clip,m_hilightTex,pcolor);
        
    }

    //-----------------------------------------------------------------------
    //                     d r a w 2 D R e c t a n g l e
    //-----------------------------------------------------------------------
    void TGUISkin2::draw2DRectangle(IGUIElement* element, const video::SColor &color, 
        const core::rect<s32>& pos, const core::rect<s32>* clip)
    {
        m_defSkin->draw2DRectangle(element, color, pos, clip);
    }

}

