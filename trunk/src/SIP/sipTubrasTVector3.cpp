/*
 * Interface wrapper code.
 *
 * Generated by SIP 4.6 (4.6) on Sat Apr 14 23:44:11 2007
 */
#line 13 "Tubras.sip"
	#include "tubras.h"
#line 9 "sipTubrasTVector3.cpp"

#include "sipAPITubras.h"
#include "sipTubrasTVector3.h"


/* Cast a pointer to a type somewhere in its superclass hierarchy. */
extern "C" {static void *cast_TVector3(void *, sipWrapperType *);}
static void *cast_TVector3(void *ptr,sipWrapperType *targetClass)
{
    if (targetClass == sipClass_TVector3)
        return ptr;

    return NULL;
}


/* Call the instance's destructor. */
extern "C" {static void release_TVector3(void *, int);}
static void release_TVector3(void *ptr,int)
{
    delete reinterpret_cast<TVector3 *>(ptr);
}


extern "C" {static void dealloc_TVector3(sipWrapper *);}
static void dealloc_TVector3(sipWrapper *sipSelf)
{
    if (sipIsPyOwned(sipSelf))
    {
        release_TVector3(sipSelf->u.cppPtr,0);
    }
}


extern "C" {static void *init_TVector3(sipWrapper *, PyObject *, sipWrapper **, int *);}
static void *init_TVector3(sipWrapper *,PyObject *sipArgs,sipWrapper **,int *sipArgsParsed)
{
    TVector3 *sipCpp = 0;

    if (!sipCpp)
    {
        if (sipParseArgs(sipArgsParsed,sipArgs,""))
        {
            sipCpp = new TVector3();
        }
    }

    if (!sipCpp)
    {
        float a0;
        float a1;
        float a2;

        if (sipParseArgs(sipArgsParsed,sipArgs,"fff",&a0,&a1,&a2))
        {
            sipCpp = new TVector3(a0,a1,a2);
        }
    }

    if (!sipCpp)
    {
        const TVector3 * a0;

        if (sipParseArgs(sipArgsParsed,sipArgs,"JA",sipClass_TVector3,&a0))
        {
            sipCpp = new TVector3(*a0);
        }
    }

    return sipCpp;
}


extern "C" {static void *forceConvertTo_TVector3(PyObject *, int *);}
static void *forceConvertTo_TVector3(PyObject *valobj,int *iserrp)
{
    if (*iserrp || valobj == NULL)
        return NULL;

    if (valobj == Py_None || sipIsSubClassInstance(valobj,sipClass_TVector3))
        return sipConvertToCpp(valobj,sipClass_TVector3,iserrp);

    sipBadClass(sipNm_Tubras_TVector3);

    *iserrp = 1;

    return NULL;
}


sipTypeDef sipType_Tubras_TVector3 = {
    0,
    0,
    "Tubras.TVector3",
    0,
    {0, 0, 1},
    0,
    0,
    0, 0,
    0, 0,
    0,
    init_TVector3,
    0,
    0,
    0,
    0,
    0,
    0,
    dealloc_TVector3,
    cast_TVector3,
    release_TVector3,
    forceConvertTo_TVector3,
    0,
    0,
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    0
};
