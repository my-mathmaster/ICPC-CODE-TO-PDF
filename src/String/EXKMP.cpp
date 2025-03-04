vector<int> exkmp(string s){
	int len=s.size();
	s=" "+s;
	vector<int>z(len+1);
	
	z[1]=0;
	int l=1,r=0;
	for(int i=2;i<=len;i++){
		if(i>r)z[i]=0;
		else {//利用之前的信息
			int k=i-l+1;
			z[i]=min(z[k],r-i+1);
		}
		while(i+z[i]<=len&&s[z[i]+1]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r){
			l=i;r=i+z[i]-1;
		}
	}
	return z;
}