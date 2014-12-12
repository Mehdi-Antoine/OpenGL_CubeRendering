#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <iostream>

using namespace glimac;

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 700

int TAILLE = 10;

//--------------------------------------------------------------------------------------------------
//--------------------------------------STRUCTURES--------------------------------------------------
//--------------------------------------------------------------------------------------------------

struct MyProgram {
    Program m_Program;

    GLint uMVPMatrix,
          uMVMatrix,
          uPMatrix;

    MyProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3Dtest.vs.glsl",
                              applicationPath.dirPath() + "shaders/3Dtest.fs.glsl",
                              applicationPath.dirPath() + "shaders/3Dtest2.gs.glsl")) {

        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uPMatrix = glGetUniformLocation(m_Program.getGLId(), "uPMatrix");

    }
};

//--------------------------------------------------------------------------------------------------
//---------------------------------------LE MAIN----------------------------------------------------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

    float currentTime;
    float lastTime;
    int nbFrames = 0;

    //Création des variables clavier et souris SDL
    int key_z = 0, 
        key_s = 0,
        key_q = 0,
        key_d = 0,
        key_v = 0,
        click = 0;

    bool freefly = false;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

//--------------------------------------------------------------------------------------------------
//-------------CONSTRUCTION CUBE ET INJECTION DANS UN TABLEAU DE VERTICES-------------------------
//--------------------------------------------------------------------------------------------------

    glm::vec3 cube_color;
    glm::vec3 cube_position;

    cube_color = glm::sphericalRand(1.);
    cube_position = glm::vec3(0,0,0);

//--------------------------------------------------------------------------------------------------
//---------------------------------CONSTRUCTION CAMERA----------------------------------------------
//--------------------------------------------------------------------------------------------------

    TrackballCamera trackballCamera;
    FreeflyCamera freeflyCamera;

//--------------------------------------------------------------------------------------------------
//-------------------------------CHARGEMENT DES SHADERS---------------------------------------------
//--------------------------------------------------------------------------------------------------

    FilePath applicationPath(argv[0]);

    MyProgram program(applicationPath);

//--------------------------------------------------------------------------------------------------
//--------------------------CREATION DES VARIABLES UNIFORMES----------------------------------------
//--------------------------------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    glm::mat4  ProjMatrix, 
               MVMatrix,
               MVPMatrix;

    ProjMatrix = glm::perspective(glm::radians(50.f), (float)WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 1000.f);
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0., 0., -5.));
    MVPMatrix = ProjMatrix * MVMatrix;


    glUniformMatrix4fv(program.uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(program.uMVPMatrix,    1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(program.uPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix));

//--------------------------------------------------------------------------------------------------
//-----------------------------CHARGEMENT DU VBO ET DU VAO------------------------------------------
//--------------------------------------------------------------------------------------------------

    GLuint vbo_cube_color;
    GLuint vbo_cube_position;

    glGenBuffers(1, &vbo_cube_color);
    glGenBuffers(1, &vbo_cube_position);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_color);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), glm::value_ptr(cube_color), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_position);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), glm::value_ptr(cube_position), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_position);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_color);  
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*
    -param1 : index de l'attribut à spécifier
    -param2 : le nombre de composante de l'attribut (=nombre de cases dans le tableau pour définir un attribut)
    -param3 : le type de chaque composante
    -param4 : mystere pour le moment
    -param5 : le nombre de cases à sauter avant de passer à la composante suivante de l'attribut
    -param6 : offset de la première instance de l'attribut
    */

    glBindVertexArray(0);
    

