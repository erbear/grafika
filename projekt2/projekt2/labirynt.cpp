/*************************************************************************************/

// Troch� bardziej skomplikowany program wykorzystuj�cy funkcje biblioteki OpenGL

/*************************************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "LabiryntGen.h"
/*************************************************************************************/
typedef GLfloat point2[2];
void rysujLabirynt(point2 p1, GLfloat bok, int poziom)
{
	vector< vector<int> > sciany(poziom*poziom, vector<int>(2));
	vector <int> polaczenia;
	GLfloat malybok = bok / poziom;
	LabiryntGen *gen;
	gen = new LabiryntGen(poziom);
	gen->nastepnaWersja();
	polaczenia = gen->Generuj();
	for (int i = 0; i < poziom*poziom;i++){
		sciany[i][0] = 1;
		sciany[i][1] = 1;
	}
	for (int i = 0; i < polaczenia.size();i++){
		if (i%2 == 0) {
			if (polaczenia[i] + 1 ==  polaczenia[i+1]){
				sciany[polaczenia[i] - 1][0] = 0;
			}
			else {
				sciany[polaczenia[i] - 1][1] = 0;
			}
		
		}
	}
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-100.0f, 100.0f);
		glVertex2f(100.0f, 100.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-100.0f, 100.0f);
		glVertex2f(-100.0f, -100.0f);
	glEnd();
	int licznik = 0;
	for (int i = 0; i< poziom;i++){
		for (int j = 0; j< poziom;j++){
			if (sciany[licznik][0]) {
				glBegin(GL_LINES);
					glColor3f(0.0f, 0.0f, 1.0f);
					glVertex2f(-100.0f + malybok*(j+1), 100.0f - malybok * i);
					glVertex2f(-100.0f + malybok*(j+1), 100.0f - malybok * (i+1));
				glEnd();
			}
			if (sciany[licznik][1]) {
				glBegin(GL_LINES); 
					glColor3f(0.0f, 0.0f, 1.0f);
					glVertex2f(-100.0f + malybok*(j), 100.0f - malybok * (i+1));
					glVertex2f(-100.0f + malybok*(j+1), 100.0f - malybok * (i+1));
				glEnd();
			}
			licznik++;
		}
	}
}

// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)


void RenderScene(void)
{
	point2 p1, p2, p3, p4;
	p1[0] = -100;
	p1[1] = -100;
	p2[0] = 100;
	p2[1] = 100;
	GLfloat bok = 200;
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym
	glColor3f(0.5f, 0.5f, 0.5f);
	// Ustawienie aktualnego koloru rysowania na zielony
	glRectf(p1[0], p1[1], p1[0]+ bok, p1[1]+ bok); 
	glColor3f(0.0f, 0.0f, 1.0f);
	rysujLabirynt(p1, bok, 30);
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania
}
/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary
}
/*************************************************************************************/

// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora
	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okre�lenie okna obserwatora. 
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych     
	glLoadIdentity();
}
/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli


void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
