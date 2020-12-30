#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(externtype)
WASMER_IMPORT_RESOURCE(globaltype)
WASMER_IMPORT_RESOURCE(valtype)

PHP_FUNCTION (wasm_globaltype_new) {
    zval *valtype_val;
    zval *mutability_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_RESOURCE(valtype_val)
            Z_PARAM_NUMBER(mutability_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(valtype)

    int mutability = zval_get_long(mutability_val);

    wasm_globaltype_t *globaltype = wasm_globaltype_new(Z_RES_P(valtype_val)->ptr, mutability);

    zend_resource *globaltype_res;
    globaltype_res = zend_register_resource((void *) globaltype, le_wasm_globaltype);

    RETURN_RES(globaltype_res);
}

WASMER_DELETE_WITHOUT_DTOR(globaltype)

PHP_FUNCTION (wasm_globaltype_content) {
    zval *globaltype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(globaltype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(globaltype)

    const wasm_valtype_t *valtype = wasm_globaltype_content(Z_RES_P(globaltype_val)->ptr);

    zend_resource *valtype_res;
    valtype_res = zend_register_resource((void *) valtype, le_wasm_valtype);

    RETURN_RES(valtype_res);
}

PHP_FUNCTION (wasm_globaltype_mutability) {
    zval *globaltype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(globaltype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(globaltype)

    int mutability = wasm_globaltype_mutability(Z_RES_P(globaltype_val)->ptr);

    RETURN_LONG(mutability);
}

WASMER_COPY(globaltype)

PHP_FUNCTION (wasm_globaltype_as_externtype) {
    zval *globaltype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(globaltype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(globaltype)

    const wasm_externtype_t *externtype = wasm_globaltype_as_externtype(Z_RES_P(globaltype_val)->ptr);

    zend_resource *externtype_res;
    externtype_res = zend_register_resource((void *) externtype, le_wasm_externtype);

    RETURN_RES(externtype_res);
}

// TODO(jubianchi): Implement wasm_globaltype_vec_t
