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

GLfloat AspectRatio, AngY=0;
Camera* mainCamera = new Camera(new Vector3(0,0,-5), new Vector3(0,0,15));
GameManager ga = GameManager();
Player player = Player(10);
float deltaTime = 0;

bool IsColliding(Object &obj1, Object &obj2);
void LoadModel(Model &model, const char* name);
void DrawModel(const Model &model);
void DrawTriangle(const Triangle &triangle);
void SetColor(string hex, ColorRGB &colorRGB);
void GetNormalVector(Triangle &triangle);
void ProdVector(const Vector3* v1, const Vector3* v2, Vector3 &prodVect);
void MovePlayer();
void DrawGUI();
void Draw();
void Process();

bool IsColliding(Object &obj1, Object &obj2)
{
    if((obj2.position.x + obj2.model->width) < obj1.position.x - obj1.model->width) return false;
    if((obj2.position.x - obj2.model->width) > obj1.position.x + obj1.model->width) return false;
    if((obj2.position.y + obj2.model->height) < obj1.position.y - obj1.model->height) return false;
    if((obj2.position.y - obj2.model->height) > obj1.position.y + obj1.model->height) return false;
    if((obj2.position.z + obj2.model->depth) < obj1.position.z - obj1.model->depth) return false;
    if((obj2.position.z - obj2.model->depth) > obj1.position.z - obj1.model->depth) return false;
    return true;
}

void Process()
{
    int i;

    MovePlayer();
/*
    for(i=0; i<ga.enemysCont; i++)
    {
        ga.enemys[i].MoveEShip(deltaTime);
        if(ga.enemys[i].CanShoot())
        {
            ga.bullets[ga.bulletsCont].SetBullet(ga.enemys[i].angle, ga.enemys[i].position, *(ga.enemys[i].target), ga.bulletModel[0], deltaTime);
            ga.bulletsCont++;
        }
    }

    for(i=0; i<ga.bulletsCont; i++)
    {
        ga.bullets[i].Update(deltaTime);
    }
*/

    for(i=0; i</*ga.spawnersCont*/1; i++)
    {
        ga.energySpawners[i].Update();
        if(ga.energySpawners[i].active)
        {
            if(IsColliding(player, ga.energySpawners[i]))
            {
                ga.energySpawners[i].active = false;
            }
        }
    }
}

void DrawGUI()
{
    //TODO
}

void MovePlayer()
{
    if(GetKeyState('W') & 0x8000)
    {
        Vector3 newPosition = player.Move(deltaTime);

        int x = newPosition.x / ga.sizeCell;
        int z = newPosition.z / ga.sizeCell;

        if(x > ga.MAXXMATRIX) newPosition.x = ga.MAXXMATRIX * ga.sizeCell;
        else if(x < 0) newPosition.x = 0;
        if(z > ga.MAXZMATRIX) newPosition.z = ga.MAXZMATRIX * ga.sizeCell;
        else if(z < 0)
        {
            newPosition.z = 0;
        }else
        {
            if((ga.matrixConstraints[z%ga.MAXZMATRIX][x%ga.MAXXMATRIX] == 0) | (ga.matrixConstraints[z%ga.MAXZMATRIX][x%ga.MAXXMATRIX] == -2))
            {
                player.position = newPosition;
                player.target->x = newPosition.x;
                player.target->z = newPosition.z + 2;
            }
        }

    }

    if(GetKeyState('A') & 0x8000)
    {
        player.Rotate(deltaTime);
    }

    if(GetKeyState('D') & 0x8000)
    {
        player.Rotate(-deltaTime);
    }
}

void ProdVector(const Vector3 &v1, const Vector3 &v2, Vector3 &prodVect)
{
    prodVect.x = v1.y * v2.z - (v1.z * v2.y);
    prodVect.y = v1.z * v2.x - (v1.x * v2.z);
    prodVect.z = v1.x * v2.y - (v1.y * v2.x);
}

