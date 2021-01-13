#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(extern)
WASMER_IMPORT_RESOURCE(func)

WASMER_DECLARE_OWN(extern)

PHP_FUNCTION (wasm_extern_kind) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_type) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_func) {
    zval *extern_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(extern_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(extern)

    wasm_extern_t *wasm_extern = Z_RES_P(extern_val)->ptr;
    wasm_func_t *func = wasm_extern_as_func(wasm_extern);

    zend_resource *extern_res;
    extern_res = zend_register_resource(func, le_wasm_func);

    RETURN_RES(extern_res);
}

PHP_FUNCTION (wasm_extern_as_global) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_table) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_memory) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_METHOD (Wasm_Vec_Extern, __construct) {
    zend_array *externs_ht;
    zend_long size;
    zend_bool is_null = 1;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_ARRAY_HT_OR_LONG_OR_NULL(externs_ht, size, is_null)
    ZEND_PARSE_PARAMETERS_END();

    wasm_extern_vec_c *wasm_extern_vec = Z_WASM_EXTERN_VEC_P(ZEND_THIS);
    wasm_extern_vec_t vec;

    if (is_null) {
        wasm_extern_vec_new_empty(&vec);\
    } else if(externs_ht) {
        int len = zend_hash_num_elements(externs_ht);
        wasm_extern_vec_new_uninitialized(&vec, len);

        zval *tmp;
        zend_ulong index;

        ZEND_HASH_REVERSE_FOREACH_NUM_KEY_VAL(externs_ht, index, tmp) {
                vec.data[index] = Z_RES_P(tmp)->ptr;
        } ZEND_HASH_FOREACH_END();
    } else {
        wasm_extern_vec_new_uninitialized(&vec, size);
    }

    wasm_extern_vec->vec = vec;
}

PHP_METHOD (Wasm_Vec_Extern, count) {
    ZEND_PARSE_PARAMETERS_NONE();

    wasm_extern_vec_c *wasm_extern_vec = Z_WASM_EXTERN_VEC_P(ZEND_THIS);

    RETURN_LONG(wasm_extern_vec->vec.size);
}

PHP_METHOD (Wasm_Vec_Extern, offsetExists) {
    zend_long offset;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_LONG(offset)
    ZEND_PARSE_PARAMETERS_END();

    wasm_extern_vec_c *wasm_extern_vec = Z_WASM_EXTERN_VEC_P(ZEND_THIS);

    if(offset >= wasm_extern_vec->vec.size) {
        RETURN_FALSE;
    }

    RETURN_BOOL(offset < wasm_extern_vec->vec.size);
}

PHP_METHOD (Wasm_Vec_Extern, offsetGet) {
    zend_long offset;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_LONG(offset)
    ZEND_PARSE_PARAMETERS_END();

    wasm_extern_vec_c *wasm_extern_vec = Z_WASM_EXTERN_VEC_P(ZEND_THIS);

    if(offset >= wasm_extern_vec->vec.size) {
        zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\Extern::offsetGet($offset) index out of bounds");
    }
    if(wasm_extern_vec->vec.data[offset] == NULL) {
        RETURN_NULL();
    }
    zend_resource *extern_res;
    extern_res = zend_register_resource(wasm_extern_vec->vec.data[offset], le_wasm_extern);

    RETURN_RES(extern_res);
}

PHP_METHOD (Wasm_Vec_Extern, offsetSet) {
    zend_long offset;
    zval *extern_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_LONG(offset)
            Z_PARAM_RESOURCE(extern_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(extern)

    wasm_extern_vec_c *wasm_extern_vec = Z_WASM_EXTERN_VEC_P(ZEND_THIS);

    if(offset >= wasm_extern_vec->vec.size) {
        zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\Extern::offsetSet($offset) index out of bounds");
    }

    wasm_extern_vec->vec.data[offset] = Z_RES_P(extern_val)->ptr;
}

PHP_METHOD (Wasm_Vec_Extern, offsetUnset) {\
    zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\Extern::offsetUnset($offset) not available");\
}
