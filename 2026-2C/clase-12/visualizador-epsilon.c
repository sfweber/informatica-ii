/*
 * visualizador-epsilon.c  —  El plano float: puntos que se espacian solos
 * Cátedra Informática II — Ing. Weber Federico
 *
 * Cada punto de la pantalla es una posición (x, y) donde AMBAS coordenadas
 * son floats representables. La ventana mide SIEMPRE 8.0 x 8.0 unidades,
 * con su esquina inferior-izquierda en (D, D). Cerca del origen el plano
 * parece continuo (mil millones de posiciones por eje); al alejarse, la
 * grilla se abre sola: en D = 2^24 quedan 5x5 posiciones. El punto rojo
 * es una posición (x, y) de floats: con las FLECHAS salta al float
 * vecino (siempre se mueve; el tamaño del salto lo impone la grilla) y
 * con [m] se ejecuta  x = x + 0.1f;  que lejos del origen no hace nada.
 * En D = 2^27 queda UNA posición en toda la ventana.
 * Es el mismo fenómeno de FLT_EPSILON/ULP, visto como mapa de juego.
 *
 * COMPILAR:
 *   gcc -O2 -std=c11 -Wall -o epsviz visualizador-epsilon.c -lm
 *   (el -lm va AL FINAL)
 *
 * USAR (interactivo, manejado por el docente):
 *   ./epsviz [--ascii]
 *     [flechas] mover el punto   [m] x = x + 0.1f   [+/-] alejarse/acercarse
     [u] ir a 2^24   [1] origen   [q] salir
 *
 * OTROS:
 *   ./epsviz --frame=16777216     (imprime una pantalla y sale; sin terminal)
 *   ./epsviz --selfcheck          (valida la matemática; sin terminal)
 *
 * Corre en WSL / Windows Terminal / Linux. Ctrl-C sale y restaura la terminal.
 */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>

/* ------------------------------------------------------------------ */
/*  Floats como enteros: la base de todo el conteo                    */
/* ------------------------------------------------------------------ */
/* Los binary32 NO NEGATIVOS, ordenados de menor a mayor, tienen patrones
 * de bits que también van de menor a mayor si se los lee como enteros sin
 * signo (misma razón por la que el exponente va en exceso: para poder
 * comparar flotantes con el comparador de enteros). Entonces:
 *   cantidad de floats en [a;b)  =  bits(b) - bits(a)
 * sin iterar ni contar uno por uno.                                   */
static uint32_t bits_de(float f) {
    uint32_t u;
    memcpy(&u, &f, sizeof u);           /* NUNCA *(uint32_t*)&f : es UB */
    return u;
}
/* patrón de bits del MENOR float >= v  (dominio: v >= 0) */
static uint32_t ord_ge(double v) {
    float f = (float)v;                  /* redondea al más cercano      */
    if ((double)f < v) f = nextafterf(f, HUGE_VALF);
    return bits_de(f);
}
/* patrón de bits del MENOR float > v */
static uint32_t ord_gt(double v) {
    uint32_t u = ord_ge(v);
    float f;
    memcpy(&f, &u, sizeof f);
    if ((double)f == v) u++;
    return u;
}
/* floats representables en el intervalo CERRADO [a ; b] */
static long cuenta(double a, double b) {
    return (long)ord_gt(b) - (long)ord_ge(a);
}
/* paso al siguiente float (ULP hacia arriba) */
static double ulp_de(float x) {
    return (double)nextafterf(x, HUGE_VALF) - (double)x;
}

/* ------------------------------------------------------------------ */
/*  La escalera de distancias al origen (paradas del viaje)           */
/* ------------------------------------------------------------------ */
/* -1 significa D = 0 (el origen). El resto: D = 2^k. La escalera se
 * arma según la resolución de la terminal: la primera parada después
 * del origen es la primera donde los puntos YA se ven separados
 * (paso >= 2 celdas), así cada pulsación de + cambia la imagen.      */
