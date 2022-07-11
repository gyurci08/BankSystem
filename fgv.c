int dToNap(char *datum)
{
int i=0,osszeg=0, count, ev=0, honap=0, nap=0, poz=0;
sscanf(datum,"%d.%d.%d", &ev, &honap, &nap);
osszeg=ev*356+honap*31+nap;
return osszeg;
}

int kamattalNovelt(char *datum, float toke, float kamat)
{
int i, dszam=dToNap(datum), mdszam=dToNap(&maiDatum), kul=(mdszam-dszam)/356;
kamat=1+kamat/100;
 for (i = 1; i <= kul; i++)
    {
 toke =toke*kamat;
    }
return toke;
}

void penzugyek(ugyfelek *ugyfel)
{
    char nev[30];
    int novelt, nevId, leKb;
printf("\nUgyfel neve: ");
do
    {
    scanf("%s", nev);
    nevId=bennee(nev, ugyfel);
    if (nevId==-1) printf("Kerem probalja meg ujra: ");
    }
while (nevId==-1);


while(ugyfel)
    {
    if (nevId==ugyfel->azonosito) {novelt=kamattalNovelt(ugyfel->datum, ugyfel->nyEgy, ugyfel->kamat); printf("Lekotes ideje: %s\nEves kamat: %d\nNyito egyenleg: %d\nJelenlegi (kamattal novelt) egyenlege: %d\n", ugyfel->datum, ugyfel->kamat, ugyfel->nyEgy, novelt);}
    ugyfel=ugyfel->kovetkezo;
    }
}

int dvalid(char *maiDatum)
{
int i=0;
while (maiDatum[i]!=0) { if (((maiDatum[i]!='.')&&(maiDatum[i]<'0'))||((maiDatum[i]>'9')&&(maiDatum[i]!='.'))) {return -1;} i++;}
if (maiDatum[0]=='1') return -1;
if (maiDatum[4]!='.'||maiDatum[7]!='.'||maiDatum[10]!='.') return -1;
if ((maiDatum[5]=='1')||(maiDatum[5]=='0')) {} else return -1;
if (((maiDatum[5]=='1')&&((maiDatum[6]=='2')||(maiDatum[6]=='1')||(maiDatum[6]=='0')))||(maiDatum[5]=='0')) {} else return -1;
if (maiDatum[8]>'3') return -1;
if ((maiDatum[8]=='3')&&(maiDatum[9]>1)) return -1;
return 0;
}

void maximum(ugyfelek *ugyfel, int *maxId)
{
*maxId=ugyfel->azonosito;
 ugyfel=ugyfel->kovetkezo;
while (ugyfel)
{
if (*maxId<ugyfel->azonosito) {*maxId=ugyfel->azonosito;}
    ugyfel=ugyfel->kovetkezo;
}
}

int datum()
{
reset:
printf("Kerem az aktualis datumot: ");
scanf ("%s", maiDatum);
if (dvalid(&maiDatum)==0) return 0; else if (ujra()) {goto reset;} else {printf("A program kilep.\n"); return 1;}
}

void masol(char *ide, char *in)
{
    while (*(ide++)=*(in++));
}

int ugyfelhozzaad(ugyfelek **ugyfel, char *emailcim, char *telefon,char *neve, int nyitoEgy, int evesKamat)
{
ugyfelek *newugyfel; int maxId;
maximum(*ugyfel, &maxId);
if((!(newugyfel=malloc(sizeof(ugyfelek))))) {return 1;}
newugyfel->azonosito=maxId+1;
masol(newugyfel->nev,neve);
masol(newugyfel->tel,telefon);
masol(newugyfel->email,emailcim);
masol(newugyfel->datum,maiDatum);
newugyfel->nyEgy=nyitoEgy;
newugyfel->kamat=evesKamat;
newugyfel->kovetkezo=*ugyfel;
*ugyfel=newugyfel;
return 0;
}

int telvalid(char *tel)
{
int i=0;
while (tel[i]!=0)
    {
if (tel[i]<'0'||tel[i]>'9') {printf("Telefonszam ujra: ");return -1;}
i++;
    }
return 0;
}

