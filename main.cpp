#include <iostream>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>


void drawTriangle();


int main()
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr<<"error initialising SDL\n";
        exit(EXIT_FAILURE);
    }

    SDL_Rect screenSize;

    SDL_GetDisplayBounds(0,&screenSize);

    SDL_Window *window = SDL_CreateWindow(
                "OpenGL Demo",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                screenSize.w/2,
                screenSize.h/2,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                );


    SDL_GLContext glContext;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    glContext=SDL_GL_CreateContext(window);

    //now make this the active context
    SDL_GL_MakeCurrent(window,glContext);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, (float)screenSize.w/screenSize.h,0.5,100);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2,2,2,  // Eye position
              0,0,0,  // Look at this position
              0,1,0   // Up axis
              );


    SDL_Event event;


    bool quit= false;
    while (!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch( event.type)
            {
            case SDL_QUIT :quit =true; break;
            }
        }
        drawTriangle();
        SDL_GL_SwapWindow(window);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    return EXIT_SUCCESS;
}

void drawTriangle()
{
    static int rot=0;
    glPushMatrix();
        glRotated(rot++,0, 1 , 0);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f , 0.0, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
        glEnd();
    glPopMatrix();
}


