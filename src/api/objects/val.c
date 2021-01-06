#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(val)

WASMER_DELETE_WITHOUT_DTOR(val)

// TODO(jubianchi): Handle wasmer errors
PHP_FUNCTION (wasm_val_copy) {
    zval *val_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(val_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(val)

    wasm_val_t val;
    wasm_val_copy(&val, Z_RES_P(val_val)->ptr);

    zend_resource *val_res;
    val_res = zend_register_resource(&val, le_wasm_val);

    RETURN_RES(val_res);
}

// TODO(jubianchi): Implement wasm_val_vec_t
