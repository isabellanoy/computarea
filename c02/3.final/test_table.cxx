///
/// test_table.cxx
///

#include "names.h"
#include "stochastic.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


// horror: solo hay un departmento!
// Pilas! Los horrores son senales para que Uds mejoren el programa
// deberian tener por lo menos media docena de departamentos
const char *dept[] = {
  "Ingenieria de Computacion"
};

struct Student {
  const char *sid;
  int cohort;
  const char *name;
  const char *dept;
  float gpa;
};

// random student constructor
static Student *random_student() {
  // prep for sid, cohort, gpa
  const int oldest = 2000;
  const int recent = 2020;
  const int delta = 654321 / (recent - oldest);
  const int cohort = random_int(oldest, recent + 1);
  const int number = random_int(1, delta);
  const int NB = 16; // buffer size
  const double gpa = random_int(310, 495)/100.0;
  // usando la tecnica del snprintf otra vez (vean names.cxx)
  char buffer[NB]; // buffer to construct sid
  snprintf(buffer, NB, "%02d-%06d", cohort % 100, number);
  const char *sid = strdup(buffer);

  // allocate memory for the student and initialize fields
  Student *student = (Student *) malloc(sizeof(Student));
  student->sid = sid;
  student->cohort = cohort;
  student->name = random_name();
  student->dept = dept[0]; // horror: todos lo estudiantes estan en el mismo departamento!
  student->gpa = gpa;
  return student;
}

// genera un archivo con N estudiantes "aleatorios"
static int generate_file(int N, const char *filename) {
  FILE *file = fopen(filename, "w");
  for (int i = 0; i < N; ++i) {
    Student *s = random_student();
    // horror: no estamos incluyendo todos los datos del estudiante!
    fprintf(file, "%s, %s, %4.2f\n", s->sid, s->name, s->gpa);
    free(s); 
  }
  fclose(file);
  return 0;
}

// Este es el arreglo de (apuntadores a) estudiantes en memoria
// Esta definido con una maxima capacidad de 10000 estudiantes
// Sin embargo solamente van a usar las primeras NS celdas
// El valor de NS (numero de estudiantes) se computa al cargar archivos
// La forma elegante de hacer esto es usar un arreglo dinamico
// Lo definimos asi para hacerlo mas facil e independiente de dynarray
static int NS = 0;
static const int CAPACITY = 100000;
static Student *student[CAPACITY];

// funcion privada: agrega un estudiante al arreglo, si hay espacio disponible
static void add_student(Student *s) {
  if (NS < CAPACITY) {
    student[NS] = s;
    ++NS;
    // por claridad incrementamos NS (muy importante no olvidarse) por separado
    // tambien podriamos haber dicho students[NS++] = s;
    // pero no students[++NS] = s; // preguntense porque
  } else {
    fprintf(stderr, "No se pudo agregar %s: no hay capacidad", s->sid);
  }
}

static int load_file(const char *filename) {
  FILE *in_file = fopen(filename, "r");
  struct stat sb;
  stat(filename, &sb);

  char *file_contents = (char *)malloc(sizeof(char)*9999);
  int p = 0;
  while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
    Student *student = (Student *) malloc(sizeof(Student));
    student->sid = (char *)malloc(sizeof(char)*9);
    student->name = (char *)malloc(sizeof(char)*15);
    student->dept = (char *)malloc(sizeof(char)*30);
    student->sid = strtok(file_contents, ",");
    student->name = strtok(NULL, ",");
    student->name = student->name + 1;
    student->gpa = atof(strtok(NULL, ","));
    add_student(student);
  }

  fprintf(stdout, "Cargamos %d estudiantes\n", NS);
  fclose(in_file);
  return 0;
}

// ordena un arreglo de estudiantes ...
// de hecho cualquier arreglo de apuntadores a estudiantes (convenzanse!)
static void sort(int N, Student *s[]) {
  
  int i, j, min_idx;
  for (i = 0; i < N-2; i++){
    min_idx = i;
    for (j = i+1; j < N - 2; j++){
      if (strcmp(s[j]->sid, s[min_idx]->sid) < 0){
        min_idx = j;
      }
    }
    Student *studentTemp = (Student *) malloc(sizeof(Student));
    studentTemp->sid = (char *)malloc(sizeof(char)*9);
    studentTemp->name = (char *)malloc(sizeof(char)*15);
    studentTemp->dept = (char *)malloc(sizeof(char)*30);
    *studentTemp = *s[min_idx];
    *s[min_idx] = *s[i];
    *s[i] = *studentTemp;
    free(studentTemp);
  }
  
  // horror: no nos dijeron como ordenar!
  // porque ya saben como hacerlo (duh!) es una adaptacion sencilla de la tarea anterior
  // usar el algoritmo "selection sort" en el arreglo s, de 0 (incluido) a N (no incluido)
  // (noten que, por generalidad, N es un parametro: la funcion sort no conoce el tamano de s)
  // es siempre mejor escribir codigo asi que "cablear" la funcion usando NS y student
  //
  // la clave para ordenamiento es el sid (student id) que es un string
  // y Uds ya saben usar strcmp para decidir la precedencia
  // noten que solo tienen que intercambiar (swap) los apuntadores en el arreglo!
  // es asi de facil: no se pongan a horungar los campos, solo necesitan comparar los sid
}

// salvar los estudiantes en memoria, escribiendolos en un archivo
static int save_file(int N, Student *s[], const char *filename) {
  FILE *file = fopen(filename, "w");
  for (int i = 0; i < N - 1; ++i) {
    fprintf(file, "%s, %s, %4.2f\n", s[i]->sid, s[i]->name, s[i]->gpa);
  }
  fclose(file);
  return 0;
}

static int sort_file(const char *filename) {
  load_file(filename);
  sort(NS, student); // <<< ven la maravilla, solo usamos los primeros NS elementos
  save_file(NS, student, filename);
}

int test_table(int argc, const char *argv[]) {
  if (argc == 2) {
    // prueba rapida del generador de nombres
    for (int i = 0; i < 32; ++i) {
      fprintf(stdout, "%s\n", random_name());
    }
    return 0;
  }

  if (strcmp(argv[2], "gen") == 0) {
    int N = (4 <= argc ? atoi(argv[3]) : 32);
    const char *filename = (5 <= argc ? argv[4] : "students.txt");
    int status = generate_file(N, filename);
    return status;
  }

  if (strcmp(argv[2], "load") == 0) {
    const char *filename = (4 <= argc ? argv[3] : "students.txt");
    int status = load_file(filename);
    return status;
  }

  if (strcmp(argv[2], "sort") == 0) {
    const char *filename = (4 <= argc ? argv[3] : "students.txt");
    int status = sort_file(filename);
    return status;
  }
}
