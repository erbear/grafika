/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi 
//  uk³adu wspó³rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <vector>
#include <math.h>

# define M_PI           3.14159265358979323846

typedef GLfloat point3[3];
using namespace std;
static GLfloat theta[] = {0.0, 0.0, 0.0};
/*************************************************************************************/
int model = 1;  // 1- punkty, 2- siatka, 3 - wype³nione trójk¹ty
// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych
point3** kolory;
float randomColor()
{
	return ((float)(rand()%10)+1)/10; 
} 
void spinEgg()
{
    theta[0] -= 0.1;
    if( theta[0] > 360.0 ) theta[0] -= 360.0;

    theta[1] -= 0.1;
    if( theta[1] > 360.0 ) theta[1] -= 360.0;

    theta[2] -= 0.1;
    if( theta[2] > 360.0 ) theta[2] -= 360.0;

    glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}
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
			tablica[i][j][0] = x;
			tablica[i][j][1] = y - 5;
			tablica[i][j][2] = z;
			
			//glBegin(GL_POINTS);
			//	glVertex3fv(p);
			//glEnd();
			//glBegin(GL_LINES);
				
			//glEnd();

		}
	}
	/*
	for (int i =0; i < n; i++)
	{
		for (int j = 0; j < n; j++){
			//glBegin(GL_POINTS);
			//	glVertex3fv(tablica[i][j]);
			//glEnd();
			//linie w poziomie
			glBegin(GL_LINES);
				glVertex3fv(tablica[i][j]);
				if (j==n-1)
					if ((n-i)!=0 && (n-i)!=n)
						glVertex3fv(tablica[n-i][0]);
					else 
						true;
				else
					glVertex3fv(tablica[i][j+1]);
			glEnd();
			//linie w pionie
			glBegin(GL_LINES);
				glVertex3fv(tablica[i][j]);
				if (i==n-1)
					glVertex3fv(tablica[0][0]);
				else
					glVertex3fv(tablica[i+1][j]);
			glEnd();
			//linie przek¹tne
			//glBegin(GL_LINES);
			//	glVertex3fv(tablica[i][j]);
			//	if (!((j==n-1) || (i == n-1)))
			//		glVertex3fv(tablica[i+1][j+1]);
			//glEnd();
		}

	}
	*/
	for (int i =0; i < n; i++)
	{
		for (int j = 0; j < n; j++){
			if ( i == 0 ){
			//if ( false){
				glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]); 
					glVertex3fv(tablica[i][j]);
					glColor3f(kolory[i+1][j][0],kolory[i+1][j][1],kolory[i+1][j][2]); 
					glVertex3fv(tablica[i+1][j]);
					if (j==n-1){
						glColor3f(kolory[n-1][0][0],kolory[n-1][0][1],kolory[n-1][0][2]); 
						glVertex3fv(tablica[n-1][0]);
					}
					else
					{
						glColor3f(kolory[i+1][j+1][0],kolory[i+1][j+1][1],kolory[i+1][j+1][2]); 
						glVertex3fv(tablica[i+1][j+1]);
					}
					
				glEnd();
			} else if (i==n-1){
			//} else if (false){
				glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]); 
					glVertex3fv(tablica[i][j]);
					if (j==n-1){
						if ((n-i)!=0 && (n-i)!=n){
							glColor3f(kolory[n-i][0][0],kolory[n-i][0][1],kolory[n-i][0][2]); 
							glVertex3fv(tablica[n-i][0]);
						}
						else 
							true;
					}
					else
					{
						glColor3f(kolory[i][j+1][0],kolory[i][j+1][1],kolory[i][j+1][2]); 
						glVertex3fv(tablica[i][j+1]);
					}
					glColor3f(kolory[0][0][0],kolory[0][0][1],kolory[0][0][2]); 
					glVertex3fv(tablica[0][0]);
				glEnd();
			} else if (i==n/2-1){
				glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]); 
					glVertex3fv(tablica[i][j]);
					if (j==n-1){
						if ((n-i)!=0 && (n-i)!=n){
							glColor3f(kolory[n-i][0][0],kolory[n-i][0][1],kolory[n-i][0][2]); 
							glVertex3fv(tablica[n-i][0]);
						}
						else 
							true;
					}
					else
					{
						glColor3f(kolory[i][j+1][0],kolory[i][j+1][1],kolory[i][j+1][2]); 
						glVertex3fv(tablica[i][j+1]);
					}
					glColor3f(kolory[n/2][0][0],kolory[n/2][0][1],kolory[n/2][0][2]); 
					glVertex3fv(tablica[n/2][0]);
				glEnd();
			} else if ( i==n/2 ){
				glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]); 
					glVertex3fv(tablica[i][j]);
					glColor3f(kolory[i+1][j][0],kolory[i+1][j][1],kolory[i+1][j][2]); 
					glVertex3fv(tablica[i+1][j]);
					if (j==n-1){
						glColor3f(kolory[n/2-1][0][0],kolory[n/2-1][0][1],kolory[n/2-1][0][2]); 
						glVertex3fv(tablica[n/2-1][0]);
					}
					else
					{
						glColor3f(kolory[i+1][j+1][0],kolory[i+1][j+1][1],kolory[i+1][j+1][2]); 
						glVertex3fv(tablica[i+1][j+1]);
					}
					
				glEnd();
			} else{
				glBegin(GL_TRIANGLES);
						glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]); 
						glVertex3fv(tablica[i][j]);
						glColor3f(kolory[i+1][j][0],kolory[i+1][j][1],kolory[i+1][j][2]); 
						glVertex3fv(tablica[i+1][j]);
						if (j<n-1){
							glColor3f(kolory[i+1][j+1][0],kolory[i+1][j+1][1],kolory[i+1][j+1][2]); 
							glVertex3fv(tablica[i+1][j+1]);
						}
						else
						{
							if (i<n-i-1)
							{
								glColor3f(kolory[n-i-1][0][0],kolory[n-i-1][0][1],kolory[n-i-1][0][2]); 
								glVertex3fv(tablica[n-i-1][0]);
							}	else {
								glColor3f(kolory[n-i-1][0][0],kolory[n-i-1][0][1],kolory[n-i-1][0][2]); 
								glVertex3fv(tablica[n-i-1][0]);
							}
						}
				glEnd();
				glBegin(GL_TRIANGLES);
						glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]); 
						glVertex3fv(tablica[i][j]);
						if (j<n-1){
							glColor3f(kolory[i][j+1][0],kolory[i][j+1][1],kolory[i][j+1][2]); 
							glVertex3fv(tablica[i][j+1]);
							glColor3f(kolory[i+1][j+1][0],kolory[i+1][j+1][1],kolory[i+1][j+1][2]); 
							glVertex3fv(tablica[i+1][j+1]);
						}
						else
						{
							if (i<n-i)
							{
								glColor3f(kolory[n-i-1][0][0],kolory[n-i-1][0][1],kolory[n-i-1][0][2]); 
								glVertex3fv(tablica[n-i-1][0]);
								glColor3f(kolory[n-i][0][0],kolory[n-i][0][1],kolory[n-i][0][2]); 
								glVertex3fv(tablica[n-i][0]);
							} else
							{
								glColor3f(kolory[n-i-1][0][0],kolory[n-i-1][0][1],kolory[n-i-1][0][2]); 
								glVertex3fv(tablica[n-i-1][0]);
								glColor3f(kolory[n-i][0][0],kolory[n-i][0][1],kolory[n-i][0][2]); 
								glVertex3fv(tablica[n-i][0]);
							}
						}
				glEnd();
			}
		}
	}
}

void Axes(void)
{
	
	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0, 5.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0, 5.0 };
	//  pocz¹tek i koniec obrazu osi y

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

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej 
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y 

	glRotated(0.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	Egg();
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

	
	glutSwapBuffers();
	// 

}

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna 



	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

		vertical = 1;



	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)



	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji



	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej           



	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)            



	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);

	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej

}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli


void keys(unsigned char key, int x, int y)
{
	if(key == 'p') model = 1;
	if(key == 'w') model = 2;
	if(key == 's') model = 3;
    
	RenderScene(); // przerysowanie obrazu sceny
}
void main(void)
{
	int n = 20;
	kolory = new point3*[n];
	for (int i =0; i < n; i++)
	{
		kolory[i] = new point3[n];
		for (int j = 0; j < n; j++){
			kolory[i][j][0] = randomColor();
			kolory[i][j][1] = randomColor();
			kolory[i][j][2] = randomColor();
		}
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Uk³ad wspó³rzêdnych 3-D");

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem
	// gdy zajdzie potrzba przeryswania okna



	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna                        



	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych
	
	glutIdleFunc(spinEgg);
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}



/*************************************************************************************/