void GetNormalVector(Triangle &triangle)
{
    Vector3 vet1 = Vector3(triangle.vertexs[1].x - triangle.vertexs[0].x,
                           triangle.vertexs[1].y - triangle.vertexs[0].y,
                           triangle.vertexs[1].z - triangle.vertexs[0].z);

    Vector3 vet2 = Vector3(triangle.vertexs[2].x - triangle.vertexs[0].x,
                           triangle.vertexs[2].y - triangle.vertexs[0].y,
                           triangle.vertexs[2].z - triangle.vertexs[0].z);

    ProdVector(vet1, vet2, triangle.normal);
    triangle.normal.UnitVector();
}

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

void LoadModel(Model &model, const char* name)
{
    ifstream file;
    file.open(name);
    float x,y,z;
    unsigned int triangle,vertex;
    ColorRGB color;
    string hex;
    Vector3 vert;
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
            vert = Vector3(x,y,z);
            model.triangles[triangle].SetVertex(vertex, vert);

            if(x > maxVertex.x) maxVertex.x = x;
            if(y > maxVertex.y) maxVertex.y = y;
            if(z > maxVertex.z) maxVertex.z = z;
        }

        file >> hex;
        SetColor(hex, color);
        model.triangles[triangle].color = color;
        GetNormalVector(model.triangles[triangle]);
        model.width = maxVertex.x;
        model.height = maxVertex.y;
        model.depth = maxVertex.z;
    }

    file.close();
}

void DrawModel(const Model &model)
{
    glPushMatrix();
    {
        glTranslated(0,0,5);
        glRotatef(AngY,0,1,0);
        for(unsigned int triangle = 0; triangle < model.modelSize; triangle++)
        {
            glColor3f(model.triangles[triangle].color.r,
                      model.triangles[triangle].color.g,
                      model.triangles[triangle].color.b);
            DrawTriangle(model.triangles[triangle]);
        }
    }
    glPopMatrix();
}

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
// **********************************************************************
void GameManager::LoadScenario(char* fileName)
{
    ifstream file(fileName);
    string temp;
    const char* nameModel;
    float scale;
    int cont = 0;
    int pixel;
    int currentObj;
    int halfCell;

    if(file == NULL)
    {
        cout << "Arquivo " << fileName << " n„o encontrado.\n";
        return;
    }

    //le quantidade de modelos
    file >> modelsCont;
    models = new Model[modelsCont];
    //le os modelos
    while(cont < modelsCont)
    {
        file >> temp;
        file >> scale;
        nameModel = temp.c_str();
        LoadModel(models[cont], nameModel);
        models[cont].SetScale(scale);
        cont++;
    }
    //Le quantidade de spawners
    file >> spawnersCont;
    //Le modelo de spawner
    file >> temp;
    file >> scale;
    spawnerModel = new Model[1];
    nameModel = temp.c_str();
    LoadModel(spawnerModel[0], nameModel);
    spawnerModel[0].SetScale(scale);
    energySpawners = new EnergySpawner[spawnersCont];
    int spawner = 0;
    //Le quantidade de objetos
    file >> objectsCont;
    //Le dimensoes da matriz
    file >> MAXXMATRIX;
    file >> MAXZMATRIX;
    //Le dimensoes do cenario
    file >> sizeCell;
    halfCell = sizeCell/2;
    //Cria os objetos
    objects = new Object[objectsCont];
    currentObj = 0;
    int x,z;
    matrixConstraints = new char*[MAXZMATRIX];
    for(z=0; z<MAXZMATRIX; z++)
    {
        matrixConstraints[z] = new char[MAXXMATRIX];
        for(x=0; x<MAXXMATRIX; x++)
        {
            file >> pixel;
            matrixConstraints[z][x] = pixel;
            if(pixel > 0)
            {
                objects[currentObj].SetObject(Vector3(x*sizeCell + halfCell, 0, z*sizeCell + halfCell), &(models[pixel-1]), 0);
                currentObj++;
            }else if(pixel == -2)
            {
                energySpawners[spawner] = EnergySpawner(&(spawnerModel[0]), Vector3(x*sizeCell + halfCell, 0, z*sizeCell + halfCell));
                spawner++;
            }
        }
    }
    ga.sizeCell = sizeCell;

    file.close();
}
// **********************************************************************
//  void GameManager::DrawScenario()
//  Desenha todos os objetos do cenario
// **********************************************************************
void GameManager::DrawScenario()
{
    int i;
/*
    for(i=0; i<objectsCont; i++)
    {
        objects[i].Render();
    }
*/
    for(i=0; i</*spawnersCont*/1; i++)
    {
        if(energySpawners[i].active)
        {
            energySpawners[i].Render();
        }
    }
/*
    for(i=0; i<enemysCont; i++)
    {
        ga.enemys[i].Render();
    }

    for(i=0; i<bulletsCont; i++)
    {
        ga.bullets[i].Render();
    }
*/
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
        glScalef(model->scale, model->scale, model->scale);
        for(unsigned int triangle = 0; triangle < model->modelSize; triangle++)
        {
            glColor3f(model->triangles[triangle].color.r,
                      model->triangles[triangle].color.g,
                      model->triangles[triangle].color.b);
            DrawTriangle(model->triangles[triangle]);

        }

        glBegin(GL_LINES);
        {
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            glVertex3f(0,0,20);
        }
        glEnd();
    }
    glPopMatrix();
}

