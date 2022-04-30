#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Tunay Basturk 190201032  Umut Kilic 190201028
struct Cember_ust
{

    float x;
    float y;

};

struct Girilen_noktalar
{
    float x;
    float y;

};



struct tutucu {
float x;
float y;
};


/*void init(){

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(0,50,0,50,0,10);
}*/ //Önceden kalan kod


float MerkezCemberX(struct Cember_ust Koordinatlar[])
{



    float x1 = (Koordinatlar[1].x+Koordinatlar[0].x)/2.0;
    float y1 = (Koordinatlar[1].y+Koordinatlar[0].y)/2.0;
    float dy1 = Koordinatlar[1].x-Koordinatlar[0].x;
    float dx1 = -(Koordinatlar[1].y-Koordinatlar[0].y);


    float x2 = (Koordinatlar[2].x+Koordinatlar[1].x)/2.0;
    float y2 = (Koordinatlar[2].y+Koordinatlar[1].y)/2.0;
    float dy2 = Koordinatlar[2].x-Koordinatlar[1].x;
    float dx2 = -(Koordinatlar[2].y-Koordinatlar[1].y);


    float cx = (y1*dx1*dx2+x2*dx1*dy2-x1*dy1*dx2-y2*dx1*dx2)/(dx1*dy2-dy1*dx2);
    float cy = (cx-x1)*dy1/dx1+y1;



    return cx;

}


float MerkezCemberY(struct Cember_ust Koordinatlar[])
{



    float x1 = (Koordinatlar[1].x+Koordinatlar[0].x)/2.0;
    float y1 = (Koordinatlar[1].y+Koordinatlar[0].y)/2.0;
    float dy1 = Koordinatlar[1].x-Koordinatlar[0].x;
    float dx1 = -(Koordinatlar[1].y-Koordinatlar[0].y);


    float x2 = (Koordinatlar[2].x+Koordinatlar[1].x)/2.0;
    float y2 = (Koordinatlar[2].y+Koordinatlar[1].y)/2.0;
    float dy2 = Koordinatlar[2].x-Koordinatlar[1].x;
    float dx2 = -(Koordinatlar[2].y-Koordinatlar[1].y);


    float cx = (y1*dx1*dx2+x2*dx1*dy2-x1*dy1*dx2-y2*dx1*dx2)/(dx1*dy2-dy1*dx2);
    float cy = (cx-x1)*dy1/dx1+y1;

    return cy;

}


void display(){
   glClearColor(1,1,1,1);
   glClear(GL_COLOR_BUFFER_BIT);

   // glLoadIdentity(); Önceden kalan kod
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-21,21,-21,21);
    glMatrixMode(GL_MODELVIEW);
    int i;
    int j=9;
    double x,y,c;
    struct tutucu gecici[4];
    int n,k,kontrol=0;
    float x1,x2,y1,y2,yaricap;
    float Enuzak2nokta[4];
    float uzaklik,temp=0,Mx,My;
    FILE *dosya =fopen("D:\\Giris.txt","r");
    int q=0;
    float okunan_x;
    float okunan_y;

    float t;
 struct Girilen_noktalar Giris[1000];
    for(int j=0;!feof(dosya);j++){
    fscanf(dosya,"%f %f",&okunan_x,&okunan_y);
   Giris[j].x=okunan_x;
   Giris[j].y=okunan_y;
        q++;
        }
    int m=q;


    for(q=0;q<m;q++){;
        printf("%d. nokta = %.2f,%.2f\n",q+1,Giris[q].x,Giris[q].y);
    }
    fclose(dosya);



//CEMBER ALGORITMASI
    struct Cember_ust Koordinatlar[m];
  float Enuzak2_noktanin_merkezinin_diger_noktalara_uzakligi[m];

if(m>1){
for(int i=0; i<m; i++)
{
    for(int k=i+1; k<m; k++)
    {
        uzaklik=sqrt(pow((Giris[i].x-Giris[k].x),2)+pow((Giris[i].y-Giris[k].y),2));

        x1=Giris[i].x;
        x2=Giris[k].x;
        y1=Giris[i].y;
        y2=Giris[k].y;

        if(uzaklik>temp)
        {
            temp=uzaklik;
            Enuzak2nokta[0]=x1;
            Enuzak2nokta[1]=y1;
            Enuzak2nokta[2]=x2;
            Enuzak2nokta[3]=y2;

        }
    }
}

}


Koordinatlar[0].x=Enuzak2nokta[0];
Koordinatlar[0].y=Enuzak2nokta[1];
Koordinatlar[1].x=Enuzak2nokta[2];
Koordinatlar[1].y=Enuzak2nokta[3];



Mx=(Enuzak2nokta[0]+Enuzak2nokta[2])/2.0;
My=(Enuzak2nokta[1]+Enuzak2nokta[3])/2.0;


