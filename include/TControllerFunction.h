//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#ifndef _TCONTROLLERFUNCTION_H_
#define _TCONTROLLERFUNCTION_H_

namespace Tubras
{
    /** Enumerates the wave types usable with the wave controller function. */
    enum TWaveformType
    {
        /// Standard sine wave which smoothly changes from low to high and back again.
        WFT_SINE,
        /// An angular wave with a constant increase / decrease speed with pointed peaks.
        WFT_TRIANGLE,
        /// Half of the time is spent at the min, half at the max with instant transition between.
        WFT_SQUARE,
        /// Gradual steady increase from min to max over the period with an instant return to min at the end.
        WFT_SAWTOOTH,
        /// Gradual steady decrease from max to min over the period, with an instant return to max at the end.
        WFT_INVERSE_SAWTOOTH,
        /// Pulse Width Modulation. Works like WFT_SQUARE, except the high to low transition is controlled by duty cycle. 
        /// With a duty cycle of 50% (0.5) will give the same output as WFT_SQUARE.
        WFT_PWM
    };


    /**
    TControllerFunction Class.
    @remarks
    ControllerFunction class - continuously calls a user specified function.
    */

    class TControllerFunction : public TDelegate
    {
    protected:
        float                   m_value;
    public:
        TControllerFunction();
        virtual ~TControllerFunction();

        virtual float update(const f32 deltaTime) {return m_value;};
        float getValue() {return m_value;};
        virtual void setValue(float value) {m_value = value;};
    };

    class TPassThroughControllerFunction : public TControllerFunction
    {
    public:
        virtual float update(const f32 delta);
    };

    class TWaveControllerFunction : public TControllerFunction
    {
    protected:
        TWaveformType           m_waveType;
        float                   m_base;
        float                   m_frequency;
        float                   m_phase;
        float                   m_amplitude;
        float                   m_dutyCycle;
        float                   m_elapsed;
    public:
        TWaveControllerFunction(TWaveformType wType, float base = 0, float frequency = 1, 
            float phase = 0, float amplitude = 1, float dutyCycle = 0.5);

        virtual float update(const f32 value);
    };
}
#endif

