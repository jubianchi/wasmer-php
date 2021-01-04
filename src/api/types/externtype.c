#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(externtype)
WASMER_IMPORT_RESOURCE(functype)
WASMER_IMPORT_RESOURCE(globaltype)
WASMER_IMPORT_RESOURCE(memorytype)
WASMER_IMPORT_RESOURCE(tabletype)

WASMER_DECLARE_TYPE(ExternType, EXTERNTYPE, externtype)

PHP_FUNCTION (wasm_externtype_kind) {
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    int kind = wasm_externtype_kind(Z_RES_P(externtype_val)->ptr);

    RETURN_LONG(kind);
}

PHP_FUNCTION (wasm_externtype_as_functype) {
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    wasm_functype_t *functype = wasm_externtype_as_functype(Z_RES_P(externtype_val)->ptr);

    zend_resource *functype_res;
    functype_res = zend_register_resource((void *) functype, le_wasm_functype);

    RETURN_RES(functype_res);
}

PHP_FUNCTION (wasm_externtype_as_globaltype) {
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    wasm_globaltype_t *globaltype = wasm_externtype_as_globaltype(Z_RES_P(externtype_val)->ptr);

    zend_resource *globaltype_res;
    globaltype_res = zend_register_resource((void *) globaltype, le_wasm_globaltype);

    RETURN_RES(globaltype_res);
}

PHP_FUNCTION (wasm_externtype_as_memorytype) {
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    wasm_memorytype_t *memorytype = wasm_externtype_as_memorytype(Z_RES_P(externtype_val)->ptr);

    zend_resource *memorytype_res;
    memorytype_res = zend_register_resource((void *) memorytype, le_wasm_memorytype);

    RETURN_RES(memorytype_res);
}

PHP_FUNCTION (wasm_externtype_as_tabletype) {
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    wasm_tabletype_t *tabletype = wasm_externtype_as_tabletype(Z_RES_P(externtype_val)->ptr);

    zend_resource *tabletype_res;
    tabletype_res = zend_register_resource((void *) tabletype, le_wasm_tabletype);

    RETURN_RES(tabletype_res);
}
