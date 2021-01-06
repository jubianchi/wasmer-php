#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(instance)

// TODO(jubianchi): Handle wasmer errors
PHP_FUNCTION (wasm_instance_new) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

WASMER_DELETE_WITHOUT_DTOR(instance)

PHP_FUNCTION (wasm_instance_exports) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

WASMER_COPY(instance)