static int KD[16];
static int ND;
static int g_H = 16;                     /* alto del ploteo, en celdas  */
static double D_de(int i) { return KD[i] < 0 ? 0.0 : ldexp(1.0, KD[i]); }

/* La ventana mide 8.0 (potencia de 2) y el ploteo usa dimensiones que
 * también son potencias de 2: así el tamaño de celda (LADO/Wp) es una
 * potencia de 2 exacta, siempre conmensurable con el paso entre floats
 * (que también lo es) => los patrones son perfectamente regulares y no
 * aparece muaré/aliasing entre la grilla y el muestreo de la pantalla. */
#define LADO 8.0                         /* la ventana: 8.0 x 8.0      */

/* El punto rojo: una POSICION (x, y) con ambas coordenadas float.
 * Con las flechas salta al float VECINO (nextafterf): siempre se mueve,
 * pero el tamaño del salto lo impone la grilla. Con [m] se ejecuta
 * x = x + 0.1f: el paso "humano", que lejos del origen no hace nada.  */
static float  g_px, g_py;
static long   g_int, g_av;               /* intentos y avances de [m]   */
static int    g_ult = -1;                /* -1 nada, 0 [m] clavado, 1 [m] avanzo, 2 flecha */
static double g_dsalto;                  /* tamaño del último salto     */
static double g_sx;                      /* suma exacta del último [m]  */
static void reset_p(int idx) {
    g_px = (float)(D_de(idx) + LADO / 2.0);
    g_py = g_px;
    g_int = 0; g_av = 0; g_ult = -1; g_dsalto = 0.0; g_sx = 0.0;
}
/* flechas: ir al float vecino en esa dirección (si no se va de la ventana) */
static void mover(int idx, int dx, int dy) {
    double D = D_de(idx);
    float nx = g_px, ny = g_py;
    if (dx) nx = nextafterf(g_px, dx > 0 ? HUGE_VALF : -HUGE_VALF);
    if (dy) ny = nextafterf(g_py, dy > 0 ? HUGE_VALF : -HUGE_VALF);
    if ((double)nx < D || (double)nx > D + LADO) return;
    if ((double)ny < D || (double)ny > D + LADO) return;
    g_dsalto = dx ? fabs((double)nx - (double)g_px)
                  : fabs((double)ny - (double)g_py);
    g_px = nx; g_py = ny;
    g_ult = 2;
}

/* ------------------------------------------------------------------ */
/*  Salida bufereada + terminal (mismo esquema que el viz de orden.)  */
/* ------------------------------------------------------------------ */
#define RED   "\033[91m"
#define CYAN  "\033[96m"
#define GREEN "\033[92m"
#define BOLD  "\033[1m"
#define RST   "\033[0m"

static int g_cols = 80, g_rows = 24, g_ascii = 0, g_color = 1;

static char OUT[1 << 17];
static size_t OL;
static void aps(const char *s) { size_t l = strlen(s); if (OL + l < sizeof(OUT) - 1) { memcpy(OUT + OL, s, l); OL += l; } }
static void apf(const char *fmt, ...) {
    char t[512]; va_list ap; va_start(ap, fmt); vsnprintf(t, sizeof t, fmt, ap); va_end(ap); aps(t);
}
static void apcol(const char *c) { if (g_color) aps(c); }

static struct termios g_tsave;
static int g_rawon = 0;
static void term_size(void) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0) { g_cols = ws.ws_col; g_rows = ws.ws_row; }
}
static void term_enter(void) {
    struct termios t;
    tcgetattr(STDIN_FILENO, &g_tsave);
    t = g_tsave;
    t.c_lflag &= (tcflag_t)~(ICANON | ECHO);    /* teclas sin Enter y sin eco */
    t.c_cc[VMIN] = 1; t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    g_rawon = 1;
    printf("\033[?1049h\033[?25l\033[2J"); fflush(stdout);
}
static void term_leave(void) {
    if (g_rawon) { tcsetattr(STDIN_FILENO, TCSANOW, &g_tsave); g_rawon = 0; }
    printf("\033[?25h\033[?1049l"); fflush(stdout);
}
static void on_sigint(int s) { (void)s; term_leave(); _exit(0); }

