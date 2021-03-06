#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "glut.h"
#include <vector>
#include <algorithm>
#include "const.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
using namespace std;

double a = 0, b = 0, c = 0; 
float angle = 0.0;
float angle2 = 0.0;
float zoom = 0;
float angle3 = 0.0;
double Z1 = 0, Z2 = 0;
//////////////////////////////////////////
double fie  = 0, angle_qe = 0, O = 0;
double le = 0;
double l = 0 ;
double E = 0;
double qe = 0;
double R1 = 0, R2 = 0;
int iter = 1;
int N = 0;
bool eraseBool = 0;
double alpha = 0;
vector<double> x, y, z;
//double DTM = 0;
////////////////////////////////////////////////      OPENGL           /////////////////////////////////////////////////////////////////

void special_kb(int key, int, int)
{
	if (key == GLUT_KEY_LEFT)
		angle3 += 1.8;
	if (key == GLUT_KEY_RIGHT)
		angle3 -= 1.8;
	if (key == GLUT_KEY_DOWN)
		zoom -= 0.1;
	if (key == GLUT_KEY_UP)
		zoom += 0.1;
	if (key == GLUT_KEY_PAGE_DOWN)
		angle += 1.8;
	if (key == GLUT_KEY_PAGE_UP)
		angle -= 1.8;


	if (key == GLUT_KEY_HOME)
		angle2 -= 1.8;
	if (key == GLUT_KEY_END)
		angle2 += 1.8;

	glutPostRedisplay();


}

void read_key(unsigned char key, int, int)
{
	if (27 == key)
		exit(0);
	if (key == 'a')
		Z1 += 0.5;
	if (key == 'd')
		Z1 -= 0.5;
	if (key == 'w')
		Z2 -= 0.5;
	if (key == 's')
		Z2 += 0.5;
	glutPostRedisplay();
}

bool elastic(double E)
{ 
	x.push_back(0);
	y.push_back(b);
	z.push_back(0);
	double Bn_1 = 0;
	double qe_1 = 0;
	for (iter ;  ; )
	{
		l = Ry * 1.25992 / E;
		//Rezerford
		//qe = pi * Z * Z * pow(e, 4) / (pow((E*e), 2)* l*(2 + l)) / Ry / e;
		//R1 = (double)rand() / RAND_MAX;
		//R1 = 0.5;
		//qe = 2.5e-22;

		//Mott
		alpha = 0.0034*pow(Z, 2.0 / 3.0) / E;
		qe = (5.21*1e-21*pow(Z, 2) * 4 * pi*lCof*(1 - exp(-bCof * sqrt(E)))*pow(E + 511, 2))
			/ (pow(E, 2)*alpha*(alpha + 1)*pow(E + 1022, 2));
		R1 = (double)rand() / RAND_MAX;
		if((1 - 2 * l * R1 / (2 + l - 2 * R1) <= 1) && (1 - 2 * l * R1 / (2 + l - 2 * R1) >= -1 ))
		{
			O = acos(1 - 2 * l * R1 / (2 + l - 2 * R1));
			angle_qe = O;
			R2 = (double)rand() / RAND_MAX;
			fie = R2 *2* pi;
			le = A / (Na * densityBe * qe);
			x.push_back(le * 1e6 * sin(angle_qe)*cos(fie));
			y.push_back(le * 1e6 * cos(angle_qe));
			z.push_back(le * 1e6 * cos(angle_qe)*sin(fie));
			if (y[iter] != b)
			{
				x[iter] = x[iter] + x[iter - 1];
				y[iter] = y[iter - 1] - y[iter];
				z[iter] = z[iter] + z[iter - 1];
				if ((y[iter] <= -b) && (y[iter - 1] <= -b) || (x[iter] <= -b) || (z[iter] <= -b) || (x[iter] >= b) || (z[iter] >= b))
				{
					x.erase(x.begin() + iter);
					y.erase(y.begin() + iter);
					z.erase(z.begin() + iter);
					++iter;
					return 1;
				}
			}
			++iter;
		}
	}
}


