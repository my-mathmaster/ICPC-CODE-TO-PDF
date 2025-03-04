struct KMP
{
    vector<int> nxt;
    string tt;
    int len;
    KMP() {}
    KMP(string t)
    {
        len = t.size();
        t = " " + t;
        tt = t;
        nxt.resize(len + 1);
        nxt[1] = nxt[0] = 0;
        init(tt);
    }

    void init(string t)
    {
        for (int i = 2; i <= len; i++)
        {
            nxt[i] = nxt[i - 1];
            while (nxt[i] && t[i] != t[nxt[i] + 1])nxt[i] = nxt[nxt[i]];
            nxt[i] += (t[i] == t[nxt[i] + 1]);
        }
    }
    vector<int> getnxt()
    {
        return nxt;
    }
    vector<int> match(string &s, bool oneonly = 0)
    {
        int lens = s.size();
        s = " " + s;
        vector<int> stpos;
        int j = 0;
        for (int i = 1; i <= lens; i++)
        {
            while (j == len || (j && s[i] != tt[j + 1])) j = nxt[j];
            if (s[i] == tt[j + 1])j++;
            if (j == len)stpos.push_back(i - len + 1);
        }
        return stpos;
    }
};