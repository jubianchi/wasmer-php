#include "php.h"

#define WASMER_IMPORT_RESOURCE(name)\
extern int le_wasm_##name;\
extern const char *le_wasm_##name##_name;\

#define WASMER_FETCH_RESOURCE(name)\
if (zend_fetch_resource(Z_RES_P(name##_val), le_wasm_##name##_name,\
                        le_wasm_##name) == NULL) {\
    RETURN_THROWS();\
}

#define WASMER_COPY(name)\
PHP_FUNCTION (wasm_##name##_copy) {\
    zval *name##_val;\
    \
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)\
            Z_PARAM_RESOURCE(name##_val)\
    ZEND_PARSE_PARAMETERS_END();\
    \
    WASMER_FETCH_RESOURCE(name)\
    \
    wasm_##name##_t *name = wasm_##name##_copy(Z_RES_P(name##_val)->ptr);\
    \
    zend_resource *name##_res;\
    name##_res = zend_register_resource((void *) name, le_wasm_##name);\
    \
    RETURN_RES(name##_res);\
}

#define WASMER_DELETE_WITHOUT_DTOR(name)\
PHP_FUNCTION (wasm_##name##_delete) {\
    zval *name##_val;\
    \
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)\
        Z_PARAM_RESOURCE(name##_val)\
    ZEND_PARSE_PARAMETERS_END();\
    \
    if (zend_fetch_resource(Z_RES_P(name##_val), le_wasm_##name##_name,\
        le_wasm_##name) == NULL) {\
        RETURN_THROWS();\
    }\
    zend_list_close(Z_RES_P(name##_val));\
    \
    RETURN_TRUE;\
}

#define WASMER_DECLARE_VEC(class_name, macro, name)\
WASMER_DECLARE_VEC_CONSTRUCT(class_name, name)\
WASMER_DECLARE_VEC_COUNT(class_name, macro, name)\
WASMER_DECLARE_VEC_OFFSET_EXISTS(class_name, macro, name)\
WASMER_DECLARE_VEC_OFFSET_GET(class_name, macro, name)\
WASMER_DECLARE_VEC_OFFSET_SET(class_name, macro, name)\
WASMER_DECLARE_VEC_OFFSET_UNSET(class_name)

// TODO(jubianchi): Throw if size != len (zend_hash_num_elements(name##s_ht))
#define WASMER_DECLARE_VEC_CONSTRUCT(class_name, name)\
PHP_METHOD (Wasm_Vec_##class_name, __construct) {\
    zend_long size;\
    zend_bool size_is_null = 1;\
    zend_array *name##s_ht;\
    \
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 2)\
            Z_PARAM_OPTIONAL\
            Z_PARAM_LONG_OR_NULL(size, size_is_null)\
            Z_PARAM_ARRAY_HT_OR_NULL(name##s_ht)\
    ZEND_PARSE_PARAMETERS_END();\
    \
    wasm_##name##_vec_t_t *wasm_##name##_vec = Z_WASM_VALTYPE_VEC_P(ZEND_THIS);\
    wasm_##name##_vec_t vec;\
    \
    if (size_is_null) {\
        wasm_##name##_vec_new_empty(&vec);\
    } else if(name##s_ht) {\
        int len = zend_hash_num_elements(name##s_ht);\
        \
        wasm_##name##_vec_new_uninitialized(&vec, size);\
        \
        zval *tmp;\
        zend_ulong index;\
        wasm_##name##_t *name##s[len];\
        \
        ZEND_HASH_REVERSE_FOREACH_NUM_KEY_VAL(name##s_ht, index, tmp) {\
                zend_resource *res = zend_fetch_resource(Z_RES_P(tmp), le_wasm_##name##_name, le_wasm_##name);\
                \
                name##s[index] = (wasm_##name##_t*)res->ptr;\
        } ZEND_HASH_FOREACH_END();\
        \
        wasm_##name##_vec_new(&vec, size, name##s);\
    } else {\
        wasm_##name##_vec_new_uninitialized(&vec, size);\
    }\
    \
    wasm_##name##_vec->vec = vec;\
}

#define WASMER_DECLARE_VEC_COUNT(class_name, macro, name)\
PHP_METHOD (Wasm_Vec_##class_name, count) {\
    ZEND_PARSE_PARAMETERS_NONE();\
    \
    wasm_##name##_vec_t_t *wasm_##name##_vec = Z_WASM_##macro##_VEC_P(ZEND_THIS);\
    wasm_##name##_vec_t vec = wasm_##name##_vec->vec;\
    \
    RETURN_LONG(vec.size);\
}

// TODO(jubianchi): Throw if offset is invalid
#define WASMER_DECLARE_VEC_OFFSET_EXISTS(class_name, macro, name)\
PHP_METHOD (Wasm_Vec_##class_name, offsetExists) {\
    zend_long offset;\
    \
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)\
            Z_PARAM_LONG(offset)\
    ZEND_PARSE_PARAMETERS_END();\
    \
    wasm_##name##_vec_t_t *wasm_##name##_vec = Z_WASM_##macro##_VEC_P(ZEND_THIS);\
    \
    RETURN_BOOL(offset < wasm_##name##_vec->vec.size);\
}

// TODO(jubianchi): Throw if offset is invalid
// TODO(jubianchi): Throw if offset >= size
#define WASMER_DECLARE_VEC_OFFSET_GET(class_name, macro, name)\
PHP_METHOD (Wasm_Vec_##class_name, offsetGet) {\
    zend_long offset;\
    \
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)\
            Z_PARAM_LONG(offset)\
    ZEND_PARSE_PARAMETERS_END();\
    \
    wasm_##name##_vec_t_t *wasm_##name##_vec = Z_WASM_##macro##_VEC_P(ZEND_THIS);\
    \
    zend_resource *name##_res;\
    name##_res = zend_register_resource((void *) wasm_##name##_vec->vec.data[offset], le_wasm_##name);\
    \
    RETURN_RES(name##_res);\
}

// TODO(jubianchi): Throw if offset is invalid
// TODO(jubianchi): Throw if offset >= size
#define WASMER_DECLARE_VEC_OFFSET_SET(class_name, macro, name)\
PHP_METHOD (Wasm_Vec_##class_name, offsetSet) {\
    zend_long offset;\
    zval *name##_val;\
    \
    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)\
            Z_PARAM_LONG(offset)\
            Z_PARAM_RESOURCE(name##_val)\
    ZEND_PARSE_PARAMETERS_END();\
    \
    WASMER_FETCH_RESOURCE(name)\
    \
    wasm_##name##_vec_t_t *wasm_##name##_vec = Z_WASM_##macro##_VEC_P(ZEND_THIS);\
    \
    wasm_##name##_vec->vec.data[offset] = Z_RES_P(name##_val)->ptr;\
}

#define WASMER_DECLARE_VEC_OFFSET_UNSET(class_name)\
PHP_METHOD (Wasm_Vec_##class_name, offsetUnset) {\
    zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\" #class_name "::offsetUnset($offset) not available");\
}

#define WASMER_DECLARE_TYPE(class_name, macro, name) \
WASMER_IMPORT_RESOURCE(name)\
WASMER_DELETE_WITHOUT_DTOR(name)\
WASMER_COPY(name)\
WASMER_DECLARE_VEC(class_name, macro, name)