void elastic(double E , int i)
{
	x.push_back(0);
	y.push_back(b);
	z.push_back(0);
	for (int j = 0; j < i; j++)
	{
		l = Ry * 1.25992 / E;
		alpha = 0.0034*pow(Z, 2.0 / 3.0) / E;
		qe = (5.21*1e-21*pow(Z, 2) * 4 * pi*lCof*(1 - exp(-bCof * sqrt(E)))*pow(E + 511, 2))
			/ (pow(E, 2)*alpha*(alpha + 1)*pow(E + 1022, 2));
		R1 = (double)rand() / RAND_MAX;
		O = acos(1 - 2 * l * R1 / (2 + l - 2 * R1));
		if ((1 - 2 * l * R1 / (2 + l - 2 * R1) <= 1) && (1 - 2 * l * R1 / (2 + l - 2 * R1) >= -1))
		{
			angle_qe = O;
			R2 = (double)rand() / RAND_MAX;
			fie = R2 * 2 * pi;
			le = A / (Na * densityBe * qe);
			x.push_back(le * 1e6 * sin(angle_qe)*cos(fie));
			y.push_back(le * 1e6 * cos(angle_qe));
			z.push_back(le * 1e6 * cos(angle_qe)*sin(fie));
		}
	}
	eraseBool = 1;
}

void erase()
{
	for (int i = 0; i < x.size(); i++)
	{
		if (y[i] == 1);
		else
		{
			if (i != 0)
			{
				x[i] = x[i] + x[i - 1];
				y[i] = y[i - 1] - y[i];
				z[i] = z[i] + z[i - 1];
			}
		}
	}
	for (int i = 0; i < y.size() - 1; i++)
	{
		if ((x[i] > 1) || (x[i] < -1) || (y[i] > 1) || (y[i] < -1) || (z[i] > 1) || (z[i] < -1))
		{
			if ((y[i + 1]) != 1)
			{
				x.erase(x.begin() + i + 1);
				y.erase(y.begin() + i + 1);
				z.erase(z.begin() + i + 1);
				i--;
			}
		}
	}
}

void quads()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(-a, b, c);
	glVertex3f(-a, -b, c);
	glVertex3f(-a, -b, -c);
	glVertex3f(-a, b, -c);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-a, -b, c);
	glVertex3f(a, -b, c);
	glVertex3f(a, -b, -c);
	glVertex3f(-a, -b, -c);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-a, -b, c);
	glVertex3f(a, -b, c);
	glVertex3f(a, b, c);
	glVertex3f(-a, b, c);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(a, -b, c);
	glVertex3f(a, -b, -c);
	glVertex3f(a, b, -c);
	glVertex3f(a, b, c);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(a, b, c);
	glVertex3f(a, b, -c);
	glVertex3f(-a, b, -c);
	glVertex3f(-a, b, c);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, b, 0);
	glVertex3f(0, -b, 0);
	glEnd();


}
///////////////////////////////////////////////////////////////// RENDER SCENE  //////////////////////////////////////////////
void RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 600, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0, 0, -3);
	glTranslatef(Z1, Z2, zoom);

	glRotatef(angle, 0, 0, 1);
	glRotatef(angle2, 1, 0, 0);
	glRotatef(angle3, 0, 1, 0);

	quads();

	glColor3f(0, 0, 1);
	for (int i = 1; i < x.size() ; i++)
	{
		glBegin(GL_LINE_STRIP);
		if (y[i] == a);
		else
		{
			glVertex3f(x[i - 1], y[i - 1], z[i - 1]);
			glVertex3f(x[i], y[i], z[i]);
			glEnd();
		}
	}
	glutSwapBuffers();
}


//////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////
int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(700,100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("3D модель");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 1);
	//////////////////////////////////////////////////////////   /////////////////////////////////////////////
	cout << "enter the thickness of the target [nm] = ";
	cin >> a;
	a /= 2000.0;
	b = a;
	c = a * 2;
	a = c;
	cout << "enter the number of electrons = ";
	cin >> N;
	if (N != 0)
	{
		cout << "enter the energy of the electrons [eV]= ";
		cin >> E;
		for (int i = 0; i < N; i++)
		{
			elastic(E);
			//cout << endl << "i = " << i + 1 << endl;
		}
		cout << "qe = " << qe << endl << "le = " << le << endl;
		if (eraseBool == 1)
			erase();
	}
	//cout << "enter the distance to measure [nm] = ";
	//cin >> DTM;
	//double DTM = 0.1;
	vector<double> srez;
	for (double DTM = 0.1; DTM <= a; DTM += 0.1)
	{
		for (int i = 0; i < y.size(); i++)
		{
			
			if (y[i] > (a/2 - DTM - a * 0.05) && (y[i] < (a/2 - DTM + a * 0.05)))
			{
				srez.push_back(x[i]);
				srez.push_back(z[i]);
			}
		}
		sort(srez.begin(), srez.end());
		cout << DTM * 1000 << " : " << srez[0]*1000 << " "  << srez[srez.size() - 1]*1000 << endl;
		srez.clear();
	}
	//////////////////////////////////////////////////////////   /////////////////////////////////////////////
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(read_key);
	glutSpecialFunc(special_kb);
	glutMainLoop();
	return 0;
}