typedef struct wasmer_res {
    bool owned;
    union wasmer_res_inner {
        wasm_engine_t *engine;
        wasm_store_t *store;
        wasm_config_t *config;

        wasm_exporttype_t *exporttype;
        wasm_functype_t *functype;
        wasm_globaltype_t *globaltype;
        wasm_tabletype_t *tabletype;
        wasm_memorytype_t *memorytype;
        wasm_externtype_t *externtype;
        wasm_importtype_t *importtype;
        wasm_valtype_t *valtype;

        wasm_global_t *global;
        wasm_instance_t *instance;
        wasm_module_t *module;
        wasm_extern_t *xtern;
        wasm_table_t *table;
        wasm_memory_t *memory;
        wasm_func_t *func;
        wasm_val_t val;
    } inner;
} wasmer_res;

/**
 * Convert a zval* into a wasmer_res*
 */
#define WASMER_RES_P(name) ((wasmer_res*)Z_RES_P(name)->ptr)
/**
 * Convert a zval* into a wasmer_res* and returns the inner type
 */
#define WASMER_RES_P_INNER(name, type) WASMER_RES_P(name)->inner.type

/**
 * Returns the inner type from a wasmer_res*
 */
#define WASMER_RES_INNER(name, type) name->inner.type



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

Z_WASMER_DECLARE_CE_STRUCT(externtype)
#define Z_WASM_EXTERNTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(externtype, zv)

Z_WASMER_DECLARE_CE_STRUCT(importtype)
#define Z_WASM_IMPORTTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(importtype, zv)

Z_WASMER_DECLARE_CE_STRUCT(exporttype)
#define Z_WASM_EXPORTTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(exporttype, zv)

Z_WASMER_DECLARE_CE_STRUCT(functype)
#define Z_WASM_FUNCTYPE_VEC_P(zv) Z_WASMER_DECLARE_CE_P(functype, zv)

Z_WASMER_DECLARE_CE_STRUCT(extern)
#define Z_WASM_EXTERN_VEC_P(zv) ((wasm_extern_vec_c*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(wasm_extern_vec_c, std)))

Z_WASMER_DECLARE_CE_STRUCT(val)
#define Z_WASM_VAL_VEC_P(zv) Z_WASMER_DECLARE_CE_P(val, zv)