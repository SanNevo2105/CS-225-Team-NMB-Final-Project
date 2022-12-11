#pragma once
#include "/workspaces/CS-225-Team-NMB-Final-Project/lib/cs225/PNG.h"

/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
 class Image: public cs225::PNG {
    public:
        void lighten ();
        void lighten (double amount);
        void darken ();
        void darken (double amount);
        void saturate ();
        void saturate (double amount);
        void desaturate ();
        void desaturate (double amount);
        void grayscale ();
        void rotateColor (double degrees);
        void illinify ();
        void scale (double factor);
        void scale (unsigned w, unsigned h);
 };

