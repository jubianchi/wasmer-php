#include "php.h"

#include "wasm.h"

extern int le_wasm_config;

PHP_FUNCTION (wasm_config_new) {
    ZEND_PARSE_PARAMETERS_NONE();

    wasm_config_t *config = wasm_config_new();

    zend_resource *config_res;
    config_res = zend_register_resource(config, le_wasm_config);

    RETURN_RES(config_res);
}
