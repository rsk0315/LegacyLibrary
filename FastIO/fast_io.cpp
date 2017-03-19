class FastIO {
    static const size_t E=1<<17;
    static char*t,*a,e[E|1],*i,*n,o[E|1];
    static void p(){fwrite(o,1,i-o,stdout),i=o;}
    static void b(){e[fread(e,1,E,stdin)]=0,t=e;}
    static void b(size_t h){e[h+fread(e+h,1,E-h,stdin)]=0;}
public:
    static void scan(double&h){char*r;h=strtod(t,&r);if(r<a&&r-t){t=r;return;}ptrdiff_t d=a-t;memcpy(e,t,d),b(d),h=strtod(e,&t);}
    static void scan(char&h){h=*t++;if(h)return;b(),h=*t++;}
    static void scan(char*h){char*l=t,*c=l;bool u=0;for(;;++l){char r=*l;if(!r){ptrdiff_t m=l-c;memcpy(h,c,m),h+=m,b(),l=c=e,r=*e;}if(r-' '&&r-'\n'){if(!u)u=1,c=l;}else if(u){memcpy(h,c,l-c),h[l-c]=0,t=++l;return;}}}
    template<class T>
    static void scan(T&h){bool u=0,w=0;h=0;for(;;){char r=*t++;if(!r)b(),r=*t++;if(r>='0'&&r<='9')u=1,h=h*10+r-'0';else if(u){++r;break;}else if(std::is_signed<T>::value&&r=='-')w=1;}if(std::is_signed<T>::value&&w)h=-h;}
    template<class T,class...A>
    static void scan(T&h,A&...f){scan(h),scan(f...);}
    static void print(double h){char g[20];size_t m=snprintf(g,sizeof g,"%.12f",h);char*r=i+m;if(r>=n)p(),r=o+m;memcpy(i,g,m),i=r;}
    static void print(char h){if(i+1>=n)p();*i++=h;}
    static void print(const char*h){size_t m=strlen(h);char*r=i+m;if(r>=n)p(),r=o+m;memcpy(i,h,m),i=r;}
    static void print(char*h){size_t m=strlen(h);char*r=i+m;if(r>=n)p(),r=o+m;memcpy(i,h,m),i=r;}
    template<size_t N>
    static void print(const char(&h)[N]){size_t m=strlen(h);char*r=i+m;if(r>=n)p(),r=o+m;memcpy(i,h,m),i=r;}
    template<class T>
    static void print(T h){if(i+20>=n)p();if(!h){*i++='0';return;}char g[20],*l=g+20,*y=l;if(std::is_signed<T>::value&&h<0)*i++='-',h=-h;while(h)*--l=h%10+'0',h/=10;memcpy(i,l,y-l),i+=y-l;}
    template<class T,class...A>
    static void print(T h,A&&...f){print(h),print(f...);}
    template<class T>
    static void println(T h){print(h,'\n');}
    template<class T,class...A>
    static void println(T h,A&&...f){print(h,' '),println(f...);}
    template<class T>
    static void printlns(T h){print(h,'\n');}
    template<class T,class...A>
    static void printlns(T h,A&&...f){print(h,'\n'),printlns(f...);}
    static void flush(){fwrite(o,1,i-o,stdout),fflush(stdout),i=o;}
};
char FastIO::e[],*FastIO::t=e,*FastIO::a=e+E,FastIO::o[],*FastIO::i=o,*FastIO::n=o+E;
