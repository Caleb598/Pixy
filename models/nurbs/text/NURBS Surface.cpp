#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <ft2build.h>
#include FT_FREETYPE_H

const int WIDTH = 800;
const int HEIGHT = 600;

void renderTextOnSurface(const char* text, int fontSize, const char* fontPath) {
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

    float spacing = 0.2f;
    float x = -0.5f;
    float y = -0.5f;

    for (const char* c = text; *c; ++c) {
        if (FT_Load_Char(face, *c, FT_LOAD_RENDER)) {
            std::cerr << "Failed to load glyph for character '" << *c << "'" << std::endl;
            continue;
        }

        float x2 = x + g->bitmap_left * spacing;
        float y2 = y - g->bitmap_top * spacing;
        float w = g->bitmap.width * spacing;
        float h = g->bitmap.rows * spacing;

        float vertices[4][3] = {
            {x2, y2, 0},
            {x2 + w, y2, 0},
            {x2, y2 + h, 0},
            {x2 + w, y2 + h, 0}
        };

        float texCoords[4][2] = {
            {0, 0},
            {1, 0},
            {0, 1},
            {1, 1}
        };

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0); // Generate and bind your texture here

        glBegin(GL_QUADS);
        for (int i = 0; i < 4; ++i) {
            glTexCoord2f(texCoords[i][0], texCoords[i][1]);
            glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        glEnd();

        x += (g->advance.x >> 6) * spacing;
        y += (g->advance.y >> 6) * spacing;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    renderTextOnSurface("Hello, World!", 48, "/path/to/font.ttf");

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(width) / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Surface Text");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
