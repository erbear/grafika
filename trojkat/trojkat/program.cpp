/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

# define M_PI           3.14159265358979323846

typedef GLfloat point3[3];
using namespace std;

point3* punkcik = new point3[4];
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
static GLfloat wspolrzedne[] = { 0.0, 0.0, 0.0};

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
point3* kolory;
float randomColor(int i)
{
	srand( i );
	return ((float)(rand()%10)+1)/10; 
} 
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
void losujKolory()
{
	int n = 7;
	kolory = new point3[n];
	for (int i =0; i < n; i++)
	{
		kolory[i][0] = randomColor(i);
		kolory[i][1] = randomColor(i);
		kolory[i][2] = randomColor(i);
	}
}
void budujTrojkat(point3* p, float d = 0){
	point3 wierzcholek;
	float dlugosc = abs(p[0][0] - p[1][0]);
	if (d!=0)
		dlugosc = d;
	wierzcholek[0]=p[0][0] + dlugosc/2;
	wierzcholek[1]=p[0][1] + dlugosc;
	wierzcholek[2]=p[0][2] + dlugosc/2;
	for (int j = 0; j<4; j++)
	{
		glBegin(GL_TRIANGLES);
			GLfloat c= 0.2 * (j+1);
			glColor3f(c, c, c);
			glColor3f(kolory[0][0],kolory[0][1],kolory[0][2]);
			glVertex3fv(p[j]);
			glColor3f(kolory[1][0],kolory[1][1],kolory[1][2]);
			if (j+1>3)
				glVertex3fv(p[0]);
			else
				glVertex3fv(p[j+1]);
			glColor3f(kolory[2][0],kolory[2][1],kolory[2][2]);
			glVertex3fv(wierzcholek);
		glEnd();
		glBegin(GL_QUADS);
			glColor3f(kolory[3][0],kolory[3][1],kolory[3][2]);
			glVertex3fv(p[0]);
			glColor3f(kolory[4][0],kolory[4][1],kolory[4][2]);
			glVertex3fv(p[1]);
			glColor3f(kolory[5][0],kolory[5][1],kolory[5][2]);
			glVertex3fv(p[2]);
			glColor3f(kolory[6][0],kolory[6][1],kolory[6][2]);
			glVertex3fv(p[3]);
		glEnd();
	}
}
void oliczWierzcholek(point3* p)
{

}
void dzielTrojkaty(point3* p, int poziom, float d = 0)
{	
	int ostatniPoziom = 2;
	int nastepnyPoziom = poziom + 1;
	point3* w = new point3[4];
	point3* wierzcholki = new point3[4];
	//pierwszy
	float dlugosc = abs(p[0][0] - p[1][0]);
	if (d!=0)
		dlugosc = d;
	w[0][0] = p[0][0];
	w[0][1] = p[0][1];
	w[0][2] = p[0][2];
	
	w[1][0] = p[0][0] + dlugosc/2;
	w[1][1] = p[0][1];
	w[1][2] = p[0][2];

	w[2][0] = p[0][0] + dlugosc/2;
	w[2][1] = p[0][1];
	w[2][2] = p[0][2] + dlugosc/2;

	w[3][0] = p[0][0];
	w[3][1] = p[0][1];
	w[3][2] = p[0][2] + dlugosc/2;
	
	if (poziom<ostatniPoziom)
		dzielTrojkaty(w, nastepnyPoziom, dlugosc/2);
	else
		budujTrojkat(w);
	
	float dlugoscWierzcholka = abs(w[0][0] - w[1][0]);
	wierzcholki[0][0]=w[0][0] + dlugoscWierzcholka/2;
	wierzcholki[0][1]=w[0][1] + dlugoscWierzcholka;
	wierzcholki[0][2]=w[0][2] + dlugoscWierzcholka/2;

	w[0][0] = p[0][0];
	w[0][1] = p[0][1];
	w[0][2] = p[0][2]+ dlugosc/2;
	
	w[1][0] = p[0][0]+ dlugosc/2;
	w[1][1] = p[0][1];
	w[1][2] = p[0][2]+ dlugosc/2;

	w[2][0] = p[0][0]+ dlugosc/2;
	w[2][1] = p[0][1];
	w[2][2] = p[0][2]+ dlugosc;

	w[3][0] = p[0][0];
	w[3][1] = p[0][1];
	w[3][2] = p[0][2]+ dlugosc;

	if (poziom<ostatniPoziom)
		dzielTrojkaty(w, nastepnyPoziom, dlugosc/2);
	else
		budujTrojkat(w);
	
	wierzcholki[1][0]=w[0][0] + dlugoscWierzcholka/2;
	wierzcholki[1][1]=w[0][1] + dlugoscWierzcholka;
	wierzcholki[1][2]=w[0][2] + dlugoscWierzcholka/2;
	
	w[0][0] = p[0][0] + dlugosc/2;
	w[0][1] = p[0][1];
	w[0][2] = p[0][2] + dlugosc/2;
	
	w[1][0] = p[0][0] + dlugosc;
	w[1][1] = p[0][1];
	w[1][2] = p[0][2] + dlugosc/2;

	w[2][0] = p[0][0] + dlugosc;
	w[2][1] = p[0][1];
	w[2][2] = p[0][2] + dlugosc;

	w[3][0] = p[0][0]+ dlugosc/2;
	w[3][1] = p[0][1];
	w[3][2] = p[0][2] + dlugosc;

	if (poziom<ostatniPoziom)
		dzielTrojkaty(w, nastepnyPoziom, dlugosc/2);
	else
		budujTrojkat(w);

	wierzcholki[2][0]=w[0][0] + dlugoscWierzcholka/2;
	wierzcholki[2][1]=w[0][1] + dlugoscWierzcholka;
	wierzcholki[2][2]=w[0][2] + dlugoscWierzcholka/2;

	w[0][0] = p[0][0] + dlugosc/2;
	w[0][1] = p[0][1];
	w[0][2] = p[0][2];
	
	w[1][0] = p[0][0] + dlugosc;
	w[1][1] = p[0][1];
	w[1][2] = p[0][2];

	w[2][0] = p[0][0] + dlugosc;
	w[2][1] = p[0][1];
	w[2][2] = p[0][2] + dlugosc/2;

	w[3][0] = p[0][0]+ dlugosc/2;
	w[3][1] = p[0][1];
	w[3][2] = p[0][2] + dlugosc/2;

	if (poziom<ostatniPoziom)
		dzielTrojkaty(w, nastepnyPoziom, dlugosc/2);
	else
		budujTrojkat(w);

	wierzcholki[3][0]=w[0][0] + dlugoscWierzcholka/2;
	wierzcholki[3][1]=w[0][1] + dlugoscWierzcholka;
	wierzcholki[3][2]=w[0][2] + dlugoscWierzcholka/2;
	if (poziom<ostatniPoziom)
		dzielTrojkaty(wierzcholki, nastepnyPoziom, dlugosc/2);
	else
		budujTrojkat(wierzcholki, dlugosc/2);
}
void Egg(void)
{
	int n = 10;
	point3 pw;
	point3* p = new point3[4];
	int krotnosc = 3;
	float dlugoscBoku = 2 * krotnosc;// 1/2 boku
	float dlugoscWysokosci = 2 * krotnosc;
	p[0][0]= -1 * krotnosc;
	p[0][1]= -1 * krotnosc;
	p[0][2]= -1 * krotnosc;

	p[1][0]= 1 * krotnosc;
	p[1][1]= -1 * krotnosc;
	p[1][2]= -1 * krotnosc;

	p[2][0]= 1 * krotnosc;
	p[2][1]= -1 * krotnosc;
	p[2][2]= 1 * krotnosc;

	p[3][0]= -1 * krotnosc;
	p[3][1]= -1 * krotnosc;
	p[3][2]= 1 * krotnosc;

	pw[0] = 0 * krotnosc;
	pw[1] = 1 * krotnosc;
	pw[2] = 0 * krotnosc;
	punkcik = p;
	dzielTrojkaty(p, 1);
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


bool isPass(GLfloat px, GLfloat py, GLfloat pz){
	int odlegloscOdTrojkata = 4;
	GLfloat ograniczeniePlus = odlegloscOdTrojkata - ((py+3)/2);
	GLfloat ograniczenieMinus = ((py+3)/2) - odlegloscOdTrojkata;
	bool przedzialX = (px>ograniczeniePlus) || (px<ograniczenieMinus);
	bool przedzialZ = (pz>ograniczeniePlus) || (pz<ograniczenieMinus);
	bool przedzialY = (py>3) || (py<-3);

	return przedzialX || przedzialY || przedzialZ;
}
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej 
	if (afterInit == 0){
		afterInit = 1;
		r = 15.0;
	}
	
	int odlegloscOdTrojkata = 4;
	if (status == 1){
		GLfloat pointX = r*cos(kat1+delta_x/100.0)*cos(kat2+delta_y/100.0);
		GLfloat pointZ = r*sin(kat1+delta_x/100.0)*cos(kat2+delta_y/100.0);
		GLfloat pointY = r*sin(kat2+delta_y/100.0);
		if (isPass(pointX, pointY ,pointZ)){
			kat1 += delta_x/100.0;
			kat2 += delta_y/100.0;
		}
	}
	else if (status == 2){
		if (r+delta_z/50.0>0){
			GLfloat pointX = (r+delta_z/50.0)*cos(kat1)*cos(kat2);
			GLfloat pointZ = (r+delta_z/50.0)*sin(kat1)*cos(kat2);
			GLfloat pointY = (r+delta_z/50.0)*sin(kat2);
			if (isPass(pointX, pointY ,pointZ)){
				r += delta_z/50.0;
			}
		}
		else
			r = 0.0001;
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

	glColor3f(1.0f, 1.0f, 1.0f);

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
	losujKolory();
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

}



/*************************************************************************************/