/* ------------------------------------------------------------------ */
/*  Tamaño del ploteo y escalera (una vez, según la terminal)         */
/* ------------------------------------------------------------------ */
/* ploteo CUADRADO EN PANTALLA: una celda de terminal mide ~1:2 (el
 * doble de alta que de ancha), así que usamos el doble de columnas
 * que de filas y la MISMA cantidad de unidades por eje: un cuadrado
 * de 8x8 unidades se ve cuadrado y las escalas de X e Y son iguales.
 * H se redondea hacia abajo a POTENCIA DE 2 (ver nota junto a LADO).
 * El espacio que sobra a la derecha es el panel de datos.            */
static void calc_H(void) {
    int H = g_rows - 7;
    int p = 8;
    if (2 * H > g_cols - 32) H = (g_cols - 32) / 2;   /* dejar panel  */
    while (p * 2 <= H) p *= 2;
    H = p;
    if (H > 64) H = 64;
    g_H = H;
}
static void armar_escalera(void) {
    /* separación visible cuando paso >= 2 celdas: 2^(k-23) >= 8/H     */
    int h = 0, p = g_H, k, k0, n = 0;
    while (p > 1) { p >>= 1; h++; }      /* h = log2(H)                 */
    k0 = 26 - h;
    if (k0 < 19) k0 = 19;
    KD[n++] = -1;
    for (k = k0; k <= 27; k++) KD[n++] = k;
    ND = n;
}

/* ------------------------------------------------------------------ */
/*  Render                                                            */
/* ------------------------------------------------------------------ */
#define MAXPX 512

