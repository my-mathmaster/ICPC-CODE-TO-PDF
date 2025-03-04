int id(int x,int y,int m){
	//m列
	return m*(x-1)+y;
}
pii rid(int u,int m){
	int x=(u+m-1)/m;//m列
	int y=u%m;if(y==0)y+=m;
	return make_pair(x,y);
}
