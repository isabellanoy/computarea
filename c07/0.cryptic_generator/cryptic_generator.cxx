///
/// cryptic.cxx
///

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int UInt;
typedef unsigned short int Nugget;
typedef double Seed;

const Nugget NCLIPPER = 32768;

Seed VISICALC =  M_PI - floor(M_PI) + 0.1979;
Seed ZENSHEET =  M_PI - floor(M_PI) + 0.1989;

Seed seed = VISICALC;

void reset_seed(Seed s) {
  seed = s;
}

Seed gfrac(Seed x) {
  return x - floor(x);
}

UInt random() {
  seed = gfrac(seed * 997);
  return UInt(NCLIPPER * seed);
}

const Nugget p9[] = {
  907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

const Nugget PCLIPPER = sizeof(p9) / sizeof(Nugget);

const Nugget K = 16;

Nugget bhh[K][K];

void show() {
  fprintf(stdout, "{\n");
  for (int i = 0; i < K; ++i) {
    fprintf(stdout, "  { %5hd", bhh[i][0]);
    for (int j = 1; j < K; ++j) {
      fprintf(stdout, ", %5hd", bhh[i][j]);
    }
    fprintf(stdout, " }\n");
  }
  fprintf(stdout, "}\n");
}

void generate(Seed seed) {
  reset_seed(seed);
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < K; ++j) {
      bhh[i][j] = p9[random() % PCLIPPER];
    }
  }
}

const Nugget RECURSER = 10000;

Nugget rbhh() {
  Nugget i = random() % K;
  Nugget j = random() % K;
  return bhh[i][j];
}

Nugget tx(Nugget x, Nugget m, Nugget s) {
  return Nugget((UInt(x) * UInt(m) + UInt(s)) % NCLIPPER);
}

Nugget rooter(Nugget x) {
  Nugget m = rbhh();
  Nugget s = rbhh();
  return tx(x, m, s);
}

Nugget roto(Nugget N, Nugget x) {
  for (Nugget i = 0; i < N; ++i) {
    x = rooter(x);
  }
  return x;
}

Nugget nugget(const char *key) {
  Nugget result = 0;
  while (*key) {
    result = roto(RECURSER, result + *key++);
  }
  return result;  
}

void validate(int argc, const char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <clave>\n", argv[0]);
    fprintf(stderr, "Donde <clave> es su dirección de email de la universidad\n");
    exit(1);
  }
}

int main(int argc, const char *argv[]) {

  validate(argc, argv);
  generate(VISICALC);
  show();
  reset_seed(ZENSHEET);

  Nugget x = nugget(argv[1]);
  fprintf(stdout, "Nugget: %5hd\n", x);

  return 0;
}