static void render(int idx, int alt) {
    double D = D_de(idx);
    int H, Wp;                           /* celdas: alto y ancho (Wp=2H) */
    int WD, HD;                          /* + la columna/fila del borde  */
    static char colx[MAXPX], rowy[MAXPX];
    char panel[12][96];
    int c, r;
    long nx;
    float centro = (float)(D + LADO / 2.0);
    int pcol, prow;
    double ux, uy;

    H = g_H;                             /* calculado en calc_H()       */
    Wp = 2 * H;
    ux = LADO / Wp;
    uy = LADO / H;
    WD = Wp + 1;                         /* el ploteo cubre [D ; D+8]   */
    HD = H + 1;                          /* INCLUSIVE: borde con celda  */

    nx = cuenta(D, D + LADO);            /* por simetría: ny == nx      */

    /* cuántos floats hay en cada columna / fila de celda (0, 1, 2+)   */
    for (c = 0; c < WD; c++) {
        double a = D + c * ux;
        long n = (long)ord_ge(a + ux) - (long)ord_ge(a);
        colx[c] = (char)(n > 2 ? 2 : n);
    }
    for (r = 0; r < HD; r++) {           /* r = 0 es el borde de ABAJO  */
        double a = D + r * uy;
        long n = (long)ord_ge(a + uy) - (long)ord_ge(a);
        rowy[r] = (char)(n > 2 ? 2 : n);
    }

    /* celda del punto rojo */
    pcol = (int)(((double)g_px - D) / ux);
    if (pcol > WD - 1) pcol = WD - 1;
    if (pcol < 0) pcol = 0;
    prow = (int)(((double)g_py - D) / uy);
    if (prow > HD - 1) prow = HD - 1;
    if (prow < 0) prow = 0;

    /* panel de datos (a la derecha del plano) */
    if (KD[idx] < 0) snprintf(panel[0], sizeof panel[0], "D = 0 (el origen)");
    else             snprintf(panel[0], sizeof panel[0], "D = %.0f (2^%d)", D, KD[idx]);
    snprintf(panel[1], sizeof panel[1], "paso entre posiciones: %.10g", ulp_de(centro));
    if (nx > 100000) snprintf(panel[2], sizeof panel[2], "posiciones: %ld x %ld", nx, nx);
    else             snprintf(panel[2], sizeof panel[2], "posiciones: %ld x %ld = %ld", nx, nx, nx * nx);
    if (ulp_de(centro) < uy)                 /* hay celdas con varios floats */
        snprintf(panel[3], sizeof panel[3], "cada %s tapa ~%.2g floats",
                 g_ascii ? "#" : "█", (ux / ulp_de(centro)) * (uy / ulp_de(centro)));
    else
        snprintf(panel[3], sizeof panel[3], "cada %s es exactamente UN float",
                 g_ascii ? "." : "·");
    snprintf(panel[4], sizeof panel[4], "el punto rojo %s es una posicion:", g_ascii ? "@" : "●");
    snprintf(panel[5], sizeof panel[5], "  float x = %.9g;", (double)g_px);
    snprintf(panel[6], sizeof panel[6], "  float y = %.9g;", (double)g_py);
    snprintf(panel[7], sizeof panel[7], "[flechas] saltar al float VECINO");
    snprintf(panel[8], sizeof panel[8], "[m] ejecuta  x = x + 0.1f;");
    panel[9][0] = '\0';
    panel[10][0] = '\0';
    if (g_ult == -1)
        snprintf(panel[9], sizeof panel[9], "(todavia no te moviste)");
    else if (g_ult == 2)
        snprintf(panel[9], sizeof panel[9], "salto al vecino: %.10g", g_dsalto);
    else {
        snprintf(panel[9], sizeof panel[9], "suma exacta: %.10g", g_sx);
        if (g_ult == 1)
            snprintf(panel[10], sizeof panel[10], "redondea a:  %.9g  -> x cambio",
                     (double)g_px);
        else
            snprintf(panel[10], sizeof panel[10], "redondea a:  %.9g  %s == x  (van %ld)",
                     (double)g_px, g_ascii ? ">>" : "✗", g_int);
    }

    OL = 0;
    if (alt) aps("\033[H");

    apcol(BOLD);
    aps(" EL PLANO FLOAT — ventana fija de 8.0 x 8.0 unidades, esquina en (D, D)");
    apcol(RST); aps(alt ? "\033[K\n" : "\n");

    /* marco superior */
    aps(" "); aps(g_ascii ? "+" : "┌");
    for (c = 0; c < WD; c++) aps(g_ascii ? "-" : "─");
    aps(g_ascii ? "+" : "┐"); aps(alt ? "\033[K\n" : "\n");

    /* el plano: un punto por celda + panel a la derecha               */
    for (r = HD - 1; r >= 0; r--) {      /* de arriba hacia abajo       */
        int fila_panel = (HD - 1) - r;   /* 0 arriba                    */
        aps(" "); aps(g_ascii ? "|" : "│");
        apcol(CYAN);
        for (c = 0; c < WD; c++) {
            int on  = rowy[r] && colx[c];
            int jug = (pcol == c) && (prow == r);
            if (jug) {
                apcol(RST); apcol(RED BOLD);
                aps(g_ascii ? "@" : "●");
                apcol(RST); apcol(CYAN);
            }
            else if (!on)                             aps(" ");
            else if (rowy[r] > 1 || colx[c] > 1)      /* varios floats  */
                aps(g_ascii ? "#" : "█");
            else                                      /* UN solo float  */
                aps(g_ascii ? "." : "·");
        }
        apcol(RST);
        aps(g_ascii ? "|" : "│");
        if (fila_panel < 11 && panel[fila_panel][0]) {
            if (fila_panel == 0) apcol(CYAN BOLD);
            if (fila_panel == 5 || fila_panel == 6) apcol(RED);
            if (fila_panel == 9 && g_ult == 2) apcol(GREEN);
            if (fila_panel == 10 && g_ult == 1) apcol(GREEN);
            if (fila_panel == 10 && g_ult == 0) apcol(RED BOLD);
            apf("  %s", panel[fila_panel]);
            apcol(RST);
        }
        aps(alt ? "\033[K\n" : "\n");
    }

    /* marco inferior */
    aps(" "); aps(g_ascii ? "+" : "└");
    for (c = 0; c < WD; c++) aps(g_ascii ? "-" : "─");
    aps(g_ascii ? "+" : "┘"); aps(alt ? "\033[K\n" : "\n");

    if (alt) {
        apcol(BOLD);
        aps(" [flechas] mover  [m] x = x + 0.1f  [+/-] alejar/acercar  [u] 2^24  [1] origen  [q] salir");
        apcol(RST); aps("\033[K\033[J");
    }
    { ssize_t w = write(STDOUT_FILENO, OUT, OL); (void)w; }
}

