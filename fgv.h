#ifndef FGV_H_INCLUDED
#define FGV_H_INCLUDED

char maiDatum[30];

typedef struct ugyfelek
{
int azonosito;
char nev[30];
char email[30];
char tel[30];
int nyEgy;
char datum[30];
int kamat;
struct ugyfelek *kovetkezo;

}ugyfelek;


int dToNap(char *datum);
int kamattalNovelt(char *datum, float toke, float kamat);
void penzugyek(ugyfelek *ugyfel);
int dvalid(char *maiDatum);
void maximum(ugyfelek *ugyfel, int *maxId);
int datum();
void masol(char *ide, char *in);
int ugyfelhozzaad(ugyfelek **ugyfel, char *emailcim, char *telefon,char *neve, int nyitoEgy, int evesKamat);
int telvalid(char *tel);
int evalid(char *email);
int evalid(char *email);
void tranzakcio(ugyfelek *ugyfel, int utId, int kedvId,int utalando);
int bennee(char *nev, ugyfelek *ugyfel);
int keret(ugyfelek *ugyfel, int utId);
int utalas(ugyfelek *ugyfel);
int valaszto(int *valasztas);
void onStart();
void ugyfelekKi(ugyfelek *ugyfel);
felTolt(ugyfelek **ugyfel, FILE **lista);
int fajlBe(ugyfelek **ugyfel, char *fajlNev);
int ujra();
void kilepes(ugyfelek *ugyfel, char *fajlNev);



#endif // FGV_H_INCLUDED
