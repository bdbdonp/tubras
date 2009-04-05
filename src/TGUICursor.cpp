//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine.
//
// Copyright (c) 2006-2009 Tubras Software, Ltd
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
    static struct {

        unsigned int 	 width;

        unsigned int 	 height;

        unsigned int 	 bytes_per_pixel; /* 3:RGB, 4:RGBA */ 

        unsigned char	 pixel_data[32 * 32 * 4];

    } _defCursor_ = {
        32, 32, 4,
        "\1\1\1\255\1\1\1\254\1\1\1\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\260\15\15\15\376\1\1\1"
        "\334\1\1\1""3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\1\1\1\263edd\364][[\361\4\4\4\367\1\1\1k\1\1\1\1\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\265ig"
        "g\364\271\266\266\343\206\204\204\342\21\21\21\372\1\1\1\251\1\1\1\17\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\270kii\364\271"
        "\266\266\343\271\266\266\330\246\243\243\321+**\357\1\1\1\332\1\1\1""1\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\273mkk\363\271\266\266"
        "\343\271\266\266\330\271\266\266\315\267\264\264\302POO\333\3\3\3\366\1\1"
        "\1g\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\276omm\363\271\266\266\343"
        "\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266\266{yy\301\15"
        "\15\15\366\1\1\1\246\1\1\1\15\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\301qoo\363\271"
        "\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266"
        "\266\271\266\266\253\237\234\234\252!!!\344\1\1\1\330\1\1\1/\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\1\1\1\303sqq\363\271\266\266\343\271\266\266\330\271\266\266\315\271"
        "\266\266\302\271\266\266\266\271\266\266\253\271\266\266\240\265\262\262"
        "\227BAA\306\2\2\2\364\1\1\1d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\306uss\363\271\266\266\343\271"
        "\266\266\330\271\266\266\315\271\266\266\302\271\266\266\266\271\266\266"
        "\253\271\266\266\240\271\266\266\225\271\266\266\212kii\242\11\11\11\362"
        "\1\1\1\242\1\1\1\14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\1\1\1\311wuu\363\271\266\266\343\271\266\266\330\271\266\266\315"
        "\271\266\266\302\271\266\266\266\271\266\266\253\271\266\266\240\271\266"
        "\266\225\271\266\266\212\271\266\266\177\224\222\222\202\30\30\30\332\1\1"
        "\1\326\1\1\1,\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1"
        "\1\314yww\362\271\266\266\343\271\266\266\330\271\266\266\315\271\266\266"
        "\302\271\266\266\266\271\266\266\253\271\266\266\240\271\266\266\225\271"
        "\266\266\212\271\266\266\177\271\266\266t\262\257\257k100\262\2\2\2\363\1"
        "\1\1a\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\317{yy\362\271"
        "\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266"
        "\266\271\266\266\253\271\266\266\240\271\266\266\225\271\266\266\212\271"
        "\266\266\177\271\266\266t\271\266\266i\271\266\266^UTT\204\6\6\6\357\1\1"
        "\1\237\1\1\1\13\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\321}{{\362\271\266\266"
        "\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266\266\271"
        "\266\266\253\271\266\266\240\271\266\266\225\271\266\266\212\271\266\266"
        "\177\271\266\266t\271\266\266i\271\266\266^\271\266\266S\201\177\177\\\16"
        "\16\16\321\1\1\1\323\1\1\1*\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\324\177}}\362\271"
        "\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271\266\266"
        "\266\271\266\266\253\271\266\266\240\271\266\266\225\271\266\266\212\271"
        "\266\266\177\271\266\266t\271\266\266i\271\266\266^\271\266\266S\271\266"
        "\266H\253\250\250@\34\34\34\237\1\1\1\361\1\1\1]\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\327"
        "\202\177\177\362\271\266\266\343\271\266\266\330\271\266\266\315\271\266"
        "\266\302\271\266\266\266\271\266\266\253\271\266\266\240\271\266\266\225"
        "\271\266\266\212\271\266\266\177\271\266\266t\271\266\266i\271\266\266^\271"
        "\266\266S\271\266\266H\271\266\266<\271\266\2661322g\3\3\3\355\1\1\1\234"
        "\1\1\1\12\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\1\1\1\332\204\202\202\362\271\266\266\343\271\266\266\330\271\266"
        "\266\315\271\266\266\302\271\266\266\266\271\266\266\253}{{\267MKK\305ED"
        "D\302>==\277666\275///\273(((\272\"!!\272\34\34\34\271\26\26\26\272\21\21"
        "\21\273\15\14\14\274\5\5\5\326\1\1\1\377\1\1\1\321\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\335\206\204\204"
        "\361\271\266\266\343\271\266\266\330\271\266\266\315\271\266\266\302\271"
        "\266\266\266\244\241\241\263\13\13\13\367\1\1\1\263\1\1\1\242\1\1\1\234\1"
        "\1\1\226\1\1\1\220\1\1\1\212\1\1\1\204\1\1\1~\1\1\1x\1\1\1r\1\1\1l\1\1\1"
        "f\1\1\1`\1\1\1Y\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\1\1\1\337\210\206\206\361\271\266\266\343\271\266\266\330"
        "\271\266\266\315\271\266\266\302\271\266\266\267211\343\1\1\1\257\1\1\1\1"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\342\212\210\210\361\271\266\266\343"
        "\271\266\266\330\271\266\266\315\271\266\266\302rpp\316\1\1\1\356\1\1\1\32"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\345\214\212\212\361\271\266"
        "\266\343\271\266\266\330\271\266\266\315\251\246\246\306\17\17\17\370\1\1"
        "\1`\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\350\216\214\214"
        "\361\271\266\266\343\271\266\266\330\271\266\266\315;;;\351\1\1\1\267\1\1"
        "\1\1\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\27\1\1\1q\1\1\1\237\1\1\1\233\1\1\1d\1"
        "\1\1\14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\352\220\216"
        "\216\361\271\266\266\343\271\266\266\330|zz\334\2\2\2\360\1\1\1\36\0\0\0"
        "\0\0\0\0\0\0\0\0\0\1\1\1Y\5\1\1\361U\1\1\377\221\0\0\377\213\0\0\377C\1\1"
        "\377\2\1\1\343\1\1\1:\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\355\222"
        "\220\220\361\271\266\266\343\255\252\252\332\23\23\23\371\1\1\1h\0\0\0\0"
        "\0\0\0\0\0\0\0\0\1\1\1F\22\1\1\374\304\0\0\377\377\0\0\377\377\0\0\377\377"
        "\0\0\377\377\0\0\377\245\0\0\377\5\1\1\360\1\1\1%\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\1\1\1\360\225\222\222\360\271\266\266\343EDD\360\1\1\1\275\1\1\1"
        "\2\0\0\0\0\0\0\0\0\1\1\1\1\1\1\1\325\245\0\0\377\377\0\0\377\377\0\0\377"
        "\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377x\0\0\377\1\1\1\251\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\363\227\224\224\360\205\203\203\353\2\2"
        "\2\363\1\1\1#\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1*\26\1\1\377\373\0\0\377\377\0"
        "\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\342\0"
        "\0\377\3\1\1\365\1\1\1\10\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\366\220\216\216\361"
        "\30\30\30\374\1\1\1o\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1J9\1\1\377\377"
        "\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377"
        "\0\0\377\376\0\0\377\16\1\1\377\1\1\1\36\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\370"
        "322\373\1\1\1\304\1\1\1\3\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1:&\1\1\377"
        "\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377"
        "\377\0\0\377\362\0\0\377\6\1\1\375\1\1\1\20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1"
        "\373\1\1\1\366\1\1\1(\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1\10\2"
        "\1\1\360\321\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377"
        "\0\0\377\377\0\0\377\245\0\0\377\1\1\1\313\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\1\1\1\376\1\1\1w\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\1\1\1|8\1\1\377\363\0\0\377\377\0\0\377\377\0\0\377\377\0\0\377\377\0"
        "\0\377\342\0\0\377\34\1\1\376\1\1\1P\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1"
        "\1\312\1\1\1\4\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1"
        "\1\1\4\1\1\1\251+\1\1\377\252\0\0\377\346\0\0\377\340\0\0\377\230\0\0\377"
        "\31\1\1\376\1\1\1\201\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1-\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1\1\1"
        "\2\1\1\1_\1\1\1\306\1\1\1\364\1\1\1\360\1\1\1\271\1\1\1F\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
        "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    };

    //-----------------------------------------------------------------------
    //                       T G U I C u r s o r
    //-----------------------------------------------------------------------
    TGUICursor::TGUICursor(IGUIEnvironment* environment) : TGUIImage(environment, 0, -1, 
        core::rect<s32>(0,0,32,32))
    {
#ifdef _DEBUG
        setDebugName("TGUICursor");
#endif
        setVisible(false);

        m_pos = vector2di(0,0);

        unsigned char*  pDest = _defCursor_.pixel_data;
        const unsigned char* pSrc  = _defCursor_.pixel_data;

        // convert to argb,
        for(size_t y = 0; y < _defCursor_.height; y++)
        {
            for(size_t x = 0; x < _defCursor_.width; x++)
            { 
                unsigned char r,g,b,a;
                r = *pSrc++; g = *pSrc++; b = *pSrc++; a=*pSrc++;
                *pDest++ = b;
                *pDest++ = g;
                *pDest++ = r;
                *pDest++ = a;
            }
        }

        m_defaultImage = getApplication()->getRenderer()->getVideoDriver()->createImageFromData(ECF_A8R8G8B8,
            dimension2d<u32>(32,32), (void*)&_defCursor_.pixel_data);

        m_screenSize = getApplication()->getRenderer()->getVideoDriver()->getScreenSize();

        m_defaultTexture = getApplication()->getRenderer()->getVideoDriver()->addTexture("defaultCursor", m_defaultImage);
        setImage(m_defaultTexture);
        this->setUseAlphaChannel(true);
        centerCursor();        
    }

    //-----------------------------------------------------------------------
    //                       ~ T G U I C u r s o r
    //-----------------------------------------------------------------------
    TGUICursor::~TGUICursor()
    {
        m_defaultImage->drop();
    }

    //-----------------------------------------------------------------------
    //                          s e t I m a g e
    //-----------------------------------------------------------------------
    void TGUICursor::setImage(video::ITexture* image)
    {
        TGUIImage::setImage(image);
        m_cursorSize = image->getSize();
    }

    //-----------------------------------------------------------------------
    //                       c e n t e r C u r s o r
    //-----------------------------------------------------------------------
    void TGUICursor::centerCursor()
    {
        setPosition(vector2di(m_screenSize.Width / 2, 
            m_screenSize.Height / 2));
    }

    //-----------------------------------------------------------------------
    //                       s e t P o s i t i o n
    //-----------------------------------------------------------------------
    void TGUICursor::setPosition(const vector2di& value) 
    {
        m_pos = value;
        setRelativePosition(m_pos);
    }

    //-----------------------------------------------------------------------
    //                        m o u s e M o v e d
    //-----------------------------------------------------------------------
    void TGUICursor::mouseMoved(const vector2di& relPos)
    {
        m_pos += relPos;
        if(m_pos.X < 0)
            m_pos.X = 0;

        if(m_pos.X+2 > (s32)m_screenSize.Width)
            m_pos.X = m_screenSize.Width-2;

        if(m_pos.Y < 0)
            m_pos.Y = 0;
        if(m_pos.Y+2 > (s32)m_screenSize.Height)
            m_pos.Y = m_screenSize.Height-2;

        setRelativePosition(m_pos);
    }
}
