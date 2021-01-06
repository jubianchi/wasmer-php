#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasmer_wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(store)

WASMER_DECLARE_OWN(module)

extern zend_class_entry *wasm_vec_importtype_ce;
extern zend_class_entry *wasm_vec_exporttype_ce;

PHP_FUNCTION (wasm_module_new) {
    zval *store_val;
    char *wasm;
    size_t wasm_len;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_RESOURCE(store_val)
            Z_PARAM_STRING(wasm, wasm_len)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(store)

    wasm_store_t *store = Z_RES_P(store_val)->ptr;

    wasm_byte_vec_t *wasm_vec = emalloc(sizeof(wasm_byte_vec_t));;
    wasm_vec->size = wasm_len;
    wasm_vec->data = wasm;

    wasm_module_t *module = wasm_module_new(store, wasm_vec);

    int error_length = wasmer_last_error_length();

    if (error_length > 0) {
        char buffer[error_length];
        wasmer_last_error_message(buffer, error_length);

        efree(wasm_vec);

        zend_throw_exception_ex(zend_ce_exception, 0, "%s", buffer);

        return;
    }

    zend_resource *module_res;
    module_res = zend_register_resource(module, le_wasm_module);

    efree(wasm_vec);

    RETURN_RES(module_res);
}

PHP_FUNCTION (wasm_module_validate) {
    zval *store_val;
    char *wasm;
    size_t wasm_len;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_RESOURCE(store_val)
            Z_PARAM_STRING(wasm, wasm_len)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(store)

    wasm_store_t *store = Z_RES_P(store_val)->ptr;

    wasm_byte_vec_t *wasm_vec = emalloc(sizeof(wasm_byte_vec_t));;
    wasm_vec->size = wasm_len;
    wasm_vec->data = wasm;

    bool valid = wasm_module_validate(store, wasm_vec);

    int error_length = wasmer_last_error_length();

    if (error_length > 0) {
        char buffer[error_length];
        wasmer_last_error_message(buffer, error_length);

        efree(wasm_vec);

        zend_throw_exception_ex(zend_ce_exception, 0, "%s", buffer);

        return;
    }

    efree(wasm_vec);

    RETURN_BOOL(valid);
}

PHP_FUNCTION (wasm_module_imports) {
    zval *module_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(module_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(module)

    wasm_module_t *module = Z_RES_P(module_val)->ptr;

    wasm_importtype_vec_t *importtypes = emalloc(sizeof(wasm_exporttype_vec_t));
    wasm_module_imports(module, importtypes);

    zval obj;
    object_init_ex(&obj, wasm_vec_importtype_ce);
    wasm_importtype_vec_c *ce = Z_WASM_IMPORTTYPE_VEC_P(&obj);
    ce->vec = *importtypes;

    efree(importtypes);

    RETURN_OBJ(Z_OBJ(obj));
}

PHP_FUNCTION (wasm_module_exports) {
    zval *module_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(module_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(module)

    wasm_module_t *module = Z_RES_P(module_val)->ptr;

    wasm_exporttype_vec_t *exporttypes = emalloc(sizeof(wasm_exporttype_vec_t));
    wasm_module_exports(module, exporttypes);

    zval obj;
    object_init_ex(&obj, wasm_vec_exporttype_ce);
    wasm_exporttype_vec_c *ce = Z_WASM_EXPORTTYPE_VEC_P(&obj);
    ce->vec = *exporttypes;

    efree(exporttypes);

    RETURN_OBJ(Z_OBJ(obj));
}

PHP_FUNCTION (wasm_module_serialize) {
    zval *module_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(module_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(module)

    wasm_module_t *module = Z_RES_P(module_val)->ptr;

    wasm_byte_vec_t *byte_vec = emalloc(sizeof(wasm_byte_vec_t));
    wasm_module_serialize(module, byte_vec);

    char *name = byte_vec->data;
    int length = byte_vec->size;

    efree(byte_vec);

    RETURN_STRINGL(name, length);
}

PHP_FUNCTION (wasm_module_deserialize) {
    zval *store_val;
    char *wasm;
    size_t wasm_len;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_RESOURCE(store_val)
            Z_PARAM_STRING(wasm, wasm_len)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(store)

    wasm_store_t *store = Z_RES_P(store_val)->ptr;

    wasm_byte_vec_t *wasm_vec = emalloc(sizeof(wasm_byte_vec_t));;
    wasm_vec->size = wasm_len;
    wasm_vec->data = wasm;

    wasm_module_t *module = wasm_module_deserialize(store, wasm_vec);

    int error_length = wasmer_last_error_length();

    if (error_length > 0) {
        char buffer[error_length];
        wasmer_last_error_message(buffer, error_length);

        efree(wasm_vec);

        zend_throw_exception_ex(zend_ce_exception, 0, "%s", buffer);

        return;
    }

    zend_resource *module_res;
    module_res = zend_register_resource(module, le_wasm_module);

    efree(wasm_vec);

    RETURN_RES(module_res);
}

PHP_FUNCTION (wasm_module_name) {
    zval *module_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(module_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(module)

    wasm_module_t *module = Z_RES_P(module_val)->ptr;

    wasm_byte_vec_t *name_vec = emalloc(sizeof(wasm_byte_vec_t));
    wasm_module_name(module, name_vec);

    char *name = name_vec->data;
    int length = name_vec->size;

    efree(name_vec);

    RETURN_STRINGL(name, length);
}

PHP_FUNCTION (wasm_module_set_name) {
    zval *module_val;
    char *name;
    size_t name_len;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_RESOURCE(module_val)
            Z_PARAM_STRING(name, name_len)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(module)

    wasm_module_t *module = Z_RES_P(module_val)->ptr;

    wasm_byte_vec_t *name_vec = emalloc(sizeof(wasm_byte_vec_t));
    name_vec->size = name_len;
    name_vec->data = name;

    bool result = wasm_module_set_name(module, name_vec);

    efree(name_vec);

    RETURN_BOOL(result);
}

WASMER_COPY(module)