/* ------------------------------------------------------------------ */
/*  Selfcheck: valida la matemática sin necesitar terminal            */
/* ------------------------------------------------------------------ */
static int check(const char *nom, int ok) {
    printf("%-52s %s\n", nom, ok ? "OK" : "FALLA");
    return !ok;
}
static int selfcheck(void) {
    int f = 0;
    float x, p;
    double muestras[7] = { 1.0, 3.0, 4096.0, 1000000.0, 8388608.0, 16777216.0, 1e9 };
    int i, relok = 1;

    f += check("bits(1.0f) == 0x3F800000", bits_de(1.0f) == 0x3F800000u);
    f += check("ULP(1.0f) == FLT_EPSILON", ulp_de(1.0f) == (double)FLT_EPSILON);
    f += check("floats en [1;2) == 2^23", (long)ord_ge(2.0) - (long)ord_ge(1.0) == 8388608L);
    f += check("floats en [4096;4097) == 2048", (long)ord_ge(4097.0) - (long)ord_ge(4096.0) == 2048L);

    x = 16777215.0f;                      /* 2^24 - 1 */
    f += check("en 2^24-1: x+1.0f avanza", x + 1.0f != x);
    x = 16777216.0f;                      /* 2^24 */
    f += check("en 2^24:   x+1.0f se clava (x+1==x)", x + 1.0f == x);

    for (i = 0; i < 7; i++) {
        float xi = (float)muestras[i];
        double rel = ulp_de(xi) / (double)xi;
        if (!(rel > 1.0 / 16777216.0 / 2.0 && rel <= 1.0 / 8388608.0)) relok = 0;
    }
    f += check("paso relativo en (2^-25 ; 2^-23] en 7 magnitudes", relok);

    /* las ventanas del plano (validadas contra Python antes de fijarlas) */
    f += check("posiciones por eje en [2^20 ; +8] == 65",
               cuenta(ldexp(1.0, 20), ldexp(1.0, 20) + LADO) == 65L);
    f += check("posiciones por eje en [2^22 ; +8] == 17",
               cuenta(ldexp(1.0, 22), ldexp(1.0, 22) + LADO) == 17L);
    f += check("posiciones por eje en [2^24 ; +8] == 5",
               cuenta(ldexp(1.0, 24), ldexp(1.0, 24) + LADO) == 5L);
    f += check("posiciones por eje en [2^26 ; +8] == 2",
               cuenta(ldexp(1.0, 26), ldexp(1.0, 26) + LADO) == 2L);
    f += check("posiciones por eje en [2^27 ; +8] == 1",
               cuenta(ldexp(1.0, 27), ldexp(1.0, 27) + LADO) == 1L);
    f += check("posiciones por eje en [0 ; 8] > 10^9",
               cuenta(0.0, LADO) > 1000000000L);

    /* el jugador */
    p = (float)(ldexp(1.0, 24) + 5.0);
    f += check("p en el centro de D=2^24: p+0.1f == p (clavada)", p + 0.1f == p);
    p = 5.0f;
    f += check("p en el centro de D=0:    p+0.1f avanza", p + 0.1f != p);
    return f;
}

