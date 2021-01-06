#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(limits)

PHP_FUNCTION (wasm_limits_new) {
    zval *min_val;
    zval *max_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_NUMBER(min_val)
            Z_PARAM_NUMBER(max_val)
    ZEND_PARSE_PARAMETERS_END();

    int min = zval_get_double(min_val);
    int max = zval_get_double(max_val);
    wasm_limits_t *limits = malloc(sizeof(wasm_limits_t));
    limits->min = min;
    limits->max = max;

    zend_resource *limits_res;
    limits_res = zend_register_resource(limits, le_wasm_limits);

    RETURN_RES(limits_res);
}

PHP_FUNCTION (wasm_limits_min) {
    zval *limits_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(limits_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(limits)

    wasm_limits_t *limits = Z_RES_P(limits_val)->ptr;

    RETURN_LONG(limits->min);
}

PHP_FUNCTION (wasm_limits_max) {
    zval *limits_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(limits_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(limits)

    wasm_limits_t *limits = Z_RES_P(limits_val)->ptr;

    RETURN_LONG(limits->max);
}