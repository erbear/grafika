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
//static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };

static GLfloat theta1 = 0.0;   // k�t obrotu obiektu
static GLfloat theta2 = 0.0;   // k�t obrotu obiektu
static GLfloat theta3 = 0.0;   // k�t obrotu obiektu
static GLfloat kat1 = 0.0, kat2 = 0.0, r = 0.0;
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy 
// 0 - nie naci�ni�to �adnego klawisza
// 1 - naci�ni�ty zosta� lewy klawisz
static int afterInit = 0;
static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;       // poprzednia pozycja kursora myszy
static int z_pos_old = 0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;        // r�nica pomi�dzy pozycj� bie��c�
static int delta_y = 0;        // r�nica pomi�dzy pozycj� bie��c�
static int delta_z = 0;        // r�nica pomi�dzy pozycj� bie��c�
// i poprzedni� kursora myszy 
/*************************************************************************************/
int model = 1;  // 1- punkty, 2- siatka, 3 - wype�nione tr�jk�ty
// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych
point3** kolory;
// Funkcja "bada" stan myszy i ustawia warto�ci odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		status = 1;          // wci�ni�ty zosta� lewy klawisz myszy
	} else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		z_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		status = 2;          // wci�ni�ty zosta� lewy klawisz myszy
	}
	else
		status = 0;          // nie zosta� wci�ni�ty �aden klawisz 
}

/*************************************************************************************/

// Funkcja "monitoruje" po�o�enie kursora myszy i ustawia warto�ci odpowiednich 
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x =x - x_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy
	delta_y = y - y_pos_old;     // obliczenie r�nicy po�o�enia kursora myszy    // obliczenie r�nicy po�o�enia kursora myszy
	delta_z = y - z_pos_old;

	x_pos_old = x;            // podstawienie bie��cego po�o�enia jako poprzednie
	y_pos_old = y;            // podstawienie bie��cego po�o�enia jako poprzednie
	z_pos_old = y;            // podstawienie bie��cego po�o�enia jako poprzednie

	glutPostRedisplay();     // przerysowanie obrazu sceny
}
float randomColor()
{
	return ((float)(rand()%10)+1)/10; 
} 
//void spinEgg()
//{
//    theta[0] -= 0.1;
//    if( theta[0] > 360.0 ) theta[0] -= 360.0;

//    theta[1] -= 0.1;
//    if( theta[1] > 360.0 ) theta[1] -= 360.0;

//    theta[2] -= 0.1;
//    if( theta[2] > 360.0 ) theta[2] -= 360.0;

//    glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
//}
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
	
	*/
	if (model ==1)
	{
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
	} else
	{
		for (int i =0; i < n; i++)
		{
			for (int j = 0; j < n; j++){
				if (model ==2)
				{
				glBegin(GL_POINTS);
					glVertex3fv(tablica[i][j]);
				glEnd();
				}
				if (model ==3)
				{
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
				}
				//linie przek�tne
				//glBegin(GL_LINES);
				//	glVertex3fv(tablica[i][j]);
				//	if (!((j==n-1) || (i == n-1)))
				//		glVertex3fv(tablica[i+1][j+1]);
				//glEnd();
			}

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
	/*
	if (status == 2)                     // je�li lewy klawisz myszy wci�ni�ty
	{
		viewer[2] += delta_z;
	}
	*/
	if (afterInit == 0){
		afterInit = 1;
		r = 15.0;
	}

	if (status == 1){
		kat1 += delta_x/50.0;
		kat2 += delta_y/50.0;
	}
	else if (status == 2){
		if (r>0)
			r += delta_z;
		else
			r -=delta_z;
	}
	if(kat2 >= M_PI) 
		kat2 -= 2*M_PI;
    else if(kat2 <= -M_PI) 
		kat2 += 2*M_PI;
	
	int upY;

    if(kat2 < M_PI/2 && kat2 > -M_PI/2) upY = 1;
    else upY = -1;
	
	viewer[0] = r*cos(kat1)*cos(kat2);
	viewer[1] = r*sin(kat2);
	viewer[2] = r*sin(kat1)*cos(kat2);
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, upY,0.0);
	// Zdefiniowanie po�o�enia obserwatora

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej 
	/* zad 1
	if (status == 1)                     // je�li lewy klawisz myszy wci�ni�ty
	{
		theta1 += delta_x*pix2angle;    // modyfikacja k�ta obrotu o kat proporcjonalny
		theta2 += delta_y*pix2angle;   // modyfikacja k�ta obrotu o kat proporcjonalny

	}                                  // do r�nicy po�o�e� kursora myszy

	glRotatef(theta1, 0.0, 1.0, 0.0);  //obr�t obiektu o nowy k�t
	glRotatef(theta2, 1.0, 0.0, 0.0);  //obr�t obiektu o nowy k�t
	*/
	
	

	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia�y 

	//glRotated(0.0, 1.0, 1.0, 1.0);  // Obr�t o 60 stopni
	
	//glRotatef(theta[0], 1.0, 0.0, 0.0);

	//glRotatef(theta[1], 0.0, 1.0, 0.0);

	//glRotatef(theta[2], 0.0, 0.0, 1.0);

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
	pix2angle = 360.0 / ((float)horizontal);  // przeliczenie pikseli na stopnie
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie��cej 

	gluPerspective(70, 1.0, 1.0, 30.0);
	// Ustawienie parametr�w dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielko�ci okna okna widoku (viewport) w zale�no�ci
	// relacji pomi�dzy wysoko�ci� i szeroko�ci� okna

	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej 
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli


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
	glutKeyboardFunc(keys);
	glutMouseFunc(Mouse);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcj� zwrotn� odpowiedzialn� za badanie ruchu myszy
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych
	
	//glutIdleFunc(spinEgg);
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}



/*************************************************************************************/