float Merkezin_uzak_2_noktaya_uzakligi=sqrt(pow((Mx-Enuzak2nokta[0]),2)+pow((My-Enuzak2nokta[1]),2));
float yeninokta[2];
for(int i=0; i<m; i++)
{

        Enuzak2_noktanin_merkezinin_diger_noktalara_uzakligi[i]=sqrt(pow((Mx-Giris[i].x),2)+pow((My-Giris[i].y),2));
        if(Enuzak2_noktanin_merkezinin_diger_noktalara_uzakligi[i]>Merkezin_uzak_2_noktaya_uzakligi)
        {
            Merkezin_uzak_2_noktaya_uzakligi=Enuzak2_noktanin_merkezinin_diger_noktalara_uzakligi[i];
            yeninokta[0]=Giris[i].x;
            yeninokta[1]=Giris[i].y;
            kontrol++;
        }




}
if(m>1){
if(kontrol!=0)
{
    Koordinatlar[2].x=yeninokta[0];
    Koordinatlar[2].y=yeninokta[1];
    Mx=MerkezCemberX(Koordinatlar);
    My=MerkezCemberY(Koordinatlar);
    yaricap=sqrt(pow((Mx-Koordinatlar[0].x),2)+pow((My-Koordinatlar[0].y),2));
    printf("Cember Merkez= %f %f\n",Mx,My);
    printf("Cember Yaricap = %f\n",yaricap);

}
else if(kontrol==0)
{
    yaricap=sqrt(pow((Mx-Koordinatlar[0].x),2)+pow((My-Koordinatlar[0].y),2));
    printf("Cember Merkez= %f %f\n",Mx,My);
    printf("Cember Yaricap = %f\n",yaricap);


}

}

 char numaralar[34]="1234567891011121314151617181920";
 numaralar[32]='\0';


 for(i=0;i<31;i++){

    if(i>8){

    glRasterPos2f(0,(i)+0.85);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j]);

    glRasterPos2f(0.3,(i)+0.85);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j+1]);

    glRasterPos2f((i)+0.75,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j]);

    glRasterPos2f((i)+1.05,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j+1]);

         glRasterPos2f(-(i)-0.94,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j+1]);

    glRasterPos2f(-(i)-1.25,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j]);

    if(i<20){
    glRasterPos2f(-(i)-1.7,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'-');
    }

    if(i<20){
    glRasterPos2f(0,(-i)-1.118);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'-');
    }

    glRasterPos2f(0.5,(-i)+-1.25);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j]);

    glRasterPos2f(0.8,(-i)-1.25);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[j+1]);


    j+=2;
    }
    else{
    glColor3f(0,0,0);
    glRasterPos2f(0,(i)+0.75);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[i]);
    glRasterPos2f((i)+0.75,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[i]);
    glRasterPos2f((-i)-1.25,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[i]);
    glRasterPos2f((-i)-1.75,0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'-');
    glRasterPos2f(0,(-i)-1.25);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'-');
    glRasterPos2f(0.5,(-i)-1.25);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,numaralar[i]);


    }




}

  //KOORDINAT SISTEMI
    glPointSize(3.0);
    //glLoadIdentity();Önceden kalan kod
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(45,0);
    glVertex2f(-45,0);
    glVertex2f(0,45);
    glVertex2f(0,-45);
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    //glVertex2f(x,y); Önceden kalan kod
    for(i=-40;i<41;i++){
    glColor3f(0,0,1);

    glVertex2f(i,0);
    }
    for(i=-40;i<41;i++){
    glColor3f(0,0,1);

    glVertex2f(0,i);
    }
    glEnd();


    glColor3f(1,0,1);
    glPointSize(6.0);
    glBegin(GL_POINTS);

    glVertex2f(Mx,My);
    glEnd();
    glColor3f(0,1,0);
    glLineWidth(3.0);
    glBegin(GL_LINES);

    glVertex2f(Mx,My);
    glVertex2f(Mx+(yaricap),My);
    glEnd();
//CEMBER CIZIMI
     glColor3f(1,1,1);
      glPointSize(3.0);
    glBegin(GL_POINTS);
    for(c = 0.5; c < 360; c+=0.5){
      glColor3f(1,0,0);
      glPointSize(3.0);
      x = yaricap * sin(((double)c));
      y = yaricap * cos(((double)c));
      glVertex2f(x+Mx,y+My);
    }


    glEnd();

//B-SPLINE

gecici[0].x=0;
gecici[0].y=0;
gecici[1].x=Giris[0].x;
gecici[1].y=Giris[0].y;
gecici[2].x=Giris[1].x;
gecici[2].y=Giris[1].y;
gecici[3].x=Giris[2].x;
gecici[3].y=Giris[2].y;
 float splinex;
 float spliney;

glColor3f(1,0.7,0);
glPointSize(3);

//int a=0; Önceden kalan kod


        for(i=3;i<m;i++){
//gecici[0].x=gecici[1].x;
//gecici[0].y=gecici[1].y;
gecici[1].x=gecici[2].x;
gecici[1].y=gecici[2].y;
gecici[2].x=gecici[3].x;
gecici[2].y=gecici[3].y;
gecici[3].x=Giris[i].x;
gecici[3].y=Giris[i].y;


        for(t=0;t<1;t=t+0.001){


   splinex=( (pow((1-t),3)*gecici[0].x)+ ((3*pow(t,3)-(6*(pow(t,2)))+4)*gecici[1].x) -  (((3*pow(t,3))-(3*pow(t,2))-(3*t)-1)*gecici[2].x) + (pow(t,3)*gecici[3].x))/6.0;
   spliney=( (pow((1-t),3)*gecici[0].y)+ ((3*pow(t,3)-(6*(pow(t,2)))+4)*gecici[1].y) -  (((3*pow(t,3))-(3*pow(t,2))-(3*t)-1)*gecici[2].y) + (pow(t,3)*gecici[3].y))/6.0;
//B SPLÝNE CÝZÝMÝ
glBegin(GL_POINTS);

glVertex2f(splinex,spliney);


glEnd();
//a++;Önceden kalan kod
        }
}


 glColor3f(0,0,0);
       glPointSize(7);
        glBegin(GL_POINTS);
       for(int i=0;i<m;i++){
       glVertex2f(Giris[i].x,Giris[i].y);
       }
       glEnd();

glFlush();

}

int main(int argc,char**argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(500,100);
    glutInitWindowSize(900,800);
    glutCreateWindow("ProLAB1");
    glutDisplayFunc(display);
//    init();  Önceden kalan kod
    glutMainLoop();

}







