#include "php.h"

#include "wasm.h"

#include "macros.h"

WASMER_IMPORT_RESOURCE(engine)
WASMER_IMPORT_RESOURCE(store)

PHP_FUNCTION (wasm_store_new) {
    zval *engine_val;
    zend_resource *engine_res;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(engine_val)
    ZEND_PARSE_PARAMETERS_END();

    if ((engine_res = zend_fetch_resource(
            Z_RES_P(engine_val), le_wasm_engine_name, le_wasm_engine)) == NULL) {
        RETURN_THROWS();
    }

    wasm_store_t *store = wasm_store_new((wasm_engine_t *) engine_res);

    zend_resource *store_res;
    store_res = zend_register_resource((void *) store, le_wasm_store);

    RETURN_RES(store_res);
}

WASMER_DELETE_WITHOUT_DTOR(store)