int evalid(char *email)
{
int i, elemek=0, kukac=0,kukaci, pont=0,ponti, hiba=0;
while (email[elemek]!=0) {elemek++;}
if (email[elemek-1]=='@'||email[elemek-1]=='.') {hiba++;}
for (i=0;(i<elemek)&&(hiba==0);i++)
    {
        if (email[0]=='@'||email[0]=='.') {hiba++; return -1;}
        if (email[i]=='@') {kukac++;kukaci=i;}
        if (email[i]=='.') {pont++;ponti=i;}
    }
for (i=0;(i<elemek-1)&&(hiba==0);i++)
    {
    if ((email[i]=='.'||email[i]=='@')&&(email[i+1]=='.'||email[i+1]=='@')) {hiba++;return -1;}
    }
if (kukac!=1&&pont!=1) hiba++;
if (hiba==0) {return 0;} else { printf("A megfelelo formatum (asd@asd.as): ");return -1;}
}

void ujugyfel(ugyfelek *ugyfel)
{
char email[30], tel[30], nev[30]; int check, nyitoEgy, evesKamat;
printf("Email: "); check=-1; while (check==-1) {scanf ("%s", email); check = evalid(&email); }
printf("Telefonszam: "); check=-1; while (check==-1) {scanf ("%s", tel); check = telvalid(&tel); }
printf("Nev: "); scanf("%s", nev);
printf("Nyito egyenleg: "); scanf("%d", &nyitoEgy);
printf("Eves kamat: "); scanf("%d", &evesKamat);
ugyfelhozzaad(ugyfel,&email,&tel,&nev,nyitoEgy,evesKamat);
printf("Az uj ugyfel sikeresen hozzadva. ");
}

void tranzakcio(ugyfelek *ugyfel, int utId, int kedvId,int utalando)
{
    if (!ugyfel) {printf("A tranzakcio sikertelen. ");}
    else
    {
        while (ugyfel)
        {
if (ugyfel->azonosito==utId) {((ugyfel->nyEgy)=(ugyfel->nyEgy)-utalando);}
if (ugyfel->azonosito==kedvId) {((ugyfel->nyEgy)=(ugyfel->nyEgy)+utalando);}

    ugyfel=ugyfel->kovetkezo;
        }
        printf("A tranzakcio sikeres. ");
    }
}

int bennee(char *nev, ugyfelek *ugyfel)
{
char temp[30];
int i=0, j=0, beKertnevkar=0, megKaraktersz=0, id;
while (nev[beKertnevkar]!=0) { beKertnevkar++;}
while (ugyfel)
    {
megKaraktersz=0;
while (ugyfel->nev[megKaraktersz]!=0) { megKaraktersz++;}
if (megKaraktersz==beKertnevkar)
    {
        while (j<megKaraktersz) { if (ugyfel->nev[j]==nev[j]) {j++; id =ugyfel->azonosito;} else break;}
    }
if(j==beKertnevkar) {return id;}
ugyfel=ugyfel->kovetkezo;
    }
return -1;
}

int keret(ugyfelek *ugyfel, int utId)
{
int utKeret;
while(ugyfel) {if (utId==ugyfel->azonosito)  {utKeret=ugyfel->nyEgy;} ugyfel=ugyfel->kovetkezo;}
return utKeret;
}

int utalas(ugyfelek *ugyfel)
{
char utalo[20], kedvezmenyezett[20];
int utalando=0, utId, kedvId, utKeret;
printf("Utalo neve: ");
do {
scanf("%s", utalo);
utId=bennee(utalo, ugyfel);
if (utId==-1) printf("Kerem probalja meg ujra: ");
}
while (utId==-1);
printf("Kedvezmenyezett neve: ");
do {
scanf("%s", kedvezmenyezett);
kedvId=bennee(kedvezmenyezett, ugyfel);
if (kedvId==-1) printf("Kerem probalja meg ujra: ");
}
while (kedvId==-1);
utKeret=keret(ugyfel, utId);
reset:
printf("Utalando osszeg: ");
scanf("%d", &utalando);
if (utalando>0&&utalando<=utKeret) {tranzakcio(ugyfel,utId,kedvId,utalando); return 0;} else {printf("Az osszegnek nagyobbnak kell lennie nullanal, vagy kisebbnek az on egyenlegenel!\n");if (ujra()) {goto reset;} else {return 1;}}
}

