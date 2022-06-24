#pragma once

#include "Window.h"

namespace gr
{
    class Keyboard
    {
    public:
        enum Key
        {
            // Letters of alphabet

            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,

            // Numbers

            NUM0 = 48,
            NUM1 = 49,
            NUM2 = 50,
            NUM3 = 51,
            NUM4 = 52,
            NUM5 = 53,
            NUM6 = 54,
            NUM7 = 55,
            NUM8 = 56,
            NUM9 = 57,

            // Arrows

            RIGHT = 262,
            LEFT  = 263,
            UP    = 265,
            BACK  = 264,

            // F keys

            F1 = 290,
            F2 = 291,
            F3 = 292,
            F4 = 293,
            F5 = 294,
            F6 = 295,
            F7 = 296,
            F8 = 297,
            F9 = 298,
            F10 = 299,
            F11 = 300,
            F12 = 301,

            // Special

            SPACE = 32,
            ESCAPE = 256,
            ENTER = 257,
            TAB = 258,
            LSHIFT = 340,
            RSHIFT = 344,
            LALT = 342,
            RALT = 346,
        };

    public:
        static bool IsKeyPressed(Window* window, Key key);
    };
}