#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(externtype)
WASMER_IMPORT_RESOURCE(limits)
WASMER_IMPORT_RESOURCE(memorytype)
WASMER_IMPORT_RESOURCE(valtype)

PHP_FUNCTION (wasm_memorytype_new) {
    zval *limits_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(limits_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(limits)

    wasm_memorytype_t *memorytype = wasm_memorytype_new(Z_RES_P(limits_val)->ptr);

    zend_resource *memorytype_res;
    memorytype_res = zend_register_resource((void *) memorytype, le_wasm_memorytype);

    RETURN_RES(memorytype_res);
}

WASMER_DELETE_WITHOUT_DTOR(memorytype)

PHP_FUNCTION (wasm_memorytype_limits) {
    zval *memorytype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(memorytype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(memorytype)

    const wasm_limits_t *limits = wasm_memorytype_limits(Z_RES_P(memorytype_val)->ptr);

    zend_resource *limits_res;
    limits_res = zend_register_resource((void *) limits, le_wasm_limits);

    RETURN_RES(limits_res);
}

WASMER_COPY(memorytype)

PHP_FUNCTION (wasm_memorytype_as_externtype) {
    zval *memorytype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(memorytype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(memorytype)

    wasm_externtype_t *externtype = wasm_memorytype_as_externtype(Z_RES_P(memorytype_val)->ptr);

    zend_resource *externtype_res;
    externtype_res = zend_register_resource((void *) externtype, le_wasm_externtype);

    RETURN_RES(externtype_res);
}

// TODO(jubianchi): Implement wasm_memorytype_vec_t