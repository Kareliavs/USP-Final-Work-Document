#include <bits/stdc++.h> 
#include <GL/glut.h> //Graphic Library
///Compilation -----> g++ -std=c++11 main.cpp -o demo -lglut -lGL
using namespace std;
unsigned t0, t1;
float limit=1000000, size = 1.0f, maxx,minx,maxy,miny, cost=0;
int up,down, DFS_Key,BFS_Key,AA_Key,HC_Key, high,width, coord_ini,coord_fin, N_DOTS;
vector <pair<float,float>> dots;
vector<int> dots_traveled, DFS_DT,BFS_DT,AA_DT,HC_DT;
vector < pair<pair<float,float>,pair<float,float>> > edges,path, DFS_Path,BFS_Path,AA_Path,HC_Path;
vector <vector<float>> grafo;
vector<bool> visited;
vector < vector<int> > graph,tree;
pair<float,float>  meta,start;

float distance(float x1, float x2, float y1, float y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
#include "HillClimbing.hpp"
#include "Aasterisk.hpp"
#include "DFS.hpp"
#include "BFS.hpp"

void Build_graph()
{	
	//Empty matrix
	vector<float> vect;	
	for(int i=0; i<dots.size();i++)
		vect.push_back(0);	
	for(int i=0; i<dots.size();i++)
		grafo.push_back(vect);
	float d;
	//Adjacence matrix
	for(int i=0; i<dots.size();i++)
	{	vector<int> adj;
		for(int j=0; j<dots.size();j++)
		{   
			d=distance(dots[i].first,dots[j].first,dots[i].second,dots[j].second);
			if(d<limit)
			{
				grafo[i][j]=d;
				edges.push_back(make_pair(make_pair(dots[i].first,dots[i].second),make_pair(dots[j].first,dots[j].second)));///Grafico
				adj.push_back(j);
			}
		}
		graph.push_back(adj);
	}
}

void Build_tree()
{
	for(int i=0; i<dots.size();i++)
	{	
		vector<int> sons;
		for(int j=i; j<dots.size();j++)
		{
			if(grafo[i][j]<limit)
				sons.push_back(j);
		}
		tree.push_back(sons);
	}	
}

void Clear()
{
	cost=0;
	dots_traveled.clear();
    path.clear();	
    visited.clear();
    for(int i=0;i<dots.size();i++)
    	visited.push_back(false); 
}

void Path()
{   cost=0;
	cout<<"Path              : ";
	for(int i =0; i<dots_traveled.size(); i++)
		cout<<dots_traveled[i]<<",";
	cout<<endl;
  	if(dots_traveled.size()>0)
	{
		for(int i =0; i<dots_traveled.size()-1; i++)
		{   
			path.push_back(make_pair(dots[dots_traveled[i]],dots[dots_traveled[i+1]]));
			cost+=grafo[dots_traveled[i]][dots_traveled[i+1]];
			//cout<<grafo[dots_traveled[i]][dots_traveled[i+1]]<<",";
		}
	}
	cout<<"Path Size         : "<<dots_traveled.size()<<endl;
	cout<<"Execution Time(ms): " << (double(t1-t0)/CLOCKS_PER_SEC)*1000 << endl;
	cout<<"Cost              : "<<cost<<endl;
	if(dots_traveled[dots_traveled.size()-1]!=coord_fin)cout<<"META NO ACHIVED"<<endl;
}

void Algorithms()
{	
	cout<<"---------------------------------"<<endl;
	cout<<"Inicial node: "<< coord_ini<<endl;
	cout<<"Meta node   : "<< coord_fin<<endl;
	cout<<"----------------DFS--------------"<<endl;
    Clear();
    t0=clock();
    DFS();
    t1=clock();
    Path();
    DFS_Path=path;
    DFS_DT=dots_traveled;
	cout<<"----------------BFS--------------"<<endl;
   	Clear();
   	t0=clock();
    BFS();
    t1=clock();
    Path();
    BFS_Path=path;
    BFS_DT=dots_traveled;
    cout<<"----------------A*--------------"<<endl;
   	Clear();
   	t0=clock();
   	a_aterisk(grafo);
   	t1=clock();
   	Path();
   	AA_Path=path;
   	AA_DT=dots_traveled;
   	cout<<"-----------HillClimbing----------"<<endl;
   	Clear();
   	t0=clock();
   	hill_climbing(grafo);
   	t1=clock();
   	Path();
   	HC_Path=path;
   	HC_DT=dots_traveled;
}

void InitGLUT() 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(1000,1000);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("Shortest Path");
}
void PaintScene() 
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	
	//Edges
	glLineWidth(1.0); 
	glColor3f(0.1f,0.7f,1.0f);
	glBegin(GL_LINES);
	for(int i=0;i<edges.size();i++)
	{
		glVertex3f(edges[i].first.first, edges[i].first.second,0.0);	
		glVertex3f(edges[i].second.first, edges[i].second.second,0.0);	
	}
	glEnd();
	//Edges Path
	glLineWidth(1.0); 
	glColor3f(1.1f,0.7f,0.0f);
	glBegin(GL_LINES);
	for(int i=0;i<path.size();i++)
	{
		glVertex3f(path[i].first.first, path[i].first.second,0.0);	
		glVertex3f(path[i].second.first, path[i].second.second,0.0);	
	}
	glEnd();
	//Dots
   	glPointSize(10.5);
   	glBegin(GL_POINTS);
   	glColor3f(0.1f,0.5f,0.9f);
    for(int i =0; i<dots.size(); i++)
	{
		glVertex3f(dots[i].first,dots[i].second,0.0f); // sleep(1);
	}
   	glEnd();
   	//Dots Path
   	glPointSize(12.5);
   	glBegin(GL_POINTS);
  	glColor3f(0.7f,0.3f,1.0f);
    for(int i =0; i<dots_traveled.size(); i++)
	{
		glVertex3f(dots[dots_traveled[i]].first,dots[dots_traveled[i]].second,0.0f);             
    }
    glEnd();
	//Start(red)
	glPointSize(10.5);
	glBegin(GL_POINTS);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(start.first,start.second,0.0f);
	glEnd();
	//Meta
	glPointSize(12.5);
	glBegin(GL_POINTS);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(meta.first,meta.second,0.0f);
	glEnd();
   	glutSwapBuffers();
}   

