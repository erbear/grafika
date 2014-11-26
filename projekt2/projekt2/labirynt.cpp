/*************************************************************************************/

// Trochê bardziej skomplikowany program wykorzystuj¹cy funkcje biblioteki OpenGL

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

// Funkcaja okreœlaj¹ca, co ma byæ rysowane 
// (zawsze wywo³ywana, gdy trzeba przerysowaæ scenê)


void RenderScene(void)
{
	point2 p1, p2, p3, p4;
	p1[0] = -100;
	p1[1] = -100;
	p2[0] = 100;
	p2[1] = 100;
	GLfloat bok = 200;
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glColor3f(0.5f, 0.5f, 0.5f);
	// Ustawienie aktualnego koloru rysowania na zielony
	glRectf(p1[0], p1[1], p1[0]+ bok, p1[1]+ bok); 
	glColor3f(0.0f, 0.0f, 1.0f);
	rysujLabirynt(p1, bok, 30);
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}
/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnêtrza okna - ustawiono na szary
}
/*************************************************************************************/

// Funkcja s³u¿¹ca do kontroli zachowania proporcji rysowanych obiektów
// niezale¿nie od rozmiarów okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okreœlenie uk³adu wspó³rzêdnych obserwatora
	glLoadIdentity();
	// Okreœlenie przestrzeni ograniczaj¹cej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okreœlenie okna obserwatora. 
	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreœlenie uk³adu wspó³rzêdnych     
	glLoadIdentity();
}
/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli


void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyœwietlania
	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
	// GLUT_RGBA - model kolorów RGB

	glutCreateWindow("Drugi program w OpenGL");
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
	// trzeba bêdzie przerysowaæ okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst¹pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
