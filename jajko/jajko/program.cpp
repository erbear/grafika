/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <vector>
#include <math.h>

# define M_PI           3.14159265358979323846

typedef GLfloat point3[3];
using namespace std;

/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych
void Egg(void)
{
	int n = 20;
	point3** tablica = new point3*[n];
	for (int i =0; i < n; i++)
	{

		tablica[i] = new point3[n];

		float u = (float)i/(float)n;

		for (int j = 0; j < n; j++){
			float v = (float)j / (float)n ;
			float x = (-1 * 90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(M_PI * v);
			float y = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2);
			float z = (-1 * 90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3)  +180 * pow(u, 2) - 45 * u) * sin(M_PI * v);
			point3 p;
			p[0] = x;
			p[1] = y - 5;
			p[2] = z;
			tablica[i][j][0] = x;
			tablica[i][j][1] = y - 5;
			tablica[i][j][2] = z;

			glBegin(GL_POINTS);
				glVertex3fv(p);
			glEnd();
		}
	}

}

void Axes(void)
{
	
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0, 5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0, 5.0 };
	//  pocz�tek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x

	glVertex3fv(x_min);
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);

	glEnd();

}

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba
// przerysowa� scen�)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej 
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia�y 

	glRotated(60.0, 1.0, 1.0, 1.0);  // Obr�t o 60 stopni

	Egg();
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania



	glutSwapBuffers();
	// 

}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s�
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 



	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;



	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)



	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji



	glLoadIdentity();
	// Czyszcznie macierzy bie��cej           



	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            



	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie��cej

}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli



void main(void)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem
	// gdy zajdzie potrzba przeryswania okna



	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna                        



	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania

	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}



/*************************************************************************************/