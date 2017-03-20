#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <numeric>

class FastIO {
    static const size_t E=1<<17;
    static constexpr char T[]="%.16f";
    static const size_t A=20, O=330;
    static char*t,e[E|1],*a,o[E|1],*i,*n;
    static void s(){fwrite(o,1,i-o,stdout);i=o;}
    static void h(){e[fread(e,1,E,stdin)]=0;t=e;}
    static void h(size_t r){e[r+fread(e+r,1,E-r,stdin)]=0;}
public:
    static void scan(double&r){if(!*t)h();char*d;r=strtod(t,&d);if(d<a&&d-t){t=d;return;}ptrdiff_t l=a-t;memcpy(e,t,l);h(l);r=strtod(e,&t);}
    static void scan(char&r){r=*t++;if(r)return;h();r=*t++;}
    static void scan(char*r){char*d=t,*l=d;bool c=0;for(;;++d){char u=*d;if(!u){ptrdiff_t m=d-l;memcpy(r,l,m);r+=m;h();d=l=e;u=*e;}if(u-32&&u-10){if(!c)c=1,l=d;}else if(c){memcpy(r,l,d-l);r[d-l]=0;t=++d;return;}}}
    template<class I>
    static void scan(I&r,typename std::enable_if<std::is_signed<I>::value>::type*_=0){bool d=0,l=0;r=0;for(;;){char c=*t++;if(!c)h(),c=*t++;if(c>47&&c<58)d=1,r=r*10+c-48;else if(d){++c;break;}else if(c==45)l=1;}if(l)r=-r;}
    template<class I>
    static void scan(I&r,typename std::enable_if<!std::is_signed<I>::value>::type*_=0){bool d=0;r=0;for(;;){char l=*t++;if(!l)h(),l=*t++;if(l>47&&l<58)d=1,r=r*10+l-48;else if(d){++l;break;}}}
    template<class I,class...N>
    static void scan(I&&r,N&&...d){scan(r);scan(d...);}
    static void scanln(char*r){char*d=t,*l=d;bool c=false;for(;;++d){char u=*d;if(!u){ptrdiff_t m=d-l;memcpy(r,l,m);r+=m;h();d=l=e;u=*e;}if(u-10){if(!c)c=1,l=d;}else if(c){memcpy(r,l,d-l);r[d-l]=0;t=++d;return;}}}
    static void eat_space(){for(;;++t){if(!*t)h();if(*t-32&&*t-10)return;}}
    static void print(double r){char d[O];size_t l=snprintf(d,sizeof d,T,r);char*c=i+l;if(c>=n)s(),c=o+l;memcpy(i,d,l);i=c;}
    static void print(char r){if(i+1>=n)s();*i++=r;}
    static void print(const char*r){size_t d=strlen(r);char*l=i+d;if(l>=n)s(),l=o+d;memcpy(i,r,d);i=l;}
    static void print(char*r){size_t d=strlen(r);char*l=i+d;if(l>=n)s(),l=o+d;memcpy(i,r,d);i=l;}
    template<size_t I>
    static void print(const char(&r)[I]){size_t d=strlen(r);char*l=i+d;if(l>=n)s(),l=o+d;memcpy(i,r,d);i=l;}
    template<class I>
    static void print(I r,typename std::enable_if<std::is_signed<I>::value>::type*_=0){if (i+A>=n)s();if(!r){*i++=48;return;}char d[A],*l=d+A,*c=l;if(r<0)*i++=45,r=-r;while(r)*--l=r%10+48,r/=10;memcpy(i,l,c-l);i+=c-l;}
    template<class I>
    static void print(I r,typename std::enable_if<!std::is_signed<I>::value>::type*_=0){if(i+A>=n)s();if(!r){*i++=48;return;}char d[A],*l=d+A,*c=l;while(r)*--l=r%10+48,r/=10;memcpy(i,l,c-l);i+=c-l;}
    template<class I,class...N>
    static void print(I r,N&&...d){print(r);print(d...);}
    template<class I>
    static void println(I r){print(r,'\n');}
    template<class I,class...N>
    static void println(I r,N&&...d){print(r,' ');println(d...);}
    template<class I>
    static void printlns(I r){print(r,'\n');}
    template<class I, class...N>
    static void printlns(I r,N&&...d){print(r,'\n');printlns(d...);}
    static void flush(){fwrite(o,1,i-o,stdout);fflush(stdout);i=o;}
};

char FastIO::e[],*FastIO::t=e,*FastIO::a=e+E,FastIO::o[],*FastIO::i=o,*FastIO::n=o+E;
constexpr char FastIO::T[];
