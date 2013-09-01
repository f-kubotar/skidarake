#ifndef __sometuke__color__
#define __sometuke__color__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

namespace sometuke {

struct Color3B {
    Color3B() {}
    Color3B(GLubyte red, GLubyte green, GLubyte blue)
        : r(red), g(green), b(blue) {}

    GLubyte r;
    GLubyte g;
    GLubyte b;

    const static Color3B WHITE;
    const static Color3B YELLOW;
    const static Color3B BLUE;
    const static Color3B GREEN;
    const static Color3B RED;
    const static Color3B MAGENTA;
    const static Color3B BLACK;
    const static Color3B ORANGE;
    const static Color3B GRAY;
};

struct Color4B {
    Color4B() {}
    Color4B(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
        : r(red), g(green), b(blue), a(alpha) {}
    Color4B(Color3B color3, GLubyte alpha)
        : r(color3.r), g(color3.g), b(color3.b), a(alpha) {}

    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;

    const static Color4B WHITE;
    const static Color4B YELLOW;
    const static Color4B BLUE;
    const static Color4B GREEN;
    const static Color4B RED;
    const static Color4B MAGENTA;
    const static Color4B BLACK;
    const static Color4B ORANGE;
    const static Color4B GRAY;
};

struct Color4F {
    Color4F() {}
    Color4F(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
        : r(red), g(green), b(blue), a(alpha) {}

    explicit Color4F(Color3B c) : r(c.r/255.f), g(c.g/255.f), b(c.b/255.f), a(1.f) {};
    explicit Color4F(Color4B c) : r(c.r/255.f), g(c.g/255.f), b(c.b/255.f), a(c.a/255.f) {};

    const GLfloat *Pointer() const {
        return &r;
    }

    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    const static Color4F WHITE;
    const static Color4F YELLOW;
    const static Color4F BLUE;
    const static Color4F GREEN;
    const static Color4F RED;
    const static Color4F MAGENTA;
    const static Color4F BLACK;
    const static Color4F ORANGE;
    const static Color4F GRAY;
};

// struct Color4B {
//     explicit Color4B(Color4F c) : r(c.r*255.f), g(c.g*255.f), b(c.b*255.f), a(c.a*255.f) {};
// };

}

#endif /* defined(__sometuke__color__) */
