#include "php.h"

#include "wasm.h"

#include "macros.h"

WASMER_IMPORT_RESOURCE(engine)
WASMER_IMPORT_RESOURCE(store)

PHP_FUNCTION (wasm_store_new) {
    zval *engine_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(engine_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(engine)

    wasm_store_t *store = wasm_store_new(Z_RES_P(engine_val)->ptr);

    zend_resource *store_res;
    store_res = zend_register_resource(store, le_wasm_store);

    RETURN_RES(store_res);
}

WASMER_DELETE_WITHOUT_DTOR(store)
