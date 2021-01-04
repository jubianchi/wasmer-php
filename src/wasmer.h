#define Z_WASMER_DECLARE_CE_STRUCT(name)\
typedef struct wasm_##name##_vec_c {\
    wasm_##name##_vec_t vec;\
    zend_object std;\
} wasm_##name##_vec_c;

#define Z_WASMER_DECLARE_CE_P(name, zv)\
    ((wasm_##name##_vec_c*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(wasm_##name##_vec_c, std)))

Z_WASMER_DECLARE_CE_STRUCT(valtype)
#define Z_WASM_VALTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(valtype, zv)

Z_WASMER_DECLARE_CE_STRUCT(globaltype)
#define Z_WASM_GLOBALTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(globaltype, zv)

Z_WASMER_DECLARE_CE_STRUCT(tabletype)
#define Z_WASM_TABLETYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(tabletype, zv)

Z_WASMER_DECLARE_CE_STRUCT(memorytype)
#define Z_WASM_MEMORYTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(memorytype, zv)