// **********************************************************************
//  void DefineLuz(void)
//
//
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
//
// **********************************************************************
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

	glShadeModel(GL_SMOOTH);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_DEPTH_TEST);
	//glEnable ( GL_CULL_FACE );

    // Obtem o tempo inicial
#ifdef WIN32
    last_idle_time = GetTickCount();
#else
    gettimeofday (&last_idle_time, NULL);
#endif

    ga.LoadScenario("map.txt");

    ga.MAXBULLETS = 100;
    ga.bulletsCont = 0;
    ga.bulletModel = new Model[1];
    LoadModel(ga.bulletModel[0], "bullet.tri");
    ga.bulletModel[0].SetScale(0.1f);
    ga.bullets = new Bullet[ga.MAXBULLETS];

    player.SetPosition(0,1,0);
    player.model = new Model[1];
    LoadModel(player.model[0], "player.tri");
    player.model->SetScale(0.1f);

    ga.enemysCont = 1;
    ga.enemys = new EnemyShip[ga.enemysCont];
    ga.enemyModel = new Model[1];
    LoadModel(ga.enemyModel[0], "enemy.tri");
    ga.enemyModel[0].SetScale(0.1f);
    for(int i=0; i<ga.enemysCont; i++)
    {
        ga.enemys[i].SetEnemyShip(&(ga.enemyModel[0]), &(player.position));
    }
}
// **********************************************************************
//  void PosicUser()
//
//
// **********************************************************************
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,AspectRatio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	    glRotatef(-player.angle, 0,1,0);
	    gluLookAt(player.position.x, player.position.y, player.position.z,
                  player.position.x, player.position.y, player.position.z + 10,
                  0.0f,1.0f,0.0f);
    */
    glRotatef(player.angle*-1, 0,1,0);
    gluLookAt(player.position.x, player.position.y+1, player.position.z,
              player.target->x, player.target->y+1, player.target->z,
                  0.0f,1.0f,0.0f);
}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
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
//  void DesenhaCubo()
//
//
// **********************************************************************
void DesenhaCubo()
{
	glBegin ( GL_QUADS );
		// Front Face
		glNormal3f(0,0,1);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f(0,0,-1);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f(0,1,0);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f(0,-1,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f(1,0,0);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1,0,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}
// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display( void )
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	DefineLuz();
	PosicUser();
	glMatrixMode(GL_MODELVIEW);

	Process();
    ga.DrawScenario();
    DrawGUI();

	glutSwapBuffers();
}

// **********************************************************************
//  void animate ( unsigned char key, int x, int y )
//
//
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
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
        case 27:        // Termina o programa qdo
          exit ( 0 );   // a tecla ESC for pressionada
          break;
    default:
            cout << key;
      break;
  }
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
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
            mainCamera->angle -= 10;
			break;
        case GLUT_KEY_RIGHT:
            mainCamera->angle += 10;
			break;
		default:
			break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
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


