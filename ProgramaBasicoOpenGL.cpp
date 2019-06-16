// **********************************************************************
// PUCRS/Escola Politécnica
// COMPUTAÇÃO GRÁFICA
//
// Programa básico para criar aplicacoes 3D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <Vector3.h>
#include <Camera.h>
#include <Triangle.h>
#include <Model.h>
#include <GameManager.h>
#include <Player.h>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include "gl\glut.h"
    static DWORD last_idle_time;
#else
    #include <sys/time.h>
    static struct timeval last_idle_time;
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

enum STATUS{GAMEOVER,INGAME};
STATUS status = INGAME;
GLfloat AspectRatio, AngY=0;
GameManager ga = GameManager();
Player player = Player(10);
Model model;
float deltaTime = 0;
bool debug = false;
bool godMode = false;

bool IsColliding(Object &obj1, Object &obj2);
void LoadModel(Model &model, const char* name);
void DrawModel(const Model &model);
void DrawTriangle(const Triangle &triangle);
void SetColor(string hex, ColorRGB &colorRGB);
void GetNormalVector(Triangle &triangle);
void ProdVector(const Vector3* v1, const Vector3* v2, Vector3 &prodVect);
void MovePlayer();
void DrawGUI();
void Process();
void GameOver();

// **********************************************************************
// void GameOver()
// Renderiza a tela de game over
// **********************************************************************
void GameOver()
{
    ga.gameoverObject.Render();
}
// **********************************************************************
// bool IsColliding(Object &obj1, Object &obj2)
// MÈtodo que informa se 2 objetos se colidiram
// Parametros:
//      obj1: objeto 1
//      obj2: objeto 2
// **********************************************************************
bool IsColliding(Object &obj1, Object &obj2)
{
    if((obj2.position.x + obj2.model->width) < obj1.position.x - obj1.model->width) return false;
    if((obj2.position.x - obj2.model->width) > obj1.position.x + obj1.model->width) return false;
    if((obj2.position.y + obj2.model->height) < obj1.position.y - obj1.model->height) return false;
    if((obj2.position.y - obj2.model->height) > obj1.position.y + obj1.model->height) return false;
    if((obj2.position.z + obj2.model->depth) < obj1.position.z - obj1.model->depth) return false;
    if((obj2.position.z - obj2.model->depth) > obj1.position.z + obj1.model->depth) return false;
    return true;
}
// **********************************************************************
// void Process()
// MÈtodo que processa os valores dos objetos a cada frame
// **********************************************************************
void Process()
{
    if(player.inGame | godMode)
    {
        int i, j, k;

        MovePlayer();

        // Processa dados das naves inimigas
        for(i=0; i<ga.enemysCont; i++)
        {
            ga.enemys[i].Update(deltaTime);
            // Verifica se o trajeto da bezie j· terminou para gerar outro
            if(ga.enemys[i].BezieCompleted()) ga.enemys[i].SetNewBezie(ga.MAXX, ga.MAXY, ga.MAXZ);
            // Processa dados dos disparos ativos
            for(j=0; j<ga.enemys[i].MAXBULLETS; j++)
            {
                if(ga.enemys[i].bullets[j].inGame)
                {
                    // Colis„o com o jogador
                    if(IsColliding(player, ga.enemys[i].bullets[j]))
                    {
                        ga.enemys[i].bullets[j].inGame = false;
                        player.TakeDamage(ga.enemys[i].bullets[j].damage);
                    }
                    //Colis„o com objetos no cen·rio
                    for(k=0; k<ga.objectsCont; k++)
                    {
                        if(IsColliding(ga.objects[k], ga.enemys[i].bullets[j])) ga.enemys[i].bullets[j].inGame = false;
                    }
                }
            }
        }
        // Verifica colisıes com EnergySpawners e atualiza seus atributos
        for(i=0; i<ga.spawnersCont; i++)
        {
            ga.energySpawners[i].Update();
            if(ga.energySpawners[i].inGame)
            {
                if(IsColliding(player, ga.energySpawners[i]))
                {
                    ga.energySpawners[i].inGame = false;
                    player.Charge(ga.energySpawners[i].energyCharge);
                }
            }
        }
    }else
    {
        status = GAMEOVER;
        debug = false;
        godMode = false;
    }
}
// **********************************************************************
// void DrawGUI()
// Desenha a interface do usu·rio
// **********************************************************************
void DrawGUI()
{
    int x = -9;
    int y = ga.HEIGHTSCREEN - 105;
    int width = 2;
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    {
        glVertex2d(x,y);
        glVertex2d(x+width,y);
        glVertex2d(x+width,y+player.battery);
        glVertex2d(x,y+player.battery);
    }
    glEnd();
}
// **********************************************************************
// void MovePlayer()
// Processa as requisiÁıes do usu·rio para locomover o obj do jogador
// **********************************************************************
void MovePlayer()
{
    if(GetKeyState('A') & 0x8000)
    {
        player.Rotate(deltaTime);
    }

    if(GetKeyState('D') & 0x8000)
    {
        player.Rotate(-deltaTime);
    }

    if(GetKeyState('I') & 0x8000)
    {
        player.target->y += 5 * deltaTime;
    }

    if(GetKeyState('J') & 0x8000)
    {
        player.target->x += 5 * deltaTime;
    }

    if(GetKeyState('K') & 0x8000)
    {
        player.target->y -= 5 * deltaTime;
    }

    if(GetKeyState('L') & 0x8000)
    {
        player.target->x -= 5 * deltaTime;
    }


    if(GetKeyState('W') & 0x8000)
    {
        Vector3 alfa = player.Move(deltaTime);
        Vector3 newPos = Vector3(player.position.x + alfa.x, player.position.y, player.position.z + alfa.z);
        if(ga.CanMove(newPos) | godMode)
        {
            player.position = newPos;
            player.target->x += alfa.x;
            player.target->z += alfa.z;

            player.Discharge();
        }
    }
}
// **********************************************************************
// void GetNormalVector(Triangle &triangle)
// Define o vetor normal de um triangulo
// Parametros:
//      triangle: triangulo a ser calculado a normal
// **********************************************************************
void GetNormalVector(Triangle &triangle)
{
    Vector3 vet1 = Vector3(triangle.vertexs[1].x - triangle.vertexs[0].x,
                           triangle.vertexs[1].y - triangle.vertexs[0].y,
                           triangle.vertexs[1].z - triangle.vertexs[0].z);

    Vector3 vet2 = Vector3(triangle.vertexs[2].x - triangle.vertexs[0].x,
                           triangle.vertexs[2].y - triangle.vertexs[0].y,
                           triangle.vertexs[2].z - triangle.vertexs[0].z);

    triangle.normal = vet1.ProdVector(vet2);
    triangle.normal.UnitVector();
}
// **********************************************************************
// void SetColor(string hex, ColorRGB &colorRGB)
// Define uma cor com base no valor hexadecimal informado
// Parametros:
//      hex: valor hexadecimal a ser traduzido em cor
//      colorRGB: cor a ser iniciada
// **********************************************************************
void SetColor(string hex, ColorRGB &colorRGB)
{
    char color[2];
    color[0] = hex[2];
    color[1] = hex[3];
    colorRGB.r = ((float) strtol(color, 0, 16))/255.0f;

    color[0] = hex[4];
    color[1] = hex[5];
    colorRGB.g = ((float) strtol(color, 0, 16))/255.0f;

    color[0] = hex[6];
    color[1] = hex[7];
    colorRGB.b = ((float) strtol(color, 0, 16))/255.0f;
}
// **********************************************************************
// void LoadModel(Model &model, const char* name)
// Carrega um modelo de objeto de um arquivo .tri
// Parametros:
//      model: instancia do modelo a ser escrito
//      name: nome do arquivo .tri
// **********************************************************************
void LoadModel(Model &model, const char* name, float scale)
{
    ifstream file;
    file.open(name);
    float x,y,z;
    unsigned int triangle,vertex;
    ColorRGB color;
    string hex;
    Vector3 vert;
    Vector3 minVertex = Vector3(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
    Vector3 maxVertex = Vector3(0, 0, 0);

    if(file ==  NULL)
    {
        cout << name << " n„o encontrado!!!\n";
        return;
    }

    file >> model.modelSize;
    model.triangles = new Triangle[model.modelSize];

    for(triangle=0; triangle<model.modelSize; triangle++)
    {
        for(vertex=0; vertex<3; vertex++)
        {
            file >> x;
            file >> y;
            file >> z;

            x *= scale;
            y *= scale;
            z *= scale;

            vert = Vector3(x, y, z);
            model.triangles[triangle].SetVertex(vertex, vert);

            if(x < minVertex.x) minVertex.x = x;
            if(y < minVertex.y) minVertex.y = y;
            if(z < minVertex.z) minVertex.z = z;

            if(x > maxVertex.x) maxVertex.x = x;
            if(y > maxVertex.y) maxVertex.y = y;
            if(z > maxVertex.z) maxVertex.z = z;
        }

        file >> hex;
        SetColor(hex, color);
        model.triangles[triangle].color = color;
        GetNormalVector(model.triangles[triangle]);
    }

    model.width = (maxVertex.x - minVertex.x)/2.0f;
    model.height = (maxVertex.y - minVertex.y)/2.0f;
    model.depth = (maxVertex.z - minVertex.z)/2.0f;
    file.close();
}
// **********************************************************************
// void DrawTriangle(const Triangle &triangle)
// MÈtodo auxiliar de Object::Render() que desenha um triangulo
// Parametros:
//      triangle: triangulo a ser desenhado
// **********************************************************************
void DrawTriangle(const Triangle &triangle)
{
    glBegin(GL_TRIANGLES);
    {
        for(int i=0; i<3; i++)
        {
            glVertex3f(triangle.vertexs[i].x,triangle.vertexs[i].y, triangle.vertexs[i].z);
        }
    }
    glEnd();
}
// **********************************************************************
//  void GameManager::LoadScenario(string fileName)
//  Carrega os modelos e objetos que estaram no cenario
//  Parametros:
//      fileName: nome do arquivo de configuraÁ„o do mapa. Formato .txt
// **********************************************************************
void GameManager::LoadScenario(char* fileName)
{
    ifstream file(fileName);
    string temp;
    const char* nameModel;
    float scale;
    int cont = 0;
    int pixel, currentObj, halfCell;

    if(file == NULL)
    {
        cout << "Arquivo " << fileName << " n„o encontrado.\n";
        return;
    }

    file >> temp;
    file >> scale;
    nameModel = temp.c_str();
    bulletModel = new Model[1];
    LoadModel(bulletModel[0], nameModel, scale);

    file >> temp;
    file >> scale;
    nameModel = temp.c_str();
    player.model = new Model[1];
    LoadModel(player.model[0], nameModel, scale);

    file >> enemysCont;
    file >> temp;
    file >> scale;
    nameModel = temp.c_str();
    enemyModel = new Model[1];
    enemys = new EnemyShip[enemysCont];
    LoadModel(enemyModel[0], nameModel, scale);

    for(int i=0; i<ga.enemysCont; i++)
    {
        enemys[i].SetEnemyShip(&(enemyModel[0]), &(player.position), &(bulletModel[0]));
    }

    LoadModel(model, "gameover.tri", 3.0f);
    gameoverObject.SetObject(Vector3(0,0,0), &model, 0);

    //le quantidade de modelos
    file >> modelsCont;
    models = new Model[modelsCont];
    //le os modelos
    while(cont < modelsCont)
    {
        file >> temp;
        file >> scale;
        nameModel = temp.c_str();
        LoadModel(models[cont], nameModel, scale);
        cont++;
    }
    //Le quantidade de spawners
    file >> spawnersCont;
    //Le modelo de spawner
    file >> temp;
    file >> scale;
    spawnerModel = new Model[1];
    nameModel = temp.c_str();
    LoadModel(spawnerModel[0], nameModel, scale);
    energySpawners = new EnergySpawner[spawnersCont];
    int spawner = 0;
    //Le quantidade de objetos
    file >> objectsCont;
    //Le dimensoes da matriz
    file >> XMATRIX;
    file >> MAXY;
    file >> ZMATRIX;
    //Le dimensoes do cenario
    file >> sizeCell;
    halfCell = sizeCell/2;
    MAXX = XMATRIX * sizeCell;
    MAXZ = ZMATRIX * sizeCell;
    //Cria os objetos
    objects = new Object[objectsCont];
    currentObj = 0;
    int x,z;
    InitMatrix();

    for(z=0; z<ZMATRIX; z++)
    {
        for(x=0; x<XMATRIX; x++)
        {
            file >> pixel;
            if(pixel > 0)
            {
                objects[currentObj].SetObject(Vector3(x*sizeCell + halfCell, 0, z*sizeCell + halfCell), &(models[pixel-1]), 0);
                SetsObjectBoundary(&(objects[currentObj].position), objects[currentObj].model);
                cout << "OBJ -> " << objects[currentObj].model->width << " " << objects[currentObj].model->height << " " << objects[currentObj].model->depth << "\n";
                currentObj++;
            }else if(pixel == -1)
            {
                energySpawners[spawner] = EnergySpawner(&(spawnerModel[0]), Vector3(x*sizeCell + halfCell, 1, z*sizeCell + halfCell));
                spawner++;
            }
        }
    }
    file.close();
}
// **********************************************************************
//  void GameManager::DrawScenario()
//  Desenha todos os objetos do cenario
// **********************************************************************
void GameManager::DrawScenario()
{
    int i, j;

    //Desenha Objetos est·ticos
    for(i=0; i<objectsCont; i++)
    {
        objects[i].Render();
    }
    //Desenha combustiveis
    for(i=0; i<spawnersCont; i++)
    {
        if(energySpawners[i].inGame)
        {
            energySpawners[i].Render();
        }
    }
    //Desenha inimigos
    for(i=0; i<enemysCont; i++)
    {
        ga.enemys[i].Render();

        for(j=0; j<ga.enemys[i].MAXBULLETS; j++)
        {
            if(ga.enemys[i].bullets[j].inGame) ga.enemys[i].bullets[j].Render();
        }
    }
    //Desenha jogador
    player.Render();
}
// **********************************************************************
//  void Object::Render()
//  Desenha o modelo do objeto
// **********************************************************************
void Object::Render()
{
    glPushMatrix();
    {
        glTranslated(position.x,position.y,position.z);
        glRotatef(angle,0,1,0);
        for(unsigned int triangle = 0; triangle < model->modelSize; triangle++)
        {
            glColor3f(model->triangles[triangle].color.r,
                      model->triangles[triangle].color.g,
                      model->triangles[triangle].color.b);
            DrawTriangle(model->triangles[triangle]);

        }
        // Desenha o envelope dos objetos, caso o debug estaja ligado
        if(debug)
        {
            glBegin(GL_LINES);
            {
                float height = model->height*2;
                glColor3f(1,0,0);
                glVertex3f(-model->width, 0, -model->depth);
                glVertex3f(-model->width, height, -model->depth);

                glVertex3f(model->width, 0, -model->depth);
                glVertex3f(model->width, height, -model->depth);

                glVertex3f(model->width, 0, model->depth);
                glVertex3f(model->width, height, model->depth);

                glVertex3f(-model->width, 0, model->depth);
                glVertex3f(-model->width, height, model->depth);

                glVertex3f(-model->width, 0 , -model->depth);
                glVertex3f(model->width, 0 , -model->depth);

                glVertex3f(model->width, 0 , -model->depth);
                glVertex3f(model->width, 0 , model->depth);

                glVertex3f(model->width, 0 , model->depth);
                glVertex3f(-model->width, 0 , model->depth);

                glVertex3f(-model->width, 0 , model->depth);
                glVertex3f(-model->width, 0 , -model->depth);

                glVertex3f(-model->width, height , -model->depth);
                glVertex3f(model->width, height, -model->depth);

                glVertex3f(model->width, height, -model->depth);
                glVertex3f(model->width, height, model->depth);

                glVertex3f(model->width, height, model->depth);
                glVertex3f(-model->width, height, model->depth);

                glVertex3f(-model->width, height, model->depth);
                glVertex3f(-model->width, height, -model->depth);
            }
            glEnd();
        }
    }
    glPopMatrix();
}

// **********************************************************************
//  void DefineLuz(void)
// **********************************************************************
void DefineLuz(void)
{
  // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.4, 0.4, 0.4f } ;
  GLfloat LuzDifusa[]   = {0.7, 0.7, 0.7};
  GLfloat LuzEspecular[] = {0.9f, 0.9f, 0.9 };
  GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f };
  GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f};

   // ****************  Fonte de Luz 0

 glEnable ( GL_COLOR_MATERIAL );

   // Habilita o uso de iluminaÁ„o
  glEnable(GL_LIGHTING);

  // Ativa o uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
  // Define os parametros da luz número Zero
  glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
  glEnable(GL_LIGHT0);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentraçãoo do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado será o brilho. (Valores válidos: de 0 a 128)
  glMateriali(GL_FRONT,GL_SHININESS,51);
}
// **********************************************************************
//  void init(void)
//		Inicializa os par‚metros globais de OpenGL
// **********************************************************************
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

	glShadeModel(GL_SMOOTH);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_DEPTH_TEST);
	glEnable ( GL_CULL_FACE );

    // Obtem o tempo inicial
