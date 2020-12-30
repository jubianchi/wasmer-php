typedef struct wasm_valtype_vec_t_t {
    wasm_valtype_vec_t vec;
    zend_object std;
} wasm_valtype_vec_t_t;

#define Z_WASM_VALTYPE_VEC_P(zv) \
    ((wasm_valtype_vec_t_t*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(wasm_valtype_vec_t_t, std)))
