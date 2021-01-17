#include "php.h"

#include "wasm.h"

#include "./macros.h"
#include "../wasmer.h"

WASMER_DECLARE_OWN(config)

PHP_FUNCTION (wasm_config_new) {
    ZEND_PARSE_PARAMETERS_NONE();

    wasmer_res *config = emalloc(sizeof(wasmer_res));
    config->inner.config = wasm_config_new();
    config->owned = true;

    zend_resource *config_res = zend_register_resource(config, le_wasm_config);

    RETURN_RES(config_res);
}
