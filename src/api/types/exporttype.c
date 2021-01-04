#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(externtype)
WASMER_IMPORT_RESOURCE(exporttype)

WASMER_DECLARE_TYPE(ExportType, EXPORTTYPE, exporttype)

PHP_FUNCTION (wasm_exporttype_new) {
    char *name;
    size_t name_len;
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_STRING(name, name_len)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    wasm_name_t *name_vec = malloc(sizeof(wasm_name_t));
    name_vec->size = name_len;
    name_vec->data = name;

    wasm_exporttype_t *exporttype = wasm_exporttype_new(name_vec, Z_RES_P(externtype_val)->ptr);

    zend_resource *exporttype_res;
    exporttype_res = zend_register_resource((void *) exporttype, le_wasm_exporttype);

    RETURN_RES(exporttype_res);
}

PHP_FUNCTION (wasm_exporttype_name) {
    zval *exporttype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(exporttype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(exporttype)

    const wasm_name_t *name = wasm_exporttype_name(Z_RES_P(exporttype_val)->ptr);

    RETURN_STRINGL(name->data, name->size);
}

PHP_FUNCTION (wasm_exporttype_type) {
    zval *exporttype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(exporttype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(exporttype)

    const wasm_externtype_t *externtype = wasm_exporttype_type(Z_RES_P(exporttype_val)->ptr);

    zend_resource *externtype_res;
    externtype_res = zend_register_resource((void *) externtype, le_wasm_externtype);

    RETURN_RES(externtype_res);
}
