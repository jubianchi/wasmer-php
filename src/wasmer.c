#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "Zend/zend_interfaces.h"
#include "ext/standard/info.h"

#include "wasm.h"

#include "php_wasmer.h"
#include "wasmer_arginfo.h"
#include "macros.h"
#include "wasmer.h"

WASMER_RESOURCE_LE(config)
WASMER_RESOURCE(engine)
WASMER_RESOURCE_LE(exporttype)
WASMER_RESOURCE_LE(extern)
WASMER_RESOURCE_LE(externtype)
WASMER_RESOURCE_LE(foreign)
WASMER_RESOURCE_LE(frame)
WASMER_RESOURCE_LE(func)
WASMER_RESOURCE_LE(functype)
WASMER_RESOURCE_LE(global)
WASMER_RESOURCE_LE(globaltype)
WASMER_RESOURCE_LE(importtype)
WASMER_RESOURCE_LE(instance)
WASMER_RESOURCE_LE(limits)
WASMER_RESOURCE_LE(memory)
WASMER_RESOURCE_LE(memorytype)
WASMER_RESOURCE_LE(module)
WASMER_RESOURCE(store)
WASMER_RESOURCE_LE(table)
WASMER_RESOURCE_LE(tabletype)
WASMER_RESOURCE_LE(trap)
WASMER_RESOURCE_LE(val)
WASMER_RESOURCE_LE(valtype)

Z_WASMER_DECLARE_CE(valtype)
Z_WASMER_DECLARE_CE(globaltype)
Z_WASMER_DECLARE_CE(tabletype)
Z_WASMER_DECLARE_CE(memorytype)
Z_WASMER_DECLARE_CE(extern)
Z_WASMER_DECLARE_CE(externtype)
Z_WASMER_DECLARE_CE(importtype)
Z_WASMER_DECLARE_CE(exporttype)

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
    WASMER_RESOURCE_REGISTER(config)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(engine)
    WASMER_RESOURCE_REGISTER(exporttype)
    WASMER_RESOURCE_REGISTER(extern)
    WASMER_RESOURCE_REGISTER(externtype)
    WASMER_RESOURCE_REGISTER(foreign)
    WASMER_RESOURCE_REGISTER(frame)
    WASMER_RESOURCE_REGISTER(func)
    WASMER_RESOURCE_REGISTER(functype)
    WASMER_RESOURCE_REGISTER(global)
    WASMER_RESOURCE_REGISTER(globaltype)
    WASMER_RESOURCE_REGISTER(importtype)
    WASMER_RESOURCE_REGISTER(instance)
    WASMER_RESOURCE_REGISTER(limits)
    WASMER_RESOURCE_REGISTER(memorytype)
    WASMER_RESOURCE_REGISTER(memory)
    WASMER_RESOURCE_REGISTER(module)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(store)
    WASMER_RESOURCE_REGISTER(table)
    WASMER_RESOURCE_REGISTER(tabletype)
    WASMER_RESOURCE_REGISTER(trap)
    WASMER_RESOURCE_REGISTER(val)
    WASMER_RESOURCE_REGISTER(valtype)

    REGISTER_LONG_CONSTANT("WASM_I32", WASM_I32, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_I64", WASM_I64, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_F32", WASM_F32, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_F64", WASM_F64, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_ANYREF", WASM_ANYREF, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_FUNCREF", WASM_FUNCREF, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_CONST", WASM_CONST, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_VAR", WASM_VAR, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_EXTERN_FUNC", WASM_EXTERN_FUNC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_GLOBAL", WASM_EXTERN_GLOBAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_TABLE", WASM_EXTERN_TABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_MEMORY", WASM_EXTERN_MEMORY, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_LIMITS_MAX_DEFAULT", wasm_limits_max_default, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_MEMORY_PAGE_SIZE", MEMORY_PAGE_SIZE, CONST_CS | CONST_PERSISTENT);

    zend_class_entry ce;

    Z_WASMER_DECLARE_VEC_CLASS(ExportType, exporttype)
    Z_WASMER_DECLARE_VEC_CLASS(ExternType, externtype)
    Z_WASMER_DECLARE_VEC_CLASS(Extern, extern)
    Z_WASMER_DECLARE_VEC_CLASS(GlobalType, globaltype)
    Z_WASMER_DECLARE_VEC_CLASS(ImportType, importtype)
    Z_WASMER_DECLARE_VEC_CLASS(MemoryType, memorytype)
    Z_WASMER_DECLARE_VEC_CLASS(TableType, tabletype)
    Z_WASMER_DECLARE_VEC_CLASS(ValType, valtype)

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