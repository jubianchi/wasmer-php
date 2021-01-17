#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(global);

PHP_FUNCTION (wasm_global_new) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

WASMER_DELETE_RESOURCE(global)

PHP_FUNCTION (wasm_global_type) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_global_get) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

// TODO(jubianchi): Handle wasmer errors
PHP_FUNCTION (wasm_global_set) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

// TODO(jubianchi): Implement copy

PHP_FUNCTION (wasm_global_as_extern) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}