#ifdef WIN32
    last_idle_time = GetTickCount();
#else
    gettimeofday (&last_idle_time, NULL);
#endif

    ga.LoadScenario("map.txt");
    player.SetPosition(6,0,6);
    player.target = new Vector3(6,0,7);
}
// **********************************************************************
//  void PosicUser()
// **********************************************************************
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,AspectRatio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    if(status == INGAME)
    {
        glRotatef(player.angle*-1, 0,1,0);
        gluLookAt(player.position.x, player.position.y+2, player.position.z,
                  player.target->x, player.target->y+2, player.target->z,
                      0.0f,1.0f,0.0f);
    }else
    {
        gluLookAt(8, 1, 20,
                  8, 1, 0,
                  0.0f,1.0f,0.0f);
    }
}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
// **********************************************************************
void reshape( int w, int h )
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	AspectRatio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	PosicUser();

}
// **********************************************************************
// void DrawGrid()
// Desenha os limites do cen·rio
// **********************************************************************
void DrawGrid()
{
    int i;
    glBegin(GL_LINES);
    {
        glLineWidth(1);
        glColor3f(0,0,1);

        for(i=0; i<ga.MAXX; i+=10)
        {
            glVertex3f(i, 0, 0);
            glVertex3f(i, 0, ga.MAXZ);
            glVertex3f(0, 0, i);
            glVertex3f(ga.MAXX, 0, i);

            glVertex3f(i, ga.MAXY, 0);
            glVertex3f(i, ga.MAXY, ga.MAXZ);
            glVertex3f(0, ga.MAXY, i);
            glVertex3f(ga.MAXX, ga.MAXY, i);

            glVertex3f(i, 0, 0);
            glVertex3f(i, ga.MAXY, 0);

            glVertex3f(0, 0, i);
            glVertex3f(0, ga.MAXY, i);

            glVertex3f(i, 0, ga.MAXZ);
            glVertex3f(i, ga.MAXY, ga.MAXZ);

            glVertex3f(ga.MAXX, 0, i);
            glVertex3f(ga.MAXX, ga.MAXY, i);
        }

        for(i=0; i<ga.MAXY; i+=10)
        {
            glVertex3f(0, i, 0);
            glVertex3f(ga.MAXX, i, 0);

            glVertex3f(0, i, 0);
            glVertex3f(0, i, ga.MAXZ);

            glVertex3f(0, i, ga.MAXZ);
            glVertex3f(ga.MAXX, i, ga.MAXZ);

            glVertex3f(ga.MAXX, i, ga.MAXZ);
            glVertex3f(ga.MAXX, i, 0);
        }
    }
    glEnd();
}
// **********************************************************************
//  void display( void )
// **********************************************************************
void display( void )
{
	if(status == INGAME)
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        DefineLuz();
        PosicUser();
        glMatrixMode(GL_MODELVIEW);

        Process();

        ga.DrawScenario();
        DrawGrid();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0,ga.WIDTHSCREEN,0,ga.HEIGHTSCREEN,0,1);

        DrawGUI();
    }else
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        DefineLuz();
        PosicUser();
        glMatrixMode(GL_MODELVIEW);

        GameOver();
    }

	glutSwapBuffers();
}
// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
// **********************************************************************
void animate()
{
    static float dt;
    static float AccumTime=0;

#ifdef _WIN32
    DWORD time_now;
    time_now = GetTickCount();
    dt = (float) (time_now - last_idle_time) / 1000.0;
#else
    // Figure out time elapsed since last call to idle function
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
    1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);