int valaszto(int *valasztas)
{
reset:
printf("Kerem az elvegezendo muveletet (1-5): ");
scanf("%d", &(*valasztas));
if (0<(*valasztas)&&(*valasztas)<6) return 0; else if (ujra()) {goto reset;} else {printf("A program kilep.\n"); return 1;}
return 0;
}

void onStart()
{
int valasztas=0;
printf("\n1: UGYFELLISTA\t");
printf("2: UTALAS\t");
printf("3: UJ UGYFEL\t");
printf("4: KIVALASZTOTT UGYFEL\t");
printf("5: KILEPES\t\n");
}

void ugyfelekKi(ugyfelek *ugyfel)
{
if(!ugyfel) {printf("Nem talalhato ugyfel a rendszerben.\n");}
else
{
printf("\nAz adatbazisban szereplo ugyfelek:\n");
printf("NEV\t\tEMAIL\t\tTELEFONSZAM\tNYITO EGYENLEG\tLEKOTES DATUMA\tEVES KAMAT\n");
while(ugyfel)
{
printf("%-16s%-20s%-16s%-16d%-16s%-16d\n", ugyfel->nev,ugyfel->email, ugyfel->tel, ugyfel->nyEgy, ugyfel->datum, ugyfel->kamat);
ugyfel=ugyfel->kovetkezo;
}
}
}


felTolt(ugyfelek **ugyfel, FILE **lista)
{
ugyfelek *ujUgyfel;
if((!(ujUgyfel=malloc(sizeof(ugyfelek)))))
    {
        return 1;
    }
fscanf(*lista, "%d", &ujUgyfel->azonosito);
fscanf(*lista, "%s", ujUgyfel->nev);
fscanf(*lista, "%s", ujUgyfel->email);
fscanf(*lista, "%s", ujUgyfel->tel);
fscanf(*lista, "%d", &ujUgyfel->nyEgy);
fscanf(*lista, "%s", ujUgyfel->datum);
fscanf(*lista, "%d", &ujUgyfel->kamat);
ujUgyfel->kovetkezo=*ugyfel;
*ugyfel=ujUgyfel;
return 0;
}

int fajlBe(ugyfelek **ugyfel, char *fajlNev)
{
reset:
printf("A beolvasando allomany neve: ");
scanf("%s", fajlNev);
char ch;
int i=0, elemek=0;
FILE *lista=fopen(fajlNev, "r");
if (lista==NULL) {printf("A fajlbeolvasas sikertelen.\n");if (ujra()) {goto reset;} else {printf("A program kilep.\n"); return 1;} }
while ((ch=fgetc(lista))!=EOF) {if (ch=='\n') {elemek++;}}
rewind(lista);
for (i=0; i<elemek;i++)
{
if (felTolt(ugyfel, &lista)) {printf("Nem elegendo a memoria.\n"); if (ujra()) {goto reset;} else {printf("A program kilep.\n"); return 1;}}
}
fclose(lista); printf("Sikeres beolvasas...\n");
return 0;
}



int ujra()
{
    char ujra;
    printf("Megint megprobalja? (i/n): ");
    fflush(stdin);
    scanf(" %c", &ujra);
    if (ujra=='i') return 1; else return 0;
}

void kilepes(ugyfelek *ugyfel, char *fajlNev)
{
char ch, valasztas;
ugyfelek *torlendo;
printf("Lehetseges hogy tortentek valtozasok. Kivanja menteni oket? (i/n): ");
scanf(" %c", &valasztas);
if (valasztas=='i')
{
FILE *lista=fopen(fajlNev, "w");
while (ugyfel)
{
fprintf(lista, "%-8d%-16s%-20s%-16s%-16d%-16s%d\n", ugyfel->azonosito,ugyfel->nev,ugyfel->email, ugyfel->tel, ugyfel->nyEgy, ugyfel->datum, ugyfel->kamat);

torlendo=ugyfel;
ugyfel=ugyfel->kovetkezo;
free(torlendo);
}
fflush(lista);
fclose(lista); printf("Sikeres mentes...");
}
else {
        while (ugyfel) {torlendo=ugyfel; ugyfel=ugyfel->kovetkezo; free(torlendo);}
        printf("Viszlat! "); }
}

