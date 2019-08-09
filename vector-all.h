#define COLOR
#define N 3
#define T float

#ifdef COLOR
#define DIM1 r
#define DIM2 g
#define DIM3 b
#define DIM4 a
#define CLASS_BASE CVec
#else
#define DIM1 x
#define DIM2 y
#define DIM3 z
#define DIM4 w
#define CLASS_BASE Vec
#endif

#define PASTER(X, Y) X ## Y
#define CLASS_EVALUATOR(X, Y) PASTER(X, Y)
#define CLASS_NAME CLASS_EVALUATOR(CLASS_BASE, N)

#if 0
#define MEMBERS1 DIM1
#define MEMBERS2 MEMBERS1, DIM2
#define MEMBERS3 MEMBERS2, DIM3
#define MEMBERS4 MEMBERS3, DIM4
#define MEMBERS_EVALUATOR(X) PASTER(MEMBERS, X)
#define MEMBERS MEMBERS_EVALUATOR(N)

#define ARGS1 T DIM1
#define ARGS2 ARGS1, T DIM2
#define ARGS3 ARGS2, T DIM3
#define ARGS4 ARGS3, T DIM4
#define ARGS_EVALUATOR(X) PASTER(ARGS, X)
#define ARGS ARGS_EVALUATOR(N)

#define MINUS1 -DIM1
#define MINUS2 MINUS1, -DIM2
#define MINUS3 MINUS2, -DIM3
#define MINUS4 MINUS3, -DIM4
#define MINUS_EVALUATOR(X) PASTER(MINUS, X)
#define MINUS MINUS_EVALUATOR(N)

#define SUM1 DIM1 += v.DIM1;
#define SUM2 SUM1 DIM2 += v.DIM2;
#define SUM3 SUM2 DIM3 += v.DIM3;
#define SUM4 SUM3 DIM4 += v.DIM4;
#define SUM_EVALUATOR(X) PASTER(SUM, X)
#define SUM SUM_EVALUATOR(N)

#define DIFF1 DIM1 -= v.DIM1;
#define DIFF2 DIFF1 DIM2 -= v.DIM2;
#define DIFF3 DIFF2 DIM3 -= v.DIM3;
#define DIFF4 DIFF3 DIM4 -= v.DIM4;
#define DIFF_EVALUATOR(X) PASTER(DIFF, X)
#define DIFF DIFF_EVALUATOR(N)

#define MUL1 DIM1 *= c;
#define MUL2 MUL1 DIM2 *= c;
#define MUL3 MUL2 DIM3 *= c;
#define MUL4 MUL3 DIM4 *= c;
#define MUL_EVALUATOR(X) PASTER(MUL, X)
#define MUL MUL_EVALUATOR(N)

#define DIVIDE1 DIM1 /= c;
#define DIVIDE2 DIVIDE1 DIM2 /= c;
#define DIVIDE3 DIVIDE2 DIM3 /= c;
#define DIVIDE4 DIVIDE3 DIM4 /= c;
#define DIVIDE_EVALUATOR(X) PASTER(DIVIDE, X)
#define DIVIDE DIVIDE_EVALUATOR(N)

#define COUT1 << v.DIM1
#define COUT2 COUT1 << " " << v.DIM2
#define COUT3 COUT2 << " " << v.DIM3
#define COUT4 COUT3 << " " << v.DIM4
#define COUT_EVALUATOR(X) PASTER(COUT, X)
#define COUT COUT_EVALUATOR(N)

#define CIN1 >> v.DIM1
#define CIN2 CIN1 >> v.DIM2
#define CIN3 CIN2 >> v.DIM3
#define CIN4 CIN3 >> v.DIM4
#define CIN_EVALUATOR(X) PASTER(CIN, X)
#define CIN CIN_EVALUATOR(N)
#endif

#define INIT1 DIM1(DIM1)
#define INIT2 INIT1, DIM2(DIM2)
#define INIT3 INIT2, DIM3(DIM3)
#define INIT4 INIT3, DIM4(DIM4)
#define INIT_EVALUATOR(X) PASTER(INIT, X)
#define INIT INIT_EVALUATOR(N)