//--------------------------------------------------------------------------------------------------
//----------------------------------APPLICATION LOOP------------------------------------------------
//--------------------------------------------------------------------------------------------------

    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(e.type == SDL_KEYDOWN){

                if(e.key.keysym.sym == SDLK_ESCAPE){
                    done = true;
                }  

                if(e.key.keysym.sym == SDLK_z){
                    key_z = 1;
                }                 
                if(e.key.keysym.sym == SDLK_s){
                    key_s = 1;
                }
                if(e.key.keysym.sym == SDLK_q){
                    key_q = 1;
                }                 
                if(e.key.keysym.sym == SDLK_d){
                    key_d = 1;
                }
                if(e.key.keysym.sym == SDLK_p){
                    TAILLE++;
                    std::cout << "TAILLE = " << TAILLE << std::endl;
                }
                if(e.key.keysym.sym == SDLK_m){
                    TAILLE--;
                    if(TAILLE <= 0) TAILLE = 1;

                    std::cout << "TAILLE = " << TAILLE << std::endl;
                }
                if(e.key.keysym.sym == SDLK_v){
                    if(freefly == true){
                       freefly = false; 
                    }
                    else{
                       freefly = true; 
                    }
                    
                }
                    
            }

            if(e.type == SDL_KEYUP){
                    
                if(e.key.keysym.sym == SDLK_z){
                    key_z = 0;
                }           
                if(e.key.keysym.sym == SDLK_s){
                    key_s = 0;
                }
                if(e.key.keysym.sym == SDLK_q){
                    key_q = 0;
                }                 
                if(e.key.keysym.sym == SDLK_d){
                    key_d = 0;
                }
                    
            }

            if(e.type == SDL_MOUSEBUTTONDOWN){
                click = 1;
            }

            if(e.type == SDL_MOUSEBUTTONUP){
                click = 0;
            }

            if(e.type == SDL_MOUSEMOTION){
                if(e.motion.xrel != 0 && click == 1){
                    //std::cout << e.motion.xrel << std::endl;
                    trackballCamera.rotateLeft(e.motion.xrel/2.);
                    freeflyCamera.rotateLeft(-e.motion.xrel/2.);
                }
                if(e.motion.yrel != 0 && click == 1){
                    //std::cout << e.motion.xrel << std::endl;
                    trackballCamera.rotateUp(e.motion.yrel/2.);
                    freeflyCamera.rotateUp(-e.motion.yrel/2.);
                }
            }

        }

        if(key_z && !key_s){
            trackballCamera.moveFront(-2);
            freeflyCamera.moveFront(2);
        }
        if(key_s && !key_z){
            trackballCamera.moveFront(2);
            freeflyCamera.moveFront(-2);
        }
        if(key_q && !key_d){
            freeflyCamera.moveLeft(2);
        }
        if(key_d && !key_q){
            freeflyCamera.moveLeft(-2);
        }

//--------------------------------------------------------------------------------------------------
//-----------------------------------RENDERING CODE-------------------------------------------------
//--------------------------------------------------------------------------------------------------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);

        //DESSIN DE LA TERRE
        program.m_Program.use();

        for(int i = 0; i<TAILLE; ++i){
            for(int j=0; j<TAILLE; ++j){

                //CONSTRUCTION MATRICE V
                MVMatrix = freefly? freeflyCamera.getViewMatrix() : trackballCamera.getViewMatrix();
                //CONSTRUCTION MATRICE MV
                MVMatrix = glm::translate(MVMatrix, glm::vec3(2*i, 0, 2*j));
                //MVMatrix = glm::rotate(MVMatrix, (float)(M_PI * i), glm::vec3(0, 0, 1));
                //MVMatrix = glm::rotate(MVMatrix, (float)(M_PI * j), glm::vec3(0, 0, 1));

                //CONSTRUCTION MATRICE MVP
                MVPMatrix = ProjMatrix * MVMatrix;

                //ENVOI DES NOUVELLES VALEURS AUX UNIFORMS
                glUniformMatrix4fv(program.uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(program.uMVPMatrix,    1, GL_FALSE, glm::value_ptr(MVPMatrix));
                glUniformMatrix4fv(program.uPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix));

                //DESSIN
                //cube_position = glm::vec3(i, 0, j);
                cube_color = glm::vec3((float)(i+3)/(TAILLE+10),(float)j/(TAILLE+10),(float)(i+j)/(TAILLE+10)*2);//glm::sphericalRand(1.0);

                //glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_position);
                //glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), glm::value_ptr(cube_position), GL_STATIC_DRAW);
                //glBindBuffer(GL_ARRAY_BUFFER, 0);

                glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_color);
                glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), glm::value_ptr(cube_color), GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glDrawArrays(GL_POINTS, 0, 1);

            }

            ++nbFrames;

            currentTime = windowManager.getTime();

            //std::cout << nbFrames / windowManager.getTime() << std::endl;

            float ellapsedTime = currentTime - lastTime;
            if(ellapsedTime >= 1){

                float res = ellapsedTime / nbFrames;

                if(res > 0.04){
                    std::cout << "Warning ! : ";
                }

                std::cout << res << " sec" << std::endl;
                std::cout << 1 / res << " fps" << std::endl;

                nbFrames = 0;

                lastTime = windowManager.getTime();
            }

        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();

        glFinish();
        glFlush();
    }

    glDeleteBuffers(1, &vbo_cube_position);
    glDeleteBuffers(1, &vbo_cube_color);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
