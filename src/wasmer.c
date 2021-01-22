#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "Zend/zend_interfaces.h"
#include "ext/standard/info.h"

#include "wasmer_wasm.h"

#include "php_wasmer.h"
#include "wasmer_arginfo.h"
#include "macros.h"
#include "wasmer.h"

///////////////////////////////////////////////////////////////////////////////
// Runtime Environment

WASMER_RESOURCE_LE(config)
static ZEND_RSRC_DTOR_FUNC(wasm_config_dtor) { \
    efree(res->ptr);
}
WASMER_RESOURCE(engine)
WASMER_RESOURCE(store)

///////////////////////////////////////////////////////////////////////////////
// Type Representations

WASMER_RESOURCE(valtype)
Z_WASMER_DECLARE_CE(valtype)
WASMER_RESOURCE(functype)
Z_WASMER_DECLARE_CE(functype)
WASMER_RESOURCE(globaltype)
Z_WASMER_DECLARE_CE(globaltype)
// TODO(jubianchi): limits
WASMER_RESOURCE_LE(limits)
WASMER_RESOURCE(tabletype)
Z_WASMER_DECLARE_CE(tabletype)
WASMER_RESOURCE(memorytype)
Z_WASMER_DECLARE_CE(memorytype)
WASMER_RESOURCE(externtype)
Z_WASMER_DECLARE_CE(externtype)
WASMER_RESOURCE(importtype)
Z_WASMER_DECLARE_CE(importtype)
WASMER_RESOURCE(exporttype)
Z_WASMER_DECLARE_CE(exporttype)

///////////////////////////////////////////////////////////////////////////////
// Runtime Objects

WASMER_RESOURCE(module)
WASMER_RESOURCE_LE(extern)
static ZEND_RSRC_DTOR_FUNC(wasm_extern_dtor) {
    wasmer_res *extern_res = (wasmer_res*)res->ptr;
    wasm_extern_t *wasm_extern = extern_res->inner.xtern;

    if (extern_res->owned) {
        wasm_extern_delete(wasm_extern);
    }

    if (res->ptr != NULL) {
        efree(res->ptr);
    }
}
Z_WASMER_DECLARE_CE(extern)

WASMER_RESOURCE_LE(foreign)
WASMER_RESOURCE_LE(frame)
WASMER_RESOURCE(func)
WASMER_RESOURCE_LE(global)
WASMER_RESOURCE(instance)
WASMER_RESOURCE_LE(memory)
WASMER_RESOURCE_LE(table)
WASMER_RESOURCE_LE(trap)
WASMER_RESOURCE_LE(val)
static ZEND_RSRC_DTOR_FUNC(wasm_val_dtor) {
    wasmer_res *val_res = (wasmer_res*)res->ptr;
    wasm_val_t wasm_val = val_res->inner.val;

    if (val_res->owned) {
        wasm_val_delete(&wasm_val);
    }

    if (res->ptr != NULL) {
        efree(res->ptr);
    }
}
Z_WASMER_DECLARE_CE(val)

/*
static zend_class_entry* fetch_internal_class(const char* class_name)
{
    zend_class_entry* ce;

    if ((ce = zend_hash_str_find_ptr(CG(class_table), class_name, strlen(class_name)))) {
        return ce;
    }

    return NULL;
}
*/

PHP_MINIT_FUNCTION (wasmer) {
    zend_class_entry ce;

    ///////////////////////////////////////////////////////////////////////////////
    // Runtime Environment

    WASMER_RESOURCE_REGISTER_WITH_DTOR(config)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(engine)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(store)

    ///////////////////////////////////////////////////////////////////////////////
    // Type Representations

    WASMER_RESOURCE_REGISTER_WITH_DTOR(valtype)
    Z_WASMER_DECLARE_VEC_CLASS(ValType, valtype)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(functype)
    Z_WASMER_DECLARE_VEC_CLASS(FuncType, functype)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(globaltype)
    Z_WASMER_DECLARE_VEC_CLASS(GlobalType, globaltype)
    // TODO(jubianchi): limits
    WASMER_RESOURCE_REGISTER(limits)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(tabletype)
    Z_WASMER_DECLARE_VEC_CLASS(TableType, tabletype)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(memorytype)
    Z_WASMER_DECLARE_VEC_CLASS(MemoryType, memorytype)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(externtype)
    Z_WASMER_DECLARE_VEC_CLASS(ExternType, externtype)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(importtype)
    Z_WASMER_DECLARE_VEC_CLASS(ImportType, importtype)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(exporttype)
    Z_WASMER_DECLARE_VEC_CLASS(ExportType, exporttype)

    ///////////////////////////////////////////////////////////////////////////////
    // Runtime Objects

    WASMER_RESOURCE_REGISTER_WITH_DTOR(val)
    Z_WASMER_DECLARE_VEC_CLASS(Val, val)
    // TODO(jubianchi): references
    WASMER_RESOURCE_REGISTER(frame)
    WASMER_RESOURCE_REGISTER(trap)
    WASMER_RESOURCE_REGISTER(foreign)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(module)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(func)
    WASMER_RESOURCE_REGISTER(global)
    WASMER_RESOURCE_REGISTER(table)
    WASMER_RESOURCE_REGISTER(memory)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(extern)
    Z_WASMER_DECLARE_VEC_CLASS(Extern, extern)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(instance)

    ///////////////////////////////////////////////////////////////////////////////
    // Type Representations

    // Type attributes
    REGISTER_LONG_CONSTANT("WASM_CONST", WASM_CONST, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_VAR", WASM_VAR, CONST_CS | CONST_PERSISTENT);

    // Value Types
    REGISTER_LONG_CONSTANT("WASM_I32", WASM_I32, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_I64", WASM_I64, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_F32", WASM_F32, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_F64", WASM_F64, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_ANYREF", WASM_ANYREF, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_FUNCREF", WASM_FUNCREF, CONST_CS | CONST_PERSISTENT);

    // Extern Types
    REGISTER_LONG_CONSTANT("WASM_EXTERN_FUNC", WASM_EXTERN_FUNC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_GLOBAL", WASM_EXTERN_GLOBAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_TABLE", WASM_EXTERN_TABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_MEMORY", WASM_EXTERN_MEMORY, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_LIMITS_MAX_DEFAULT", wasm_limits_max_default, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_MEMORY_PAGE_SIZE", MEMORY_PAGE_SIZE, CONST_CS | CONST_PERSISTENT);

    return SUCCESS;
}

PHP_RINIT_FUNCTION(wasmer) {
#if defined(ZTS) && defined(COMPILE_DL_WASMER)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(wasmer) {
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(wasmer) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION (wasmer) {
    php_info_print_table_start();
    php_info_print_table_header(2, "Wasmer support", "enabled");
    php_info_print_table_header(2, "Wasmer version", wasmer_version());
    php_info_print_table_end();
}

zend_module_entry wasmer_module_entry = {
        STANDARD_MODULE_HEADER,
        "wasmer",
        ext_functions,
        PHP_MINIT(wasmer),
        PHP_MSHUTDOWN(wasmer),
        PHP_RINIT(wasmer),
        PHP_RSHUTDOWN(wasmer),
        PHP_MINFO(wasmer),
        PHP_WASMER_VERSION,
        STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_WASMER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wasmer)
#endif