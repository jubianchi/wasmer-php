#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasmer_wasm.h"

PHP_FUNCTION (wat2wasm) {
    char *wat;
    size_t wat_len;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_STRING(wat, wat_len)
    ZEND_PARSE_PARAMETERS_END();

    wasm_byte_vec_t *wat_vec = emalloc(sizeof(wasm_byte_vec_t));
    wat_vec->size = wat_len;
    wat_vec->data = wat;

    wasm_byte_vec_t *wasm_vec = emalloc(sizeof(wasm_byte_vec_t));;
    wat2wasm(wat_vec, wasm_vec);

    int error_length = wasmer_last_error_length();

    if (error_length > 0) {
        char buffer[error_length];
        wasmer_last_error_message(buffer, error_length);

        efree(wat_vec);
        efree(wasm_vec);

        zend_throw_exception_ex(zend_ce_exception, 0, "%s", buffer);

        return;
    }

    char *wasm = wasm_vec->data;
    int length = wasm_vec->size;

    efree(wat_vec);
    efree(wasm_vec);

    RETURN_STRINGL(wasm, length);
}
