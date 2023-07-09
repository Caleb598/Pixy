#include <iostream>
#include <cmath>
#include <ft2build.h>
#include FT_FREETYPE_H

const int WIDTH = 800;
const int HEIGHT = 600;

void renderTextOnCurve(const char* text, int fontSize, const char* fontPath, float curveRadius) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Failed to initialize FreeType library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    FT_GlyphSlot g = face->glyph;

    float angleStep = (2 * M_PI) / strlen(text);
    float angle = 0.0f;

    for (const char* c = text; *c; ++c) {
        if (FT_Load_Char(face, *c, FT_LOAD_RENDER)) {
            std::cerr << "Failed to load glyph for character '" << *c << "'" << std::endl;
            continue;
        }

        glPushMatrix();
        glTranslatef(cos(angle) * curveRadius, sin(angle) * curveRadius, 0);
        glRotatef(angle * 180.0f / M_PI, 0, 0, 1);

        glTranslatef(-g->bitmap.width / 2, -g->bitmap.rows / 2, 0);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        glPushMatrix();
        glScalef(1.0f, -1.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(g->bitmap.width, 0);
        glTexCoord2f(1, 1); glVertex2f(g->bitmap.width, g->bitmap.rows);
        glTexCoord2f(0, 1); glVertex2f(0, g->bitmap.rows);
        glEnd();
        glPopMatrix();

        glPopMatrix();

        angle += angleStep;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    renderTextOnCurve("Hello, World!", 48, "/path/to/font.ttf", 200.0f);

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Curved Text");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
