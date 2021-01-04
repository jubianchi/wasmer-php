typedef struct wasm_valtype_vec_c {
    wasm_valtype_vec_t vec;
    zend_object std;
} wasm_valtype_vec_c;

#define Z_WASM_VALTYPE_VEC_P(zv) \
    ((wasm_valtype_vec_c*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(wasm_valtype_vec_c, std)))

typedef struct wasm_globaltype_vec_c {
    wasm_globaltype_vec_t vec;
    zend_object std;
} wasm_globaltype_vec_c;

#define Z_WASM_GLOBALTYPE_VEC_P(zv) \
    ((wasm_globaltype_vec_c*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(wasm_globaltype_vec_c, std)))
