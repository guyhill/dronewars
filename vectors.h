#define T int
#define PREFIX I
#undef COLOR
#define N 2
#include "generate-vector-class.h"

#undef T
#define T float
#undef PREFIX
#define PREFIX
#include "generate-vector-class.h"

#undef N
#define N 3
#include "generate-vector-class.h"

#undef N
#define N 4
#include "generate-vector-class.h"

#define COLOR
#undef N
#define N 3
#include "generate-vector-class.h"

#undef N
#define N 4
#include "generate-vector-class.h"

#undef T
#undef PREFIX
#undef N
#undef COLOR
