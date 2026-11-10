// I think this TU didn't include the header or used a different header
// allowing for both the inline definition and these symbols to exist

#define __HI(x) *(int*)&x
#define __LO(x) *(1 + (int*)&x)
#define __HIp(x) *(int*)x
#define __LOp(x) *(1 + (int*)x)

#if 0
// Dead-stripped from the retail DOL (no caller); kept out of the build so extab/extabindex
// contain only the functions the original object has.
int __fpclassifyf(float x) {
    switch ((*(long*)&x) & 0x7f800000) {
    case 0x7f800000: {
        if ((*(long*)&x) & 0x007fffff)
            return 1;
        else
            return 2;
        break;
    }
    case 0: {
        if ((*(long*)&x) & 0x007fffff)
            return 5;
        else
            return 3;
        break;
    }
    }
    return 4;
}
#endif

int __signbitd(double x) {
    return __HI(x) & 0x80000000;
}

int __fpclassifyd(double x) {
    switch (__HI(x) & 0x7ff00000) {
    case 0x7ff00000: {
        if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
            return 1;
        else
            return 2;
        break;
    }
    case 0: {
        if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
            return 5;
        else
            return 3;
        break;
    }
    }
    return 4;
}
