#include <stdio.h>
#include "fgv.h"
#include "fgv.c"

int main()
{

ugyfelek *ugyfel=NULL; char fajlNev[30];
int ujra, valasztas=0;

if (fajlBe(&ugyfel, fajlNev)) return 0;
if (datum()) return 0;
reset:
onStart();
if (valaszto(&valasztas)) return 0;
switch(valasztas)
{
case 1: {ugyfelekKi(ugyfel);goto reset;}
case 2: {if(utalas(ugyfel)) goto reset; goto reset;}
case 3: { ujugyfel(&ugyfel);goto reset;}
case 4: { penzugyek(ugyfel);goto reset;}
case 5: {kilepes(ugyfel, fajlNev);}
}


    return 0;
}