void ReProyect(int w, int h) 
{
	width = w;
   	high = h;
   	GLfloat format;
  	if(h == 0) h = 1;
   	glViewport(-10, -10, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();

   	format = (GLfloat)w / (GLfloat)h;
   	if (w <= h)
		glOrtho (-10.0f*size, 10.0f*size, -10.0f*size / format, 10.0f*size / format, 1.0f, -1.0f);
   	else glOrtho (-10.0f*size * format, 10.0f*size * format, -10.0f*size, 10.0f*size, 1.0f, -1.0f);
   		glutDisplayFunc(PaintScene);
}

void Zoom(int value) 
{
	if (up) size = size * 1.2;//1.01f;
   	if (down) size = size / 1.2;//1.01f;
   	if (DFS_Key)
   	{
   	   	path=DFS_Path; 
   	   	dots_traveled=DFS_DT;
   	}
   	if (BFS_Key)
   	{
   	   	path=BFS_Path;
   	   	dots_traveled=BFS_DT;
   	}
   	if (AA_Key)  
   	{
   		path=AA_Path;
   		dots_traveled=AA_DT;
   	}
	if (HC_Key)  
	{
   		path=HC_Path;
   		dots_traveled=HC_DT;
   	}
    ReProyect(width,high);
    glutTimerFunc(33,Zoom,1);
    glutPostRedisplay();
}

void Rows(int key, int x, int y) 
{
	if (key==GLUT_KEY_UP) up = 1;
	if (key==GLUT_KEY_DOWN) down = 1;
}

void RowsUp(int key, int x, int y) 
{
	if (key==GLUT_KEY_UP) up = 0;
	if (key==GLUT_KEY_DOWN) down = 0;
}

void NormalKeyHandler (unsigned char key, int x, int y)
{
    if (key == 'd') DFS_Key = 1;
    if (key == 'b') BFS_Key = 1;
    if (key == 'a') AA_Key = 1;
    if (key == 'h') HC_Key = 1;
}

void NormalKeyHandlerUP (unsigned char key, int x, int y)
{
    if (key == 'd') DFS_Key = 0;
    if (key == 'b') BFS_Key = 0;
    if (key == 'a') AA_Key = 0;
    if (key == 'h') HC_Key = 0;
}

int main(int argc, char **argv)
{
    cout<<"Number of dots"<<endl;
    cin>>N_DOTS;
    cout<<endl<<"Complete graph? (y/n)"<<endl;
    char yn;
    cin>>yn;
    if(yn=='n')limit=N_DOTS*0.8;
    cout<<endl<<"Press key to algorithm path"<<endl;
    cout<<"d ---> DFS "<<endl; 
    cout<<"b ---> BFS "<<endl;
    cout<<"a ---> A* "<<endl;
    cout<<"h ---> Hill Climbing "<<endl;
    ///Random dots
    srand(time(NULL));
    for(int i=0; i<N_DOTS; ++i)
    {
        float auxx=rand()%N_DOTS-rand()%N_DOTS;
        float auxy=rand()%N_DOTS-rand()%N_DOTS;
		dots.push_back(make_pair(auxx,auxy));
    }
    coord_ini=0;
    coord_fin=rand()%N_DOTS;
    start = dots[coord_ini];
    meta = dots[coord_fin];
    
    Build_graph();
    Build_tree();
  	Algorithms();

    glutInit(&argc,argv); //just for Linux
    InitGLUT();
    glutReshapeFunc(ReProyect);
    glutDisplayFunc(PaintScene);
    glutTimerFunc(33,Zoom,1);
    glutSpecialFunc(Rows);
    glutSpecialUpFunc(RowsUp);
    glutKeyboardFunc(NormalKeyHandler);
    glutKeyboardUpFunc(NormalKeyHandlerUP);
    glutMainLoop();

    return 0;
}
