
// Helper macros
// PASTER() pastes two arguments together. It is necessary to do this in two separate
// macro expansion steps as ## does not perform macro expansion of its arguments.
// UNPAREN X removes the parentheses from a parenthesized macro argument X.
// This is necessary because we want to be able to have a comma as macro argument, and
// the only way to do so is to put it between parentheses.
#define PASTER(X, Y) X ## Y
#define EVALUATOR(X, Y) PASTER(X, Y)
#define UNPAREN(...) __VA_ARGS__

// Component and class names
#ifdef COLOR
#define COMPONENT1 r
#define COMPONENT2 g
#define COMPONENT3 b
#define COMPONENT4 a
#define CLASS_BASE EVALUATOR(PREFIX, CVec)
#else
#define COMPONENT1 x
#define COMPONENT2 y
#define COMPONENT3 z
#define COMPONENT4 w
#define CLASS_BASE EVALUATOR(PREFIX, Vec)
#endif

// Generates the class name. Class names generated are of the form [C]VecN,
// where the C is only present for color vectors, and N runs from 1 to 4.
#define CLASS_NAME EVALUATOR(CLASS_BASE, N)

// Generates code that is repeated for the components of a single vector of size N.
// If N = 3, REPEAT1(A, COMPONENT, B, (Z)) generates the following code:
//
// A COMPONENT1 B Z A COMPONENT2 B Z A COMPONENT3 B 
//
// Arguments A, B and Z may be empty. Z may contain one or more commas.
#define REPEAT1_1(PFX, SFX)                                           PFX COMPONENT1 SFX
#define REPEAT1_2(SEP, PFX, SFX) REPEAT1_1(PFX, SFX)      UNPAREN SEP PFX COMPONENT2 SFX
#define REPEAT1_3(SEP, PFX, SFX) REPEAT1_2(SEP, PFX, SFX) UNPAREN SEP PFX COMPONENT3 SFX
#define REPEAT1_4(SEP, PFX, SFX) REPEAT1_3(SEP, PFX, SFX) UNPAREN SEP PFX COMPONENT4 SFX
#define REPEAT1_EVALUATOR(X) PASTER(REPEAT1_, X)
#define REPEAT1(PFX, C, SFX, SEP) REPEAT1_EVALUATOR(N)(SEP, PFX, SFX)

// Generates code that is repeated for the components of two vectors of size N.
// If N = 3, REPEAT2(A, COMPONENT, B, COMPONENT, C, (Z)) generates the following code:
//
// A COMPONENT1 B COMPONENT1 C Z A COMPONENT2 B COMPONENT2 C Z A COMPONENT3 B COMPONENT3 C
// 
// Arguments A, B, C and Z may be empty. Z may contain one or more commas.
#define REPEAT2_1(PFX, IFX, SFX)                                                PFX COMPONENT1 IFX COMPONENT1 SFX
#define REPEAT2_2(SEP, PFX, IFX, SFX) REPEAT2_1(PFX, IFX, SFX)      UNPAREN SEP PFX COMPONENT2 IFX COMPONENT2 SFX
#define REPEAT2_3(SEP, PFX, IFX, SFX) REPEAT2_2(SEP, PFX, IFX, SFX) UNPAREN SEP PFX COMPONENT3 IFX COMPONENT3 SFX
#define REPEAT2_4(SEP, PFX, IFX, SFX) REPEAT2_3(SEP, PFX, IFX, SFX) UNPAREN SEP PFX COMPONENT4 IFX COMPONENT4 SFX
#define REPEAT2_EVALUATOR(X) PASTER(REPEAT2_, X)
#define REPEAT2(PFX, C1, IFX, C2, SFX, SEP) REPEAT2_EVALUATOR(N)(SEP, PFX, IFX, SFX)


// Generic vector class for position and color vectors of size 2, 3 and 4. All the usual operators are defined,
// including streaming I/O. The inner product is defined as well, as are, for N = 3, the cross product and triple product.
// If N == 2, the scalar cross product is defined instead.
class CLASS_NAME {
public:
    T REPEAT1(, COMPONENT,, (,));

    CLASS_NAME() {}
    CLASS_NAME(REPEAT1(T, COMPONENT,, (,))): REPEAT2(, COMPONENT, {, COMPONENT, }, (,)) {}

    CLASS_NAME &operator+() {
        return *this;
    }
    CLASS_NAME operator-() {
        return CLASS_NAME(REPEAT1(-, COMPONENT,,(,)));
    }
    CLASS_NAME &operator+=(const CLASS_NAME &v) {
        REPEAT2(, COMPONENT, += v., COMPONENT,, (;));
        return *this;
    }
    CLASS_NAME &operator-=(const CLASS_NAME &v) {
        REPEAT2(, COMPONENT, -= v., COMPONENT,, (;));
        return *this;
    }
    CLASS_NAME &operator*=(const T c) {
        REPEAT1(, COMPONENT, *= c, (;));
        return *this;
    }
    CLASS_NAME &operator/=(const T c) {
        REPEAT1(, COMPONENT, /= c, (;));
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
    friend T inner(const CLASS_NAME &u, const CLASS_NAME &v);
#if N == 2
    friend T cross(const CLASS_NAME &u, const CLASS_NAME &v);
#elif N == 3
    friend CLASS_NAME cross(const CLASS_NAME &u, const CLASS_NAME &v);
    friend T triple(const CLASS_NAME &u, const CLASS_NAME &v, const CLASS_NAME &w);
#endif
};

inline std::ostream &operator<<(std::ostream &s, const CLASS_NAME &v) {
    s << REPEAT1(v., COMPONENT,, (<< " " <<));
    return s;
}

inline std::istream &operator>>(std::istream &s, CLASS_NAME &v) {
    s >> REPEAT1(v., COMPONENT,, (>>));
    return s;
}

inline T inner(const CLASS_NAME &u, const CLASS_NAME &v) {
    return REPEAT2(u., COMPONENT, * v., COMPONENT,, (+));
}

#if N == 2
inline T cross(const CLASS_NAME &u, const CLASS_NAME &v) {
    return u.COMPONENT1 * v.COMPONENT2 - u.COMPONENT2 * v.COMPONENT1;
}

#elif N == 3
inline CLASS_NAME cross(const CLASS_NAME &u, const CLASS_NAME &v) {
    return CLASS_NAME(
        u.COMPONENT2 * v.COMPONENT3 - u.COMPONENT3 * v.COMPONENT2,
        u.COMPONENT3 * v.COMPONENT1 - u.COMPONENT1 * v.COMPONENT3,
        u.COMPONENT1 * v.COMPONENT2 - u.COMPONENT2 * v.COMPONENT1        
    );
}

inline T triple(const CLASS_NAME &u, const CLASS_NAME &v, const CLASS_NAME &w) {
    return inner(u, cross(v, w));
}
#endif

#undef PASTER
#undef EVALUATOR
#undef UNPAREN
#undef COMPONENT1
#undef COMPONENT2
#undef COMPONENT3
#undef COMPONENT4
#undef CLASS_BASE
#undef CLASS_NAME
#undef REPEAT1_1
#undef REPEAT1_2
#undef REPEAT1_3
#undef REPEAT1_4
#undef REPEAT1_EVALUATOR
#undef REPEAT1
#undef REPEAT2_1
#undef REPEAT2_2
#undef REPEAT2_3
#undef REPEAT2_4
#undef REPEAT2_EVALUATOR
#undef REPEAT2
