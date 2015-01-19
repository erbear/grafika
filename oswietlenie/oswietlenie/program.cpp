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
//static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };

static GLfloat theta1 = 0.0;   // k¹t obrotu obiektu
static GLfloat theta2 = 0.0;   // k¹t obrotu obiektu
static GLfloat theta3 = 0.0;   // k¹t obrotu obiektu
static GLfloat kat1 = 0.0, kat2 = 0.0, r = 0.0;
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy 
// 0 - nie naciœniêto ¿adnego klawisza
// 1 - naciœniêty zostaæ lewy klawisz
static int afterInit = 0;
static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;       // poprzednia pozycja kursora myszy
static int z_pos_old = 0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
static int delta_y = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
static int delta_z = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
// i poprzedni¹ kursora myszy 
/*************************************************************************************/
int model = 1;  // 1- punkty, 2- siatka, 3 - wype³nione trójk¹ty
int model2 = 4;  // 1- punkty, 2- siatka, 3 - wype³nione trójk¹ty
// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych
point3** kolory;
// Funkcja "bada" stan myszy i ustawia wartoœci odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		y_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		status = 1;          // wciêniêty zosta³ lewy klawisz myszy
	} else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		z_pos_old = y;         // przypisanie aktualnie odczytanej pozycji kursora 
		// jako pozycji poprzedniej
		status = 2;          // wciêniêty zosta³ lewy klawisz myszy
	}
	else
		status = 0;          // nie zosta³ wciêniêty ¿aden klawisz 
}

/*************************************************************************************/

// Funkcja "monitoruje" po³o¿enie kursora myszy i ustawia wartoœci odpowiednich 
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x =x - x_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy
	delta_y = y - y_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy    // obliczenie ró¿nicy po³o¿enia kursora myszy
	delta_z = y - z_pos_old;

	x_pos_old = x;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie
	y_pos_old = y;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie
	z_pos_old = y;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie

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

