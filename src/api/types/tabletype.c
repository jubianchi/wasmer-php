#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(externtype)
WASMER_IMPORT_RESOURCE(limits)
WASMER_IMPORT_RESOURCE(tabletype)
WASMER_IMPORT_RESOURCE(valtype)

PHP_FUNCTION (wasm_tabletype_new) {
    zval *valtype_val;
    zval *limits_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_RESOURCE(valtype_val)
            Z_PARAM_RESOURCE(limits_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(valtype)
    WASMER_FETCH_RESOURCE(limits)

    wasm_tabletype_t *tabletype = wasm_tabletype_new(Z_RES_P(valtype_val)->ptr, Z_RES_P(limits_val)->ptr);

    zend_resource *tabletype_res;
    tabletype_res = zend_register_resource((void *) tabletype, le_wasm_tabletype);

    RETURN_RES(tabletype_res);
}

WASMER_DELETE_WITHOUT_DTOR(tabletype)

PHP_FUNCTION (wasm_tabletype_element) {
    zval *tabletype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(tabletype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(tabletype)

    const wasm_valtype_t *valtype = wasm_tabletype_element(Z_RES_P(tabletype_val)->ptr);

    zend_resource *valtype_res;
    valtype_res = zend_register_resource((void *) valtype, le_wasm_valtype);

    RETURN_RES(valtype_res);
}

PHP_FUNCTION (wasm_tabletype_limits) {
    zval *tabletype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(tabletype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(tabletype)

    const wasm_limits_t *limits = wasm_tabletype_limits(Z_RES_P(tabletype_val)->ptr);

    zend_resource *limits_res;
    limits_res = zend_register_resource((void *) limits, le_wasm_limits);

    RETURN_RES(limits_res);
}

WASMER_COPY(tabletype)

PHP_FUNCTION (wasm_tabletype_as_externtype) {
    zval *tabletype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(tabletype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(tabletype)

    wasm_externtype_t *externtype = wasm_tabletype_as_externtype(Z_RES_P(tabletype_val)->ptr);

    zend_resource *externtype_res;
    externtype_res = zend_register_resource((void *) externtype, le_wasm_externtype);

    RETURN_RES(externtype_res);
}

// TODO(jubianchi): Implement wasm_tabletype_vec_t