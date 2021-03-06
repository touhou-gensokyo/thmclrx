/*
 * =====================================================================================
 *
 *       Filename:  common.cpp
 *
 *    Description:  common function
 *
 *        Version:  1.0
 *        Created:  2014/09/12 18时07分53秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  XadillaX (http://xcoder.in/), admin@xcoder.in
 *   Organization:  Touhou Gensokyo
 *
 * =====================================================================================
 */
#include <vector>
using namespace std;

#include "common.h"
#include "mindiffer.h"

namespace thmclrx
{
    TCX_MemoryPool<RGB> g_PoolRGB;
    TCX_MemoryPool<ColorCount> g_PoolColorCount;

    const Palette _rgb8bpp[256] = {
        { 0x00, 0x00, 0x00 },    /* 0 Sys Black      gray 0  */                          \
        { 0x80, 0x00, 0x00 },    /* 1 Sys Dk Red  */                                     \
        { 0x00, 0x80, 0x00 },    /* 2 Sys Dk Green  */                                   \
        { 0x80, 0x80, 0x00 },    /* 3 Sys Dk Yellow  */                                  \
        { 0x00, 0x00, 0x80 },    /* 4 Sys Dk Blue  */                                    \
        { 0x80, 0x00, 0x80 },    /* 5 Sys Dk Violet  */                                  \
        { 0x00, 0x80, 0x80 },    /* 6 Sys Dk Cyan  */                                    \
        { 0xc0, 0xc0, 0xc0 },    /* 7 Sys Lt Grey    gray 192  */                        \
        { 0xc0, 0xdc, 0xc0 },    /* 8 Sys 8  */                                          \
        { 0xa6, 0xca, 0xf0 },    /* 9 Sys 9 (the first 10 are fixed by Windows)  */      \
        { 0x00, 0x00, 0x33 },    /* 10       gray 4  */                                  \
        { 0x33, 0x00, 0x00 },    /* 11       gray 8  */                                  \
        { 0x33, 0x00, 0x33 },    /* 12       gray 12  */                                 \
        { 0x00, 0x33, 0x33 },    /* 13       gray 17  */                                 \
        { 0x16, 0x16, 0x16 },    /* 14       gray 22  */                                 \
        { 0x1c, 0x1c, 0x1c },    /* 15       gray 28  */                                 \
        { 0x22, 0x22, 0x22 },    /* 16       gray 34  */                                 \
        { 0x29, 0x29, 0x29 },    /* 17       gray 41  */                                 \
        { 0x55, 0x55, 0x55 },    /* 18 swapped so inversions look good       gray 85  */ \
        { 0x4d, 0x4d, 0x4d },    /* 19 swapped so inversions look good       gray 77  */ \
        { 0x42, 0x42, 0x42 },    /* 20 swapped so inversions look good       gray 66  */ \
        { 0x39, 0x39, 0x39 },    /* 21 swapped so inversions look good       gray 57  */ \
        { 0xFF, 0x7C, 0x80 },    /* 22 R255 G124 B128  */                                \
        { 0xFF, 0x50, 0x50 },    /* 23 R255 G80  B80  */                                 \
        { 0xD6, 0x00, 0x93 },    /* 24 R214 G0   B147  */                                \
        { 0xCC, 0xEC, 0xFF },    /* 25 R204 G236 B255  */                                \
        { 0xEF, 0xD6, 0xC6 },    /* 26 R239 G214 B198  */                                \
        { 0xE7, 0xE7, 0xD6 },    /* 27 R231 G231 B214  */                                \
        { 0xAD, 0xA9, 0x90 },    /* 28 R173 G169 B144  */                                \
        { 0x33, 0xff, 0x00 },    /* 29  */                                               \
        { 0x66, 0x00, 0x00 },    /* 30  */                                               \
        { 0x99, 0x00, 0x00 },    /* 31  */                                               \
        { 0xcc, 0x00, 0x00 },    /* 32  */                                               \
        { 0x00, 0x33, 0x00 },    /* 33  */                                               \
        { 0x33, 0x33, 0x00 },    /* 34  */                                               \
        { 0x66, 0x33, 0x00 },    /* 35  */                                               \
        { 0x99, 0x33, 0x00 },    /* 36  */                                               \
        { 0xcc, 0x33, 0x00 },    /* 37  */                                               \
        { 0xff, 0x33, 0x00 },    /* 38  */                                               \
        { 0x00, 0x66, 0x00 },    /* 39  */                                               \
        { 0x33, 0x66, 0x00 },    /* 40  */                                               \
        { 0x66, 0x66, 0x00 },    /* 41  */                                               \
        { 0x99, 0x66, 0x00 },    /* 42  */                                               \
        { 0xcc, 0x66, 0x00 },    /* 43  */                                               \
        { 0xff, 0x66, 0x00 },    /* 44  */                                               \
        { 0x00, 0x99, 0x00 },    /* 45  */                                               \
        { 0x33, 0x99, 0x00 },    /* 46  */                                               \
        { 0x66, 0x99, 0x00 },    /* 47  */                                               \
        { 0x99, 0x99, 0x00 },    /* 48  */                                               \
        { 0xcc, 0x99, 0x00 },    /* 49  */                                               \
        { 0xff, 0x99, 0x00 },    /* 50  */                                               \
        { 0x00, 0xcc, 0x00 },    /* 51  */                                               \
        { 0x33, 0xcc, 0x00 },    /* 52  */                                               \
        { 0x66, 0xcc, 0x00 },    /* 53  */                                               \
        { 0x99, 0xcc, 0x00 },    /* 54  */                                               \
        { 0xcc, 0xcc, 0x00 },    /* 55  */                                               \
        { 0xff, 0xcc, 0x00 },    /* 56  */                                               \
        { 0x66, 0xff, 0x00 },    /* 57  */                                               \
        { 0x99, 0xff, 0x00 },    /* 58  */                                               \
        { 0xcc, 0xff, 0x00 },    /* 59  */                                               \
        { 0x00, 0xff, 0x33 },    /* 60  */                                               \
        { 0x33, 0x00, 0xff },    /* 61  */                                               \
        { 0x66, 0x00, 0x33 },    /* 62  */                                               \
        { 0x99, 0x00, 0x33 },    /* 63  */                                               \
        { 0xcc, 0x00, 0x33 },    /* 64  */                                               \
        { 0xff, 0x00, 0x33 },    /* 65  */                                               \
        { 0x00, 0x33, 0xff },    /* 66  */                                               \
        { 0x33, 0x33, 0x33 },    /* 67       gray 51  */                                 \
        { 0x66, 0x33, 0x33 },    /* 68  */                                               \
        { 0x99, 0x33, 0x33 },    /* 69  */                                               \
        { 0xcc, 0x33, 0x33 },    /* 70  */                                               \
        { 0xff, 0x33, 0x33 },    /* 71  */                                               \
        { 0x00, 0x66, 0x33 },    /* 72  */                                               \
        { 0x33, 0x66, 0x33 },    /* 73  */                                               \
        { 0x66, 0x66, 0x33 },    /* 74  */                                               \
        { 0x99, 0x66, 0x33 },    /* 75  */                                               \
        { 0xcc, 0x66, 0x33 },    /* 76  */                                               \
        { 0xff, 0x66, 0x33 },    /* 77  */                                               \
        { 0x00, 0x99, 0x33 },    /* 78  */                                               \
        { 0x33, 0x99, 0x33 },    /* 79  */                                               \
        { 0x66, 0x99, 0x33 },    /* 80  */                                               \
        { 0x99, 0x99, 0x33 },    /* 81  */                                               \
        { 0xcc, 0x99, 0x33 },    /* 82  */                                               \
        { 0xff, 0x99, 0x33 },    /* 83  */                                               \
        { 0x00, 0xcc, 0x33 },    /* 84  */                                               \
        { 0x33, 0xcc, 0x33 },    /* 85  */                                               \
        { 0x66, 0xcc, 0x33 },    /* 86  */                                               \
        { 0x99, 0xcc, 0x33 },    /* 87  */                                               \
        { 0xcc, 0xcc, 0x33 },    /* 88  */                                               \
        { 0xff, 0xcc, 0x33 },    /* 89  */                                               \
        { 0x33, 0xff, 0x33 },    /* 90  */                                               \
        { 0x66, 0xff, 0x33 },    /* 91  */                                               \
        { 0x99, 0xff, 0x33 },    /* 92  */                                               \
        { 0xcc, 0xff, 0x33 },    /* 93  */                                               \
        { 0xff, 0xff, 0x33 },    /* 94  */                                               \
        { 0x00, 0x00, 0x66 },    /* 95  */                                               \
        { 0x33, 0x00, 0x66 },    /* 96  */                                               \
        { 0x66, 0x00, 0x66 },    /* 97  */                                               \
        { 0x99, 0x00, 0x66 },    /* 98  */                                               \
        { 0xcc, 0x00, 0x66 },    /* 99  */                                               \
        { 0xff, 0x00, 0x66 },    /* 100  */                                              \
        { 0x00, 0x33, 0x66 },    /* 101  */                                              \
        { 0x33, 0x33, 0x66 },    /* 102  */                                              \
        { 0x66, 0x33, 0x66 },    /* 103  */                                              \
        { 0x99, 0x33, 0x66 },    /* 104  */                                              \
        { 0xcc, 0x33, 0x66 },    /* 105  */                                              \
        { 0xff, 0x33, 0x66 },    /* 106  */                                              \
        { 0x00, 0x66, 0x66 },    /* 107  */                                              \
        { 0x33, 0x66, 0x66 },    /* 108  */                                              \
        { 0x66, 0x66, 0x66 },    /* 109      gray 102  */                                \
        { 0x99, 0x66, 0x66 },    /* 110  */                                              \
        { 0xcc, 0x66, 0x66 },    /* 111  */                                              \
        { 0x00, 0x99, 0x66 },    /* 112  */                                              \
        { 0x33, 0x99, 0x66 },    /* 113  */                                              \
        { 0x66, 0x99, 0x66 },    /* 114  */                                              \
        { 0x99, 0x99, 0x66 },    /* 115  */                                              \
        { 0xcc, 0x99, 0x66 },    /* 116  */                                              \
        { 0xff, 0x99, 0x66 },    /* 117  */                                              \
        { 0x00, 0xcc, 0x66 },    /* 118  */                                              \
        { 0x33, 0xcc, 0x66 },    /* 119  */                                              \
        { 0x99, 0xcc, 0x66 },    /* 120  */                                              \
        { 0xcc, 0xcc, 0x66 },    /* 121  */                                              \
        { 0xff, 0xcc, 0x66 },    /* 122  */                                              \
        { 0x00, 0xff, 0x66 },    /* 123  */                                              \
        { 0x33, 0xff, 0x66 },    /* 124  */                                              \
        { 0x99, 0xff, 0x66 },    /* 125  */                                              \
        { 0xcc, 0xff, 0x66 },    /* 126  */                                              \
        { 0xff, 0x00, 0xcc },    /* 127  */                                              \
        { 0xcc, 0x00, 0xff },    /* 128  */                                              \
        { 0x00, 0x99, 0x99 },    /* 129  */                                              \
        { 0x99, 0x33, 0x99 },    /* 130  */                                              \
        { 0x99, 0x00, 0x99 },    /* 131  */                                              \
        { 0xcc, 0x00, 0x99 },    /* 132  */                                              \
        { 0x00, 0x00, 0x99 },    /* 133  */                                              \
        { 0x33, 0x33, 0x99 },    /* 134  */                                              \
        { 0x66, 0x00, 0x99 },    /* 135  */                                              \
        { 0xcc, 0x33, 0x99 },    /* 136  */                                              \
        { 0xff, 0x00, 0x99 },    /* 137  */                                              \
        { 0x00, 0x66, 0x99 },    /* 138  */                                              \
        { 0x33, 0x66, 0x99 },    /* 139  */                                              \
        { 0x66, 0x33, 0x99 },    /* 140  */                                              \
        { 0x99, 0x66, 0x99 },    /* 141  */                                              \
        { 0xcc, 0x66, 0x99 },    /* 142  */                                              \
        { 0xff, 0x33, 0x99 },    /* 143  */                                              \
        { 0x33, 0x99, 0x99 },    /* 144  */                                              \
        { 0x66, 0x99, 0x99 },    /* 145  */                                              \
        { 0x99, 0x99, 0x99 },    /* 146      gray 153  */                                \
        { 0xcc, 0x99, 0x99 },    /* 147  */                                              \
        { 0xff, 0x99, 0x99 },    /* 148  */                                              \
        { 0x00, 0xcc, 0x99 },    /* 149  */                                              \
        { 0x33, 0xcc, 0x99 },    /* 150  */                                              \
        { 0x66, 0xcc, 0x66 },    /* 151  */                                              \
        { 0x99, 0xcc, 0x99 },    /* 152  */                                              \
        { 0xcc, 0xcc, 0x99 },    /* 153  */                                              \
        { 0xff, 0xcc, 0x99 },    /* 154  */                                              \
        { 0x00, 0xff, 0x99 },    /* 155  */                                              \
        { 0x33, 0xff, 0x99 },    /* 156  */                                              \
        { 0x66, 0xcc, 0x99 },    /* 157  */                                              \
        { 0x99, 0xff, 0x99 },    /* 158  */                                              \
        { 0xcc, 0xff, 0x99 },    /* 159  */                                              \
        { 0xff, 0xff, 0x99 },    /* 160  */                                              \
        { 0x00, 0x00, 0xcc },    /* 161  */                                              \
        { 0x33, 0x00, 0x99 },    /* 162  */                                              \
        { 0x66, 0x00, 0xcc },    /* 163  */                                              \
        { 0x99, 0x00, 0xcc },    /* 164  */                                              \
        { 0xcc, 0x00, 0xcc },    /* 165  */                                              \
        { 0x00, 0x33, 0x99 },    /* 166  */                                              \
        { 0x33, 0x33, 0xcc },    /* 167  */                                              \
        { 0x66, 0x33, 0xcc },    /* 168  */                                              \
        { 0x99, 0x33, 0xcc },    /* 169  */                                              \
        { 0xcc, 0x33, 0xcc },    /* 170  */                                              \
        { 0xff, 0x33, 0xcc },    /* 171  */                                              \
        { 0x00, 0x66, 0xcc },    /* 172  */                                              \
        { 0x33, 0x66, 0xcc },    /* 173  */                                              \
        { 0x66, 0x66, 0x99 },    /* 174  */                                              \
        { 0x99, 0x66, 0xcc },    /* 175  */                                              \
        { 0xcc, 0x66, 0xcc },    /* 176  */                                              \
        { 0xff, 0x66, 0x99 },    /* 177  */                                              \
        { 0x00, 0x99, 0xcc },    /* 178  */                                              \
        { 0x33, 0x99, 0xcc },    /* 179  */                                              \
        { 0x66, 0x99, 0xcc },    /* 180  */                                              \
        { 0x99, 0x99, 0xcc },    /* 181  */                                              \
        { 0xcc, 0x99, 0xcc },    /* 182  */                                              \
        { 0xff, 0x99, 0xcc },    /* 183  */                                              \
        { 0x00, 0xcc, 0xcc },    /* 184  */                                              \
        { 0x33, 0xcc, 0xcc },    /* 185  */                                              \
        { 0x66, 0xcc, 0xcc },    /* 186  */                                              \
        { 0x99, 0xcc, 0xcc },    /* 187  */                                              \
        { 0xcc, 0xcc, 0xcc },    /* 188      gray 204  */                                \
        { 0xff, 0xcc, 0xcc },    /* 189  */                                              \
        { 0x00, 0xff, 0xcc },    /* 190  */                                              \
        { 0x33, 0xff, 0xcc },    /* 191  */                                              \
        { 0x66, 0xff, 0x99 },    /* 192  */                                              \
        { 0x99, 0xff, 0xcc },    /* 193  */                                              \
        { 0xcc, 0xff, 0xcc },    /* 194  */                                              \
        { 0xff, 0xff, 0xcc },    /* 195  */                                              \
        { 0x33, 0x00, 0xcc },    /* 196  */                                              \
        { 0x66, 0x00, 0xff },    /* 197  */                                              \
        { 0x99, 0x00, 0xff },    /* 198  */                                              \
        { 0x00, 0x33, 0xcc },    /* 199  */                                              \
        { 0x33, 0x33, 0xff },    /* 200  */                                              \
        { 0x66, 0x33, 0xff },    /* 201  */                                              \
        { 0x99, 0x33, 0xff },    /* 202  */                                              \
        { 0xcc, 0x33, 0xff },    /* 203  */                                              \
        { 0xff, 0x33, 0xff },    /* 204  */                                              \
        { 0x00, 0x66, 0xff },    /* 205  */                                              \
        { 0x33, 0x66, 0xff },    /* 206  */                                              \
        { 0x66, 0x66, 0xcc },    /* 207  */                                              \
        { 0x99, 0x66, 0xff },    /* 208  */                                              \
        { 0xcc, 0x66, 0xff },    /* 209  */                                              \
        { 0xff, 0x66, 0xcc },    /* 210  */                                              \
        { 0x00, 0x99, 0xff },    /* 211  */                                              \
        { 0x33, 0x99, 0xff },    /* 212  */                                              \
        { 0x66, 0x99, 0xff },    /* 213  */                                              \
        { 0x99, 0x99, 0xff },    /* 214  */                                              \
        { 0xcc, 0x99, 0xff },    /* 215  */                                              \
        { 0xff, 0x99, 0xff },    /* 216  */                                              \
        { 0x00, 0xcc, 0xff },    /* 217  */                                              \
        { 0x33, 0xcc, 0xff },    /* 218  */                                              \
        { 0x66, 0xcc, 0xff },    /* 219  */                                              \
        { 0x99, 0xcc, 0xff },    /* 220  */                                              \
        { 0xcc, 0xcc, 0xff },    /* 221  */                                              \
        { 0xff, 0xcc, 0xff },    /* 222  */                                              \
        { 0x33, 0xff, 0xff },    /* 223  */                                              \
        { 0x66, 0xff, 0xcc },    /* 224  */                                              \
        { 0x99, 0xff, 0xff },    /* 225  */                                              \
        { 0xcc, 0xff, 0xff },    /* 226  */                                              \
        { 0xff, 0x66, 0x66 },    /* 227  */                                              \
        { 0x66, 0xff, 0x66 },    /* 228  */                                              \
        { 0xff, 0xff, 0x66 },    /* 229  */                                              \
        { 0x66, 0x66, 0xff },    /* 230  */                                              \
        { 0xff, 0x66, 0xff },    /* 231  */                                              \
        { 0x66, 0xff, 0xff },    /* 232  */                                              \
        { 0xA5, 0x00, 0x21 },    /* 233      R165 G0 B33  */                             \
        { 0x5f, 0x5f, 0x5f },    /* 234      gray 95  */                                 \
        { 0x77, 0x77, 0x77 },    /* 235      gray 119  */                                \
        { 0x86, 0x86, 0x86 },    /* 236      gray 134  */                                \
        { 0x96, 0x96, 0x96 },    /* 237      gray 150  */                                \
        { 0xcb, 0xcb, 0xcb },    /* 238      gray 203  */                                \
        { 0xb2, 0xb2, 0xb2 },    /* 239      gray 178  */                                \
        { 0xd7, 0xd7, 0xd7 },    /* 240      gray 215  */                                \
        { 0xdd, 0xdd, 0xdd },    /* 241      gray 221  */                                \
        { 0xe3, 0xe3, 0xe3 },    /* 242      gray 227  */                                \
        { 0xea, 0xea, 0xea },    /* 243      gray 234  */                                \
        { 0xf1, 0xf1, 0xf1 },    /* 244      gray 241  */                                \
        { 0xf8, 0xf8, 0xf8 },    /* 245      gray 248  */                                \
        { 0xff, 0xfb, 0xf0 },    /* 246 Sys Reserved  */                                 \
        { 0xa0, 0xa0, 0xa4 },    /* 247 Sys Reserved  */                                 \
        { 0x80, 0x80, 0x80 },    /* 248 Sys Lt Gray  gray 128  */                        \
        { 0xff, 0x00, 0x00 },    /* 249 Sys Red  */                                      \
        { 0x00, 0xff, 0x00 },    /* 250 Sys Green  */                                    \
        { 0xff, 0xff, 0x00 },    /* 251 Sys Yellow  */                                   \
        { 0x00, 0x00, 0xff },    /* 252 Sys Blue  */                                     \
        { 0xff, 0x00, 0xff },    /* 253 Sys Violet  */                                   \
        { 0x00, 0xff, 0xff },    /* 254 Sys Cyan  */                                     \
        { 0xff, 0xff, 0xff }     /* 255 Sys White     gray 255  */                       \
    };

