#include <unistd.h>
/* A small implementation found somewhere on the internet */
char m[9999],*n[99],*r=m,*p=m+5000,**s=n,d,c;main(){for(read(0,r,4000);c=*r;
r++)c-']'||(d>1||(r=*p?*s:(--s,r)),!d||d--),c-'['||d++||(*++s=r),d||(*p+=c==
'+',*p-=c=='-',p+=c=='>',p-=c=='<',c-'.'||write(2,p,1),c-','||read(2,p,1));}