/* ------------------------------------------------------------------ */
static void uso(void) {
    printf(
      "El plano float — Informática II (Weber)\n\n"
      "  ./epsviz [--ascii]          interactivo: + - u 1 q\n"
      "  ./epsviz --frame=D          imprime una pantalla con la esquina en D y sale\n"
      "  ./epsviz --selfcheck        valida la matemática\n\n"
      "  Cada punto: una posición (x,y) representable en float. Ventana fija de\n"
      "  8 x 8 con esquina en (D, D): cerca del origen se ve continua; en\n"
      "  D = 2^24 quedan 5x5 posiciones. Las flechas saltan al float vecino\n"
      "  (el salto lo impone la grilla); [m] intenta x = x + 0.1f. En\n"
      "  D = 2^27 queda UNA posicion.\n");
}

int main(int argc, char **argv) {
    int idx = 0, i, corriendo = 1;
    double vframe = -1.0;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--ascii")) g_ascii = 1;
        else if (!strncmp(argv[i], "--frame=", 8)) vframe = atof(argv[i] + 8);
        else if (!strcmp(argv[i], "--selfcheck")) return selfcheck();
        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) { uso(); return 0; }
    }

    term_size();
    calc_H();
    armar_escalera();

    if (vframe >= 0) {                    /* una pantalla suelta, sin colores */
        int best = 0;
        for (i = 1; i < ND; i++)
            if (fabs(vframe - D_de(i)) < fabs(vframe - D_de(best))) best = i;
        g_color = 0;
        reset_p(best);
        render(best, 0);
        return 0;
    }

    if (!isatty(STDIN_FILENO)) { uso(); return 0; }

    signal(SIGINT, on_sigint);
    term_enter();
    reset_p(idx);
    render(idx, 1);
    while (corriendo) {
        char c = 0;
        int antes = idx;
        if (read(STDIN_FILENO, &c, 1) != 1) break;
        switch (c) {
            case '+': case '=': if (idx < ND - 1) idx++; break;
            case '-': case '_': if (idx > 0)      idx--; break;
            case 'u': case 'U': for (i = 0; i < ND; i++) if (KD[i] == 24) idx = i; break;
            case '1':           idx = 0;                 break;
            case 'm': case 'M': case ' ': {
                float x0 = g_px;
                g_sx = (double)x0 + (double)0.1f;   /* la suma exacta...   */
                g_px = g_px + 0.1f;      /* ...y lo que queda al redondear */
                g_int++;
                if (g_px != x0) { g_av++; g_ult = 1; } else g_ult = 0;
                if ((double)g_px > D_de(idx) + LADO) g_px = x0;  /* borde */
            } break;
            case 0x1B: {                 /* flechas: ESC [ A/B/C/D      */
                char s1 = 0, s2 = 0;
                if (read(STDIN_FILENO, &s1, 1) == 1 && s1 == '[' &&
                    read(STDIN_FILENO, &s2, 1) == 1) {
                    if (s2 == 'A') mover(idx, 0, +1);
                    if (s2 == 'B') mover(idx, 0, -1);
                    if (s2 == 'C') mover(idx, +1, 0);
                    if (s2 == 'D') mover(idx, -1, 0);
                }
            } break;
            case 'w': case 'W': mover(idx, 0, +1); break;
            case 's': case 'S': mover(idx, 0, -1); break;
            case 'a': case 'A': mover(idx, -1, 0); break;
            case 'd': case 'D': mover(idx, +1, 0); break;
            case 'q': case 'Q': corriendo = 0;           break;
            default: break;
        }
        if (idx != antes) reset_p(idx);
        if (corriendo) render(idx, 1);
    }
    term_leave();
    return 0;
}