    void Palette::GetDefaultPalette(vector<Palette>* palette)
    {
        palette->clear();
        for(int i = 0; i < 256; i++)
        {
            palette->push_back(_rgb8bpp[i]);
        }
    }

    void Palette::V8ToPalette(Local<Value> value, vector<Palette>* palette)
    {
        HandleScope scope;

        Local<String> symbolR = String::New("r");
        Local<String> symbolG = String::New("g");
        Local<String> symbolB = String::New("b");

        if(!value->IsArray())
        {
            GetDefaultPalette(palette);
            scope.Close(Undefined());
            return;
        }

        Local<Array> array = Local<Array>::Cast(value);

        for(int i = 0; i < array->Length(); i++)
        {
            if(!array->Get(i)->IsObject())
            {
                GetDefaultPalette(palette);
                scope.Close(Undefined());
                return;
            }

            Local<Object> obj = array->Get(i)->ToObject();
            if(!obj->Get(symbolR)->IsInt32() || !obj->Get(symbolG)->IsInt32() || !obj->Get(symbolB)->IsInt32())
            {
                GetDefaultPalette(palette);
                scope.Close(Undefined());
                return;
            }

            Palette p = { obj->Get(symbolR)->ToInt32()->Value(), obj->Get(symbolG)->ToInt32()->Value(), obj->Get(symbolB)->ToInt32()->Value() };
            palette->push_back(p);
        }

        scope.Close(Undefined());
        return;
    }
};

