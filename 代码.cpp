#include <iostream>
#include<cstdio>
#include<string.h>
#include<queue>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define N 100
struct product{
	double weight[51];
	double values;
}a[51]; 
double bestn=0;
bool x[101];
int n,num;
double  C[50];//��Ʒ����,��Ʒ����, ��ǰ����,��������
struct Product{
	double cp,rp;//��ǰ��ֵ ʣ���ֵ 
	double rw[51];//ʣ������ 
	int id;
	bool x[51];//��� 
	Product(){memset(x,0,sizeof(x));}
	Product(double _cp,double _rp,double _rw[],int _id){
		cp=_cp;
		rp=_rp;
		for(int i=1;i<=num;++i)
			rw[i]=_rw[i];
		id=_id;
	}
};
bool check(double s[])
{
	for(int i=1;i<=num;++i)
		if(s[i]) return false;
	return true;
}
double bfs(double sumw[],double sumv)
{
	Product newp,lhd,rhd;
	double ccp,crp,crw[51];
	int c,i;
	queue<Product> q;
	q.push(Product(0,sumv,C,1));
	while(!q.empty()){
		newp=q.front();
		q.pop();
		c=newp.id;
		if(c>n||check(newp.rw)){
			if(newp.cp>=bestn){
				for( i=1;i<=n;++i)
					x[i]=newp.x[i];
				bestn=newp.cp;
			}
			continue;
		}
		
	
	if(newp.cp+newp.rp<bestn)//��֦����
		continue;
	ccp=newp.cp;
	crp=newp.rp-a[c].values;
	for(int i=1;i<=num;++i)
		crw[i]=newp.rw[i];
	int flag=0;
	for( i=1;i<=num;++i){
		if(crw[i]<a[i].weight[c]){
			flag=1;
			break;
		}
	}
	if(!flag){
		for( i=1;i<=num;++i)
			lhd.rw[i]=crw[i]-a[i].weight[c];
		lhd.cp=ccp+a[c].values;
		lhd=Product(lhd.cp,crp,lhd.rw,c+1);
		for( i=1;i<c;++i)
			lhd.x[i]=newp.x[i];
		lhd.x[c]=true;
		if(lhd.cp>bestn)
			bestn=lhd.cp;
		q.push(lhd);
	}
	if(ccp+crp>=bestn){
		rhd=Product(ccp,crp,crw,c+1);
		for(i=1;i<c;++i)
			rhd.x[i]=newp.x[i];
		rhd.x[c]=false;
		q.push(rhd);

	}
}
	return bestn;
}
int main()
{
	int i,k,j;
	scanf("%d %d %lf" , &n ,&num,&a);//��Ʒ����  
	for ( i = 1; i <=n; i++) {
		scanf("%lf", &a[i].values);//������Ʒ����  
	}
	for ( k = 1; k <=num; k++) {
		for ( j = 1; j <= n; j++) {
			scanf("%lf", &a[k].weight[j]);//������Ʒ��ֵ
		}
	}
	for ( i = 1; i <= num; i++) {
		scanf( "%lf", &C[i]);//������Ʒ������	
	}	
	double sumw[51];
	memset(sumw,0,sizeof(0));
	double sumv=0;
	for( i=1;i<=n;++i){
		sumv+=a[i].values;
		for( j=1;j<=num;++j)
		sumw[i]+=a[i].weight[j];
	}
	bfs(sumw,sumv);
	printf("��֧�޽編���0/1��������:\nX=[");
	for ( i = 1; i <= n; i++)
		cout << x[i]  <<"  ";//�������X[n]����
	printf("]   װ���ܼ�ֵ%lf\n", bestn);	
	return 0;
}

