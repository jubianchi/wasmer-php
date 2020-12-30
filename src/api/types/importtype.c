#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(externtype)
WASMER_IMPORT_RESOURCE(importtype)

PHP_FUNCTION (wasm_importtype_new) {
    char *module;
    size_t module_len;
    char *name;
    size_t name_len;
    zval *externtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
            Z_PARAM_STRING(module, module_len)
            Z_PARAM_STRING(name, name_len)
            Z_PARAM_RESOURCE(externtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(externtype)

    wasm_name_t *module_vec = malloc(sizeof(wasm_name_t));
    module_vec->size = module_len;
    module_vec->data = module;

    wasm_name_t *name_vec = malloc(sizeof(wasm_name_t));
    name_vec->size = name_len;
    name_vec->data = name;

    wasm_importtype_t *importtype = wasm_importtype_new(module_vec, name_vec, Z_RES_P(externtype_val)->ptr);

    zend_resource *importtype_res;
    importtype_res = zend_register_resource((void *) importtype, le_wasm_importtype);

    RETURN_RES(importtype_res);
}

WASMER_DELETE_WITHOUT_DTOR(importtype)

PHP_FUNCTION (wasm_importtype_module) {
    zval *importtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(importtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(importtype)

    const wasm_name_t *module = wasm_importtype_module(Z_RES_P(importtype_val)->ptr);

    RETURN_STRINGL(module->data, module->size);
}

PHP_FUNCTION (wasm_importtype_name) {
    zval *importtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(importtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(importtype)

    const wasm_name_t *name = wasm_importtype_name(Z_RES_P(importtype_val)->ptr);

    RETURN_STRINGL(name->data, name->size);
}

PHP_FUNCTION (wasm_importtype_type) {
    zval *importtype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(importtype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(importtype)

    const wasm_externtype_t *externtype = wasm_importtype_type(Z_RES_P(importtype_val)->ptr);

    zend_resource *externtype_res;
    externtype_res = zend_register_resource((void *) externtype, le_wasm_externtype);

    RETURN_RES(externtype_res);
}

WASMER_COPY(importtype)

// TODO(jubianchi): Implement wasm_importtype_vec_t
