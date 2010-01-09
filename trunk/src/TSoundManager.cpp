//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

#define INITIAL_VECTOR_SIZE   100
#define INCREASE_VECTOR_SIZE  20

#define DOPPLER_SCALE         1.0
#define DISTANCE_FACTOR       1.0
#define ROLLOFF_SCALE         0.5

namespace Tubras
{

    TSoundManager::TSoundManager()
    {
        //
        // todo: make these configurable
        //
        audio_cache_limit = 15;
        audio_doppler_factor = 1.0;
        audio_distance_factor = 1.0;
        audio_drop_off_factor = 1.0;
        m_listenerNode = 0;
    }

    TSoundManager::~TSoundManager()
    {

    }

    int TSoundManager::initialize()
    {
        return 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSoundManager::shutdown
    //       Access: Published, Virtual
    //  Description: Call this at exit time to shut down the audio system.
    //               This will invalidate all currently-active
    //               AudioManagers and AudioSounds in the system.  If you
    //               change your mind and want to play sounds again, you
    //               will have to recreate all of these objects.
    ////////////////////////////////////////////////////////////////////
    void TSoundManager::shutdown() 
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSoundManager::get_null_sound
    //       Access: Public
    //  Description: Returns a special NullAudioSound object that has all
    //               the interface of a normal sound object, but plays no
    //               sound.  This same object may also be returned by
    //               get_sound() if it fails.
    ////////////////////////////////////////////////////////////////////
    TSound* TSoundManager::getnullSound() 
    {
        return new TNullSound();
    }

    //-----------------------------------------------------------------------
    //                       a d d S o u n d N o d e
    //-----------------------------------------------------------------------
    void TSoundManager::addSoundNode(TSoundNode* node)
    {
        TSoundNodeList::Iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            if(node == *itr)
            {
                return;
            }
        }

        m_3dSounds.push_back(node);
    }

    //-----------------------------------------------------------------------
    //                    r e m o v e S o u n d N o d e
    //-----------------------------------------------------------------------
    void TSoundManager::removeSoundNode(TSoundNode* node)
    {
        TSoundNodeList::Iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            if(node == *itr)
            {
                m_3dSounds.erase(itr);
                return;
            }
        }
    }

    //-----------------------------------------------------------------------
    //                     s e t L i s t e n e r N o d e
    //-----------------------------------------------------------------------
    void TSoundManager::setListenerNode(ISceneNode* node) 
    {
        m_listenerNode = node;
        if(m_listenerNode)
        {
            TVector3 pos = m_listenerNode->getAbsolutePosition();
            TVector3 dir = m_listenerNode->getRotation();
            dir.normalize();

            setAudio3DListenerAttributes(pos.X,pos.Y,pos.Z,
                0.f,0.f,0.f,
                dir.X,dir.Y,dir.Z,
                0.f,1.f,0.f);
            m_listenerPos = pos;
            m_listenerDir = dir;
        }
    }

    //-----------------------------------------------------------------------
    //                           u p d a t e
    //-----------------------------------------------------------------------
    void TSoundManager::update()
    {
        if(m_listenerNode)
        {
            TVector3 pos = m_listenerNode->getPosition();
            // get the up vector
            TMatrix4 mat4 = m_listenerNode->getAbsoluteTransformation();
            TVector3 up(0.f, 1.f, 0.f);
            mat4.rotateVect(up);

            // and forward vector
            TVector3 dir(0.f, 0.f, 1.f);
            mat4.rotateVect(dir); 

            if( (pos != m_listenerPos) || (dir != m_listenerDir))
            {
                TVector3 vel = m_listenerPos - pos;
                setAudio3DListenerAttributes(pos.X,pos.Y,pos.Z,
                    vel.X,vel.Y,vel.Z,
                    dir.X,dir.Y,dir.Z,
                    up.X,up.Y,up.Z);
                m_listenerPos = pos;
                m_listenerDir = dir;
            }
        }

        TSoundNode* node;
        TSoundNodeList::Iterator itr;

        for(itr = m_3dSounds.begin();itr != m_3dSounds.end();itr++)
        {
            node = *itr;
            TVector3 pos = node->getPosition();

            node->getSound()->set3DAttributes(pos.X,pos.Y,pos.Z,0.f,0.f,0.f);
        }
    }
}

