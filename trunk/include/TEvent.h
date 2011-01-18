//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TEVENT_H_
#define _TEVENT_H_

namespace Tubras
{


    /** TEvent class. 
    @remarks
    This class should be used as a base class for user defined
    classes that want to receive event notifications.
    */
    class TEvent : public IReferenceCounted
    {
    protected:
        typedef array<TEventParameter*> TParameterList;
        TParameterList      m_parameters;

        TString             m_name;
        u32                 m_id;
        void*               m_userData;
    public:

        TEvent() : m_name(""), m_id(0), m_userData(0) {}
        TEvent(const TString& name);
        inline virtual ~TEvent();

        u32 setName(const TString &name);
        inline const char* getName() const;
        inline u32 getID() {return m_id;}
        inline void setID(u32 id) {m_id = id;}

        inline void setUserData(void* userData);
        inline void* getUserData();
        inline void resetUserData();

        inline void addParameter(TEventParameter* param);
        inline void addIntParameter(int value);
        inline void addDoubleParameter(double value);
        inline void addStringParameter(const TString& value);
        inline void addWStringParameter(const TStringW& value);
        inline void addPointerParameter(void* value);

        int getNumParameters() const {return (int)m_parameters.size();}
        TEventParameter* getParameter(int n);

    };

    inline TEvent::~TEvent()
    {
        for(u32 i=0;i<m_parameters.size();i++)
            m_parameters[i]->drop();
        m_parameters.clear();
    }

    inline const char* TEvent::getName() const
    {
        return (char *)m_name.c_str();
    }

    inline void TEvent::addParameter(TEventParameter* param)
    {
        m_parameters.push_back(param);
    }

    inline void TEvent::addIntParameter(int value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addDoubleParameter(double value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addStringParameter(const TString& value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addWStringParameter(const TStringW& value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::addPointerParameter(void* value)
    {
        m_parameters.push_back(new TEventParameter(value));
    }

    inline void TEvent::setUserData(void* userData)
    {
        m_userData = userData;
    }

    inline void* TEvent::getUserData()
    {
        return m_userData;
    }

    inline void TEvent::resetUserData()
    {
        m_userData = NULL;
    }


#define EVENT_DELEGATE(member) new Tubras::TEventDelegate(this,(Tubras::TEventDelegateFunction)&member)

    // Proxy Class
    class LEvent : public LProxyBase<TEvent> {
    public: 
        LEvent(const TEvent* other);
        LEvent(lua_State* L);

        ~LEvent();

        int getProperty(lua_State* L, const char* propName);

        static const TLuaProxy<LEvent>::RegType Register[];
    };
}
#endif