#endif
    AccumTime +=dt;
    deltaTime = dt;
    if (AccumTime >=3) // imprime o FPS a cada 3 segundos
    {
        cout << 1.0/dt << " FPS"<< endl;
        AccumTime = 0;
    }
    //cout << "AccumTime: " << AccumTime << endl;
    // Anima cubos
    AngY++;
    // Sa;va o tempo para o próximo ciclo de rendering
    last_idle_time = time_now;

        //if  (GetAsyncKeyState(32) & 0x8000) != 0)
          //  cout << "Espaco Pressionado" << endl;

    // Redesenha
    glutPostRedisplay();
}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
        case 27:        // Termina o programa qdo
          exit ( 0 );   // a tecla ESC for pressionada
          break;
        case 'o': //God mode
          if(status == INGAME) godMode = !godMode;
          break;
        case 'p': //debug
          if(status == INGAME) debug = !debug;
          break;
    default:
            cout << key;
      break;
  }
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_UP:
			break;
	    case GLUT_KEY_DOWN:
			break;
        case GLUT_KEY_LEFT:
			break;
        case GLUT_KEY_RIGHT:
			break;
		default:
			break;
	}
}
// **********************************************************************
//  void main ( int argc, char** argv )
// **********************************************************************
int main ( int argc, char** argv )
{
	glutInit            ( &argc, argv );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
	glutInitWindowPosition (0,0);
	glutInitWindowSize  ( 700, 500 );
	glutCreateWindow    ( "Computacao Grafica - Exemplo Basico 3D" );

	init ();

	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutSpecialFunc ( arrow_keys );
	glutIdleFunc ( animate );

	glutMainLoop ( );

	return 0;
}


