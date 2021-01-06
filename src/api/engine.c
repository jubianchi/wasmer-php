#include "php.h"

#include "wasm.h"

#include "macros.h"

WASMER_IMPORT_RESOURCE(config)
WASMER_IMPORT_RESOURCE(engine)

PHP_FUNCTION (wasm_engine_new) {
    ZEND_PARSE_PARAMETERS_NONE();

    wasm_engine_t *engine = wasm_engine_new();

    zend_resource *engine_res;
    engine_res = zend_register_resource(engine, le_wasm_engine);

    RETURN_RES(engine_res);
}

PHP_FUNCTION (wasm_engine_new_with_config) {
    zval *config_val;
    zend_resource *config_res;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(config_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(config)

    wasm_engine_t *engine = wasm_engine_new_with_config(Z_RES_P(config_val)->ptr);

    zend_resource *engine_res;
    engine_res = zend_register_resource(engine, le_wasm_engine);

    RETURN_RES(engine_res);
}

PHP_FUNCTION (wasm_engine_delete) {
    zval *engine_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(engine_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(engine)

    zend_list_close(Z_RES_P(engine_val));

    RETURN_TRUE;
}
