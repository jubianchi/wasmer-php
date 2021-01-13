#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasmer_wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(val)

WASMER_DELETE_WITHOUT_DTOR(val)

PHP_FUNCTION (wasm_val_copy) {
    zval *val_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(val_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(val)

    wasm_val_t val;
    wasm_val_copy(&val, Z_RES_P(val_val)->ptr);

    WASMER_HANDLE_ERROR

    zend_resource *val_res;
    val_res = zend_register_resource(&val, le_wasm_val);

    RETURN_RES(val_res);
}

PHP_FUNCTION (wasm_val_i32) {
    zend_long value;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_t val = {.kind = WASM_I32, .of = {.i32 = value}};

    zend_resource *val_res;
    val_res = zend_register_resource(&val, le_wasm_val);

    RETURN_RES(val_res);
}

PHP_FUNCTION (wasm_val_i64) {
    zend_long value;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_LONG(value)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_t val = {.kind = WASM_I64, .of = {.i64 = value}};

    zend_resource *val_res;
    val_res = zend_register_resource(&val, le_wasm_val);

    RETURN_RES(val_res);
}

PHP_FUNCTION (wasm_val_f32) {
    double value;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_t val = {.kind = WASM_F32, .of = {.f32 = value}};

    zend_resource *val_res;
    val_res = zend_register_resource(&val, le_wasm_val);

    RETURN_RES(val_res);
}

PHP_FUNCTION (wasm_val_f64) {
    double value;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_DOUBLE(value)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_t val = {.kind = WASM_F64, .of = {.f64 = value}};

    zend_resource *val_res;
    val_res = zend_register_resource(&val, le_wasm_val);

    RETURN_RES(val_res);
}

PHP_METHOD (Wasm_Vec_Val, __construct) {
    zend_array *vals_ht;
    zend_long size;
    zend_bool is_null = 1;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_ARRAY_HT_OR_LONG_OR_NULL(vals_ht, size, is_null)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_vec_c *wasm_val_vec = Z_WASM_VAL_VEC_P(ZEND_THIS);
    wasm_val_vec_t vec;

    if (is_null) {
        wasm_val_vec_new_empty(&vec);\
    } else if(vals_ht) {
        int len = zend_hash_num_elements(vals_ht);
        wasm_val_vec_new_uninitialized(&vec, len);

        zval *tmp;
        zend_ulong index;

        ZEND_HASH_REVERSE_FOREACH_NUM_KEY_VAL(vals_ht, index, tmp) {
                vec.data[index] = *((wasm_val_t*)Z_RES_P(tmp)->ptr);
        } ZEND_HASH_FOREACH_END();
    } else {
        wasm_val_vec_new_uninitialized(&vec, size);
    }

    wasm_val_vec->vec = vec;
}

PHP_METHOD (Wasm_Vec_Val, count) {
    ZEND_PARSE_PARAMETERS_NONE();

    wasm_val_vec_c *wasm_val_vec = Z_WASM_VAL_VEC_P(ZEND_THIS);

    RETURN_LONG(wasm_val_vec->vec.size);
}

PHP_METHOD (Wasm_Vec_Val, offsetExists) {
    zend_long offset;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_LONG(offset)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_vec_c *wasm_val_vec = Z_WASM_VAL_VEC_P(ZEND_THIS);

    if(offset >= wasm_val_vec->vec.size) {
        RETURN_FALSE;
    }

    RETURN_BOOL(offset < wasm_val_vec->vec.size);
}

PHP_METHOD (Wasm_Vec_Val, offsetGet) {
    zend_long offset;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_LONG(offset)
    ZEND_PARSE_PARAMETERS_END();

    wasm_val_vec_c *wasm_val_vec = Z_WASM_VAL_VEC_P(ZEND_THIS);

    if(offset >= wasm_val_vec->vec.size) {
        zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\Val::offsetGet($offset) index out of bounds");
    }
    if(&wasm_val_vec->vec.data[offset] == NULL) {
        RETURN_NULL();
    }
    zend_resource *extern_res;
    extern_res = zend_register_resource(&wasm_val_vec->vec.data[offset], le_wasm_val);

    RETURN_RES(extern_res);
}

PHP_METHOD (Wasm_Vec_Val, offsetSet) {
    zend_long offset;
    zval *val_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_LONG(offset)
            Z_PARAM_RESOURCE(val_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(val)

    wasm_val_vec_c *wasm_val_vec = Z_WASM_VAL_VEC_P(ZEND_THIS);

    if(offset >= wasm_val_vec->vec.size) {
        zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\Val::offsetSet($offset) index out of bounds");
    }

    wasm_val_vec->vec.data[offset] = *((wasm_val_t*)Z_RES_P(val_val)->ptr);
}

PHP_METHOD (Wasm_Vec_Val, offsetUnset) {\
    zend_throw_exception_ex(zend_ce_exception, 0, "Wasm\\Vec\\Val::offsetUnset($offset) not available");\
}
