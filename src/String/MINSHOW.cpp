string getmin(string s){
	int len=s.size();
	s+=s;
	s=" "+s;
	int i=1,j=2;//i,j表示以其位置开头的循环串
	while(j<=len){
		int k=0;//时间复杂度线性
		while(k<len&&s[i+k]==s[j+k])k++;
		if(s[i+k]>s[j+k]){
			i+=k+1;
		}
		else j+=k+1;
		if(i==j)j++;
		if(i>j)swap(i,j);
	}
    //最终字典序最小的是以i开头的
	return s.substr(i,len);
}