#define CEXPAND1(PFX) PFX DIM1
#define CEXPAND2(PFX) CEXPAND1(PFX), PFX DIM2
#define CEXPAND3(PFX) CEXPAND2(PFX), PFX DIM3
#define CEXPAND4(PFX) CEXPAND3(PFX), PFX DIM4
#define CEXPAND_EVALUATOR(X) PASTER(CEXPAND, X)
#define CEXPAND_DIMENSIONS(PFX) CEXPAND_EVALUATOR(N)(PFX)

#define EXPAND1(PFX, IFX, SFX) PFX DIM1 SFX
#define EXPAND2(PFX, IFX, SFX) EXPAND1(PFX, IFX, SFX) IFX PFX DIM2 SFX
#define EXPAND3(PFX, IFX, SFX) EXPAND2(PFX, IFX, SFX) IFX PFX DIM3 SFX
#define EXPAND4(PFX, IFX, SFX) EXPAND3(PFX, IFX, SFX) IFX PFX DIM4 SFX
#define EXPAND_EVALUATOR(X) PASTER(EXPAND, X)
#define EXPAND_DIMENSIONS(PFX, IFX, SFX) EXPAND_EVALUATOR(N)(PFX, IFX, SFX)

#define EXPAND2_1(PFX, IFX, SFX) PFX DIM1 IFX DIM1 SFX
#define EXPAND2_2(PFX, IFX, SFX) EXPAND2_1(PFX, IFX, SFX) PFX DIM2 IFX DIM2 SFX
#define EXPAND2_3(PFX, IFX, SFX) EXPAND2_2(PFX, IFX, SFX) PFX DIM3 IFX DIM3 SFX
#define EXPAND2_4(PFX, IFX, SFX) EXPAND2_3(PFX, IFX, SFX) PFX DIM4 IFX DIM4 SFX
#define EXPAND2_EVALUATOR(X) PASTER(EXPAND2_, X)
#define EXPAND2_DIMENSIONS(PFX, IFX, SFX) EXPAND2_EVALUATOR(N)(PFX, IFX, SFX)

class CLASS_NAME {
public:
    T CEXPAND_DIMENSIONS();

    CLASS_NAME() {}
    CLASS_NAME(CEXPAND_DIMENSIONS(T)): INIT {}

    CLASS_NAME &operator+() {
        return *this;
    }
    CLASS_NAME operator-() {
        return CLASS_NAME(CEXPAND_DIMENSIONS(-));
    }
    CLASS_NAME &operator+=(const CLASS_NAME &v) {
        EXPAND2_DIMENSIONS(, += v., ;)
        return *this;
    }
    CLASS_NAME &operator-=(const CLASS_NAME &v) {
        EXPAND2_DIMENSIONS(, -= v., ;)
        return *this;
    }
    CLASS_NAME &operator*=(const T c) {
        EXPAND_DIMENSIONS(,,*= c;)
        return *this;
    }
    CLASS_NAME &operator/=(const T c) {
        EXPAND_DIMENSIONS(,,/= c;)
        return *this;
    }
    CLASS_NAME operator+(const CLASS_NAME &v) {
        CLASS_NAME result = *this;
        return result += v;
    }
    CLASS_NAME operator-(const CLASS_NAME &v) {
        CLASS_NAME result = *this;
        return result -= v;
    }
    CLASS_NAME operator*(const T c) {
        CLASS_NAME result = *this;
        return result *= c;
    }
    CLASS_NAME operator+(const T c) {
        CLASS_NAME result = *this;
        return result /= c;
    }     
    friend std::ostream &operator<<(std::ostream &s, const CLASS_NAME &v);
    friend std::istream &operator>>(std::istream &s, CLASS_NAME &v);
};

inline std::ostream &operator<<(std::ostream &s, const CLASS_NAME &v) {
    s EXPAND_DIMENSIONS(<< v., << " ",);
    return s;
}

inline std::istream &operator>>(std::istream &s, CLASS_NAME &v) {
    s EXPAND_DIMENSIONS(>> v., ,);
    return s;
}
