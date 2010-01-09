//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TINTERVALCONTROLLER_H_
#define _TINTERVALCONTROLLER_H_

namespace Tubras
{
    class TIntervalController : public TController
    {
    protected:
        float                   m_duration;
        float                   m_start;
        float                   m_stop;
        float                   m_length;
        float                   m_elapsed;
        float                   m_current;
        TBlendType              m_blendType;

    protected:
        float computeDelta(float t);

    public:
        TIntervalController(const TString& name, float start, float stop, float duration, 
            TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="");

        virtual ~TIntervalController();

        virtual void start() 
        {
            TController::start();
            m_elapsed = 0.f;
        }

        virtual void update(float deltaTime);

        virtual void intervalUpdate(float deltaTime) = 0;
    };

    class TFunctionInterval: public TIntervalController
    {
    protected:
        TIntervalDelegate*      m_delegate;
        const void*             m_userData;
    public:
        TFunctionInterval(TIntervalDelegate* delegate, const void* userData, 
            const TString& name, float start, float stop, 
            float duration, TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="") : 
        TIntervalController(name, start, stop, duration, blendType, startEvent, stopEvent),
            m_delegate(delegate), m_userData(userData) {}

        void intervalUpdate(float current)
        {
            if(m_delegate)
                m_delegate->Execute(current,(void *)m_userData);
        }
    };

    class TColorInterval : public TIntervalController
    {
    protected:
        TColor          m_color;
        s32             dr,dg,db,da;
        s32             sr,sg,sb,sa;
    public:
        TColorInterval(TColor color, TColor endColor,
            const TString& name, float start, float stop, 
            float duration, TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="") : 
        TIntervalController(name, start, stop, duration, blendType, startEvent, stopEvent),
            m_color(color)        
        {
            sr = color.getRed();
            sg = color.getGreen();
            sb = color.getBlue();
            sa = color.getAlpha();
            dr = endColor.getRed() - sr;
            dg = endColor.getGreen() - sg;
            db = endColor.getBlue() - sb;
            da = endColor.getAlpha() - sa;
        }

        void intervalUpdate(float current)
        {
            float t = current / m_duration;
            if(dr)
                m_color.setRed(core::clamp<u32>(sr + u32(t * dr), 0, 255));
            if(dg)
                m_color.setGreen(core::clamp<u32>(sg + u32(t * dg), 0, 255));
            if(db)
                m_color.setBlue(core::clamp<u32>(sb + u32(t * db), 0, 255));
            if(da)
                m_color.setAlpha(core::clamp<u32>(sa + u32(t * da), 0, 255));
        }
    };

    template<class T>
    class TValueInterval : public TIntervalController
    {
    protected:
        T       m_value;
        T       m_start;
        T       m_end;
        T       m_diff;

    public:
        TValueInterval(T& value, T endt,
            const TString& name, float start, float stop, 
            float duration, TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="") : 
        TIntervalController(name, start, stop, duration, blendType, startEvent, stopEvent),
            m_value(value), m_start(value), m_end(endt),
            m_diff(m_end - m_start)
        {
        }

        void reverse()
        {
            T s = m_start;
            m_start = m_end;
            m_end = s;
            m_diff = m_end - m_start;
        }

        virtual void intervalUpdate(float current) = 0;
    };

    typedef TValueInterval<f32> TValuef32Interval;
    typedef TValueInterval<s32> TValues32Interval;
    typedef TValueInterval<vector2di> TValueVector2diInterval;
    typedef TValueInterval<position2di> TValuePosition2diInterval;
    typedef TValueInterval<vector3df> TValueVector3dfInterval;


    class TNodePosInterval : public TValueVector3dfInterval
    {
    protected:
        ISceneNode*         m_node;
    public:
        TNodePosInterval(ISceneNode* node, vector3df startp, vector3df endp,
            const TString& name, float start, float stop, 
            float duration, TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="") : 
        TValueVector3dfInterval(startp, endp, name, start, stop, duration,
        blendType, startEvent, stopEvent),
        m_node(node)
        {
        }

        virtual void intervalUpdate(float current)
        {
            f32 delta = (current / m_duration);
            vector3df d;
            d.X = m_diff.X * delta;
            d.Y = m_diff.Y * delta;
            d.Z = m_diff.Z * delta;
            m_value = m_start + d;
            m_node->setPosition(m_value);
        }
    };

    class TGUIPosInterval : public TValuePosition2diInterval
    {
    protected:
        IGUIElement*    m_element;
    public:
        TGUIPosInterval(IGUIElement* element, position2di startp, position2di endp,
            const TString& name, float start, float stop, 
            float duration, TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="") : 
        TValuePosition2diInterval(startp, endp, name, start, stop, duration,
        blendType, startEvent, stopEvent),
        m_element(element)
        {
        }

        virtual void intervalUpdate(float current)
        {
            //TValueInterval<position2di>::intervalUpdate(current);

            f32 delta = (current / m_duration);
            position2di d;
            d.X = (s32) (m_diff.X * delta);
            d.Y = (s32) (m_diff.Y * delta);
            m_value = m_start + d;
            m_element->setRelativePosition(m_value);
        }
    };


    class TGUIImageColorInterval : public TColorInterval
    {
    protected:
        TGUIImage*        m_element;

    public:
        TGUIImageColorInterval(TGUIImage* element, TColor color, TColor endColor,
            const TString& name, float start, float stop, 
            float duration, TBlendType blendType=btNoBlend, 
            TString startEvent="", TString stopEvent="") : 
        TColorInterval(color, endColor, name, start, stop, duration, blendType, 
            startEvent, stopEvent), m_element(element) {}

        void intervalUpdate(float current);
    };

    typedef TIntervalController TInterval;

    #define INTERVAL_DELEGATE(member) new Tubras::TIntervalDelegate(this,(Tubras::TIntervalDelegateFunction)&member)


}

#endif

