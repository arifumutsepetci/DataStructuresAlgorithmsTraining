#include<stdio.h>
#include<string.h>
#include<math.h>
#define M 8
const double eps=1e-8;
const double inf=10e12;
const double Pi=acos(-1);
typedef struct talPoint{
	double x,y;
	talPoint(){}
	talPoint(double x,double y)
	{
		this->x=x;this->y=y;
	}
}Point;
typedef struct{
	Point p;
	double v;
	double dir;
}Guest;
Guest g[M],f[M];
Guest o;
bool mark[M];
double anst;
int stk[M],top;
int n;
double Max(double a,double b)
{
	return a>b?a:b;
}
double Dis(Point p,Point q)
{
	p.x-=q.x,p.y-=q.y;
	return sqrt(p.x*p.x+p.y*p.y);
}
double Dis(Point p)
{
	return sqrt(p.x*p.x+p.y*p.y);
}

void CallWork()
{
	int i;
	Point next;
	double tmpt,curt;
	double t1,t2;
	double a,b,c,cosa,d;
	Point e,h;
	tmpt=0;curt=0;
	o.p.x=o.p.y=0.0;
	memmove(g,f,sizeof(f));
	for(i=0;i<top;i++){
		g[stk[i]].p.x+=curt*g[stk[i]].v*cos(g[stk[i]].dir);
		g[stk[i]].p.y+=curt*g[stk[i]].v*sin(g[stk[i]].dir);
		h.x=g[stk[i]].v*cos(g[stk[i]].dir);
		h.y=g[stk[i]].v*sin(g[stk[i]].dir);
		e.x=g[stk[i]].p.x-o.p.x;
		e.y=g[stk[i]].p.y-o.p.y;
		cosa=(e.x*h.x+e.y*h.y)/(g[stk[i]].v*Dis(e));
		d=Dis(e);
		a=(o.v*o.v-g[stk[i]].v*g[stk[i]].v);
		b=2*g[stk[i]].v*d*cosa;
		c=d*d;
		t1=(b+sqrt(b*b+4*a*c))/(2*a);
		next.x=g[stk[i]].v*t1*cos(g[stk[i]].dir)+g[stk[i]].p.x;
		next.y=g[stk[i]].v*t1*sin(g[stk[i]].dir)+g[stk[i]].p.y;
		t2=Dis(next)/g[stk[i]].v;
		curt+=t1;
		o.p=next;
		if(curt+t2>anst) return;
		tmpt=Max(curt+t2,tmpt);
		double deneme = curt + t2;
	}
	if(tmpt<anst) anst=tmpt;
}
void Dfs()
{
	int i;
	if(top==n){
		CallWork();
		return;
	}
	for(i=0;i<n;i++){
		if(mark[i]) continue;
		mark[i]=true;
		stk[top++]=i;
		Dfs();top--;
		mark[i]=false;
	}
}
int main()
{
	int i;
	while(scanf("%d",&n),n){
		scanf("%lf",&o.v);
		for(i=0;i<n;i++){
			scanf("%lf%lf%lf%lf",&f[i].p.x,
				&f[i].p.y,&f[i].v,&f[i].dir);
		}
		anst=inf;top=0;
		Dfs();
		printf("%.0f\n",anst);
	}
	return 0;
}