//    glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
//}
void Egg(void)
{
	int n = 20;
	point3** tablica = new point3*[n];
	point3** normalny = new point3*[n];
	for (int i =0; i < n; i++)
	{
		tablica[i] = new point3[n];
		normalny[i] = new point3[n];
		float u = (float)i/(float)n;

		for (int j = 0; j < n; j++){
			float v = (float)j / (float)n ;
			float x = (-1 * 90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(M_PI * v);
			float y = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2);
			float z = (-1 * 90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3)  +180 * pow(u, 2) - 45 * u) * sin(M_PI * v);
			tablica[i][j][0] = x;
			tablica[i][j][1] = y - 5;
			tablica[i][j][2] = z;
			
			//liczenie wektorow normalnych
			float xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45)* cos(M_PI * v);
			float xv = M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45 * u)*sin(M_PI*v);
			float yu = 640 * pow(u, 3) - 960 * pow(u, 2) + 320 * u;
			float yv = 0;
			float zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45)*sin(M_PI*v);
			float zv = -M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * pow(u, 2) + 45u)*cos(M_PI*v);

			normalny[i][j][0] = yu*zv-zu*yv;
			normalny[i][j][1] = zu*xv-xu*zv;
			normalny[i][j][2] = xu*yv-yu*xv;
			//normalizacja
			GLfloat dlugosc = sqrt(pow(normalny[i][j][0], 2) + pow(normalny[i][j][1], 2) + pow(normalny[i][j][2], 2));

			normalny[i][j][0] = normalny[i][j][0] / dlugosc;
			normalny[i][j][1] = normalny[i][j][1] / dlugosc;
			normalny[i][j][2] = normalny[i][j][2] / dlugosc;
		}
	}

	if (model ==1)
	{
		for (int i =0; i < n; i++)
		{
			for (int j = 0; j < n; j++){
				if ( i == 0 ){
				//if ( false){
					glBegin(GL_TRIANGLES);
						glColor3f(kolory[i][j][0],kolory[i][j][1],kolory[i][j][2]);
						glNormal3fv(normalny[i][j]);
						glVertex3fv(tablica[i][j]);

						glColor3f(kolory[i + 1][j][0], kolory[i + 1][j][1], kolory[i + 1][j][2]);
						glNormal3fv(normalny[i+1][j]);
						glVertex3fv(tablica[i+1][j]);

						if (j==n-1){
							glColor3f(kolory[n - 1][0][0], kolory[n - 1][0][1], kolory[n - 1][0][2]);
							glNormal3fv(normalny[n - 1][0]);
							glVertex3fv(tablica[n-1][0]);
						}
						else
						{
							glColor3f(kolory[i + 1][j + 1][0], kolory[i + 1][j + 1][1], kolory[i + 1][j + 1][2]);
							glNormal3fv(normalny[i + 1][j + 1]);
							glVertex3fv(tablica[i+1][j+1]);
						}
						
					glEnd();
				} else if (i==n-1){
				//} else if (false){
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0], kolory[i][j][1], kolory[i][j][2]);
					glNormal3fv(normalny[i][j]);
						glVertex3fv(tablica[i][j]);
						if (j==n-1){
							if ((n-i)!=0 && (n-i)!=n){
								glColor3f(kolory[n - i][0][0], kolory[n - i][0][1], kolory[n - i][0][2]);
								glNormal3fv(normalny[n - i][0]);
								glVertex3fv(tablica[n-i][0]);
							}
							else 
								true;
						}
						else
						{
							glColor3f(kolory[i][j + 1][0], kolory[i][j + 1][1], kolory[i][j + 1][2]);
							glNormal3fv(normalny[i][j + 1]);
							glVertex3fv(tablica[i][j+1]);
						}
						glColor3f(kolory[0][0][0], kolory[0][0][1], kolory[0][0][2]);
						glNormal3fv(normalny[0][0]);
						glVertex3fv(tablica[0][0]);
					glEnd();
				} else if (i==n/2-1){
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0], kolory[i][j][1], kolory[i][j][2]);
					glNormal3fv(normalny[i][j]);
						glVertex3fv(tablica[i][j]);
						if (j==n-1){
							if ((n-i)!=0 && (n-i)!=n){
								glColor3f(kolory[n - i][0][0], kolory[n - i][0][1], kolory[n - i][0][2]);
								glNormal3fv(normalny[n - i][0]);
								glVertex3fv(tablica[n-i][0]);
							}
							else 
								true;
						}
						else
						{
							glColor3f(kolory[i][j + 1][0], kolory[i][j + 1][1], kolory[i][j + 1][2]);
							glNormal3fv(normalny[i][j + 1]);
							glVertex3fv(tablica[i][j+1]);
						}
						glColor3f(kolory[n / 2][0][0], kolory[n / 2][0][1], kolory[n / 2][0][2]);
						glNormal3fv(normalny[n / 2][0]);
						glVertex3fv(tablica[n/2][0]);
					glEnd();
				} else if ( i==n/2 ){
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0], kolory[i][j][1], kolory[i][j][2]);
					glNormal3fv(normalny[i][j]);
						glVertex3fv(tablica[i][j]);
						glColor3f(kolory[i + 1][j][0], kolory[i + 1][j][1], kolory[i + 1][j][2]);
						glNormal3fv(normalny[i + 1][j]);
						glVertex3fv(tablica[i+1][j]);
						if (j==n-1){
							glColor3f(kolory[n / 2 - 1][0][0], kolory[n / 2 - 1][0][1], kolory[n / 2 - 1][0][2]);
							glNormal3fv(normalny[n / 2 - 1][0]);
							glVertex3fv(tablica[n/2-1][0]);
						}
						else
						{
							glColor3f(kolory[i + 1][j + 1][0], kolory[i + 1][j + 1][1], kolory[i + 1][j + 1][2]);
							glNormal3fv(normalny[i + 1][j + 1]);
							glVertex3fv(tablica[i+1][j+1]);
						}
						
					glEnd();
				} else{
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0], kolory[i][j][1], kolory[i][j][2]);
					glNormal3fv(normalny[i][j]);
							glVertex3fv(tablica[i][j]);
							glColor3f(kolory[i + 1][j][0], kolory[i + 1][j][1], kolory[i + 1][j][2]);
							glNormal3fv(normalny[i + 1][j]);
							glVertex3fv(tablica[i+1][j]);
							if (j<n-1){
								glColor3f(kolory[i + 1][j + 1][0], kolory[i + 1][j + 1][1], kolory[i + 1][j + 1][2]);
								glNormal3fv(normalny[i + 1][j + 1]);
								glVertex3fv(tablica[i+1][j+1]);
							}
							else
							{
								if (i<n-i-1)
								{
									glColor3f(kolory[n - i - 1][0][0], kolory[n - i - 1][0][1], kolory[n - i - 1][0][2]);
									glNormal3fv(normalny[n - i - 1][0]);
									glVertex3fv(tablica[n-i-1][0]);
								}	else {
									glColor3f(kolory[n - i - 1][0][0], kolory[n - i - 1][0][1], kolory[n - i - 1][0][2]);
									glNormal3fv(normalny[n - i - 1][0]);
									glVertex3fv(tablica[n-i-1][0]);
								}
							}
					glEnd();
					glBegin(GL_TRIANGLES);
					glColor3f(kolory[i][j][0], kolory[i][j][1], kolory[i][j][2]);
					glNormal3fv(normalny[i][j]);
							glVertex3fv(tablica[i][j]);
							if (j<n-1){
								glColor3f(kolory[i][j + 1][0], kolory[i][j + 1][1], kolory[i][j + 1][2]);
								glNormal3fv(normalny[i][j + 1]);
								glVertex3fv(tablica[i][j+1]);
								glColor3f(kolory[i + 1][j + 1][0], kolory[i + 1][j + 1][1], kolory[i + 1][j + 1][2]);
								glNormal3fv(normalny[i + 1][j + 1]);
								glVertex3fv(tablica[i+1][j+1]);
							}
							else
							{
								if (i<n-i)
								{
									glColor3f(kolory[n - i - 1][0][0], kolory[n - i - 1][0][1], kolory[n - i - 1][0][2]);
									glNormal3fv(normalny[n - i - 1][0]);
									glVertex3fv(tablica[n-i-1][0]);
									glColor3f(kolory[n - i][0][0], kolory[n - i][0][1], kolory[n - i][0][2]);
									glNormal3fv(normalny[n - i][0]);
									glVertex3fv(tablica[n-i][0]);
								} else
								{
									glColor3f(kolory[n - i - 1][0][0], kolory[n - i - 1][0][1], kolory[n - i - 1][0][2]);
									glNormal3fv(normalny[n - i - 1][0]);
									glVertex3fv(tablica[n-i-1][0]);
									glColor3f(kolory[n - i][0][0], kolory[n - i][0][1], kolory[n - i][0][2]);
									glNormal3fv(normalny[n - i][0]);
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
					glBegin(GL_POINTS);;
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
				//linie przek¹tne
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

	int upY = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
	if (model2 == 5)
	{
		if (status == 2)                     // jeœli lewy klawisz myszy wciêniêty
		{
			viewer[2] += delta_z;
		}
		viewer[0] = 0.0;
		viewer[1] = 0.0;
	}
	if (model2 == 4){

		if (afterInit == 0){
			afterInit = 1;
			r = 15.0;
		}

		if (status == 1){
			kat1 += delta_x/50.0;
			kat2 += delta_y/50.0;
		}
		else if (status == 2){
			if (r+delta_z>0)
				r += delta_z;
		}
		if(kat2 >= M_PI) 
			kat2 -= 2*M_PI;
		else if(kat2 <= -M_PI) 
			kat2 += 2*M_PI;
		

		if(kat2 < M_PI/2 && kat2 > -M_PI/2) upY = 1;
		else upY = -1;
		
		viewer[0] = r*cos(kat1)*cos(kat2);
		viewer[1] = r*sin(kat2);
		viewer[2] = r*sin(kat1)*cos(kat2);
	}
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, upY,0.0);
	// Zdefiniowanie po³o¿enia obserwatora

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej 
	if (model2 == 5)
	{
		if (status == 1)                     // jeœli lewy klawisz myszy wciêniêty
		{
			theta1 += delta_x*pix2angle;    // modyfikacja k¹ta obrotu o kat proporcjonalny
			theta2 += delta_y*pix2angle;   // modyfikacja k¹ta obrotu o kat proporcjonalny

		}                                  // do ró¿nicy po³o¿eñ kursora myszy

		glRotatef(theta1, 0.0, 1.0, 0.0);  //obrót obiektu o nowy k¹t
		glRotatef(theta2, 1.0, 0.0, 0.0);  //obrót obiektu o nowy k¹t
	}
	
	

	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y 

	//glRotated(0.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni
	
	//glRotatef(theta[0], 1.0, 0.0, 0.0);

	//glRotatef(theta[1], 0.0, 1.0, 0.0);

	//glRotatef(theta[2], 0.0, 0.0, 1.0);

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
	/*************************************************************************************/
	//  Definicja materia³u z jakiego zrobiony jest czajnik 
	//  i definicja Ÿród³a œwiat³a
	/*************************************************************************************/

	/*************************************************************************************/
	// Definicja materia³u z jakiego zrobiony jest czajnik 

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego                

	GLfloat mat_shininess = { 50.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni

	/*************************************************************************************/
	// Definicja Ÿród³a œwiat³a

	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	// po³o¿enie Ÿród³a

	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_linear = { 0.1f };
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji 
	// odleg³oœci od Ÿród³a

	GLfloat att_quadratic = { 0.001f };
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	/*************************************************************************************/

	// Ustawienie parametrów materia³u i Ÿród³a œwiat³a

	/*************************************************************************************/
	// Ustawienie patrametrów materia³u

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	/*************************************************************************************/
	// Ustawienie parametrów Ÿród³a

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	/*************************************************************************************/
	// Ustawienie opcji systemu oœwietlania sceny 

	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny 
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora 

	/*************************************************************************************/

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / ((float)horizontal);  // przeliczenie pikseli na stopnie
	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej 

	gluPerspective(70, 1.0, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej 
}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli


void keys(unsigned char key, int x, int y)
{
	if(key == 'p') model = 1;
	if(key == 'w') model = 2;
	if(key == 's') model = 3;
	if(key == 'v') model2 = 4;
	if(key == 'b') model2 = 5;

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
	glutKeyboardFunc(keys);
	glutMouseFunc(Mouse);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie ruchu myszy
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych
	
	//glutIdleFunc(spinEgg);
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

}



/*************************************************************************************/