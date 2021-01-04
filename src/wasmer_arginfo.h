/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 317baece6ad7fd63c75e9b136ce0aee64626c6bd */

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_config_new, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_wasm_engine_new arginfo_wasm_config_new

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_engine_new_with_config, 0, 0, 1)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_engine_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, engine)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_store_new, 0, 0, 1)
	ZEND_ARG_INFO(0, engine)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_store_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, store)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_valtype_new, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, kind, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_valtype_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, valtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_valtype_kind, 0, 1, IS_LONG, 0)
	ZEND_ARG_INFO(0, valtype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_valtype_is_num arginfo_wasm_valtype_delete

#define arginfo_wasm_valtype_is_ref arginfo_wasm_valtype_delete

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_valtype_copy, 0, 0, 1)
	ZEND_ARG_INFO(0, valtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_valkind_is_num, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, kind, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_wasm_valkind_is_ref arginfo_wasm_valkind_is_num

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_globaltype_new, 0, 0, 2)
	ZEND_ARG_INFO(0, valtype)
	ZEND_ARG_TYPE_INFO(0, mutability, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_globaltype_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, globaltype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_globaltype_content, 0, 0, 1)
	ZEND_ARG_INFO(0, globaltype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_globaltype_mutability, 0, 1, IS_LONG, 0)
	ZEND_ARG_INFO(0, globaltype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_globaltype_copy arginfo_wasm_globaltype_content

#define arginfo_wasm_globaltype_as_externtype arginfo_wasm_globaltype_content

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_limits_new, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, min, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, max, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_limits_min, 0, 1, IS_LONG, 0)
	ZEND_ARG_INFO(0, limits)
ZEND_END_ARG_INFO()

#define arginfo_wasm_limits_max arginfo_wasm_limits_min

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_tabletype_new, 0, 0, 2)
	ZEND_ARG_INFO(0, valtype)
	ZEND_ARG_INFO(0, limits)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_tabletype_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, tabletype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_tabletype_element, 0, 0, 1)
	ZEND_ARG_INFO(0, tabletype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_tabletype_limits arginfo_wasm_tabletype_element

#define arginfo_wasm_tabletype_copy arginfo_wasm_tabletype_element

#define arginfo_wasm_tabletype_as_externtype arginfo_wasm_tabletype_element

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_memorytype_new, 0, 0, 1)
	ZEND_ARG_INFO(0, limits)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_memorytype_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, memorytype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_memorytype_limits, 0, 0, 1)
	ZEND_ARG_INFO(0, memorytype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_memorytype_copy arginfo_wasm_memorytype_limits

#define arginfo_wasm_memorytype_as_externtype arginfo_wasm_memorytype_limits

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_externtype_kind, 0, 0, 1)
	ZEND_ARG_INFO(0, externtype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_externtype_as_functype arginfo_wasm_externtype_kind

#define arginfo_wasm_externtype_as_globaltype arginfo_wasm_externtype_kind

#define arginfo_wasm_externtype_as_tabletype arginfo_wasm_externtype_kind

#define arginfo_wasm_externtype_as_memorytype arginfo_wasm_externtype_kind

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_importtype_new, 0, 0, 3)
	ZEND_ARG_TYPE_INFO(0, module, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_INFO(0, externtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_importtype_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, importype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_importtype_module, 0, 1, IS_STRING, 0)
	ZEND_ARG_INFO(0, importype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_importtype_name arginfo_wasm_importtype_module

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_importtype_type, 0, 0, 1)
	ZEND_ARG_INFO(0, importype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_importtype_copy arginfo_wasm_importtype_type

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_exporttype_new, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_INFO(0, externtype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_exporttype_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, exportype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_exporttype_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_INFO(0, exportype)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_exporttype_type, 0, 0, 1)
	ZEND_ARG_INFO(0, exportype)
ZEND_END_ARG_INFO()

#define arginfo_wasm_exporttype_copy arginfo_wasm_exporttype_type

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_val_delete, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_INFO(0, val)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_wasm_val_copy, 0, 0, 1)
	ZEND_ARG_INFO(0, val)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_wasm_module_new, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

#define arginfo_wasm_module_delete arginfo_wasm_module_new

#define arginfo_wasm_module_validate arginfo_wasm_module_new

#define arginfo_wasm_module_imports arginfo_wasm_module_new

#define arginfo_wasm_module_exports arginfo_wasm_module_new

#define arginfo_wasm_module_serialize arginfo_wasm_module_new

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Wasm_Vec_ValType___construct, 0, 0, 0)
	ZEND_ARG_TYPE_MASK(0, sizeOrValtypes, MAY_BE_ARRAY|MAY_BE_LONG|MAY_BE_NULL, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Wasm_Vec_ValType_count, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Wasm_Vec_ValType_offsetExists, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Wasm_Vec_ValType_offsetGet, 0, 1, IS_MIXED, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Wasm_Vec_ValType_offsetSet, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_MIXED, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Wasm_Vec_ValType_offsetUnset, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Wasm_Vec_GlobalType___construct, 0, 0, 0)
	ZEND_ARG_TYPE_MASK(0, sizeOrGlobaltypes, MAY_BE_ARRAY|MAY_BE_LONG|MAY_BE_NULL, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_Wasm_Vec_GlobalType_count arginfo_class_Wasm_Vec_ValType_count

#define arginfo_class_Wasm_Vec_GlobalType_offsetExists arginfo_class_Wasm_Vec_ValType_offsetExists

#define arginfo_class_Wasm_Vec_GlobalType_offsetGet arginfo_class_Wasm_Vec_ValType_offsetGet

#define arginfo_class_Wasm_Vec_GlobalType_offsetSet arginfo_class_Wasm_Vec_ValType_offsetSet

#define arginfo_class_Wasm_Vec_GlobalType_offsetUnset arginfo_class_Wasm_Vec_ValType_offsetUnset


ZEND_FUNCTION(wasm_config_new);
ZEND_FUNCTION(wasm_engine_new);
ZEND_FUNCTION(wasm_engine_new_with_config);
ZEND_FUNCTION(wasm_engine_delete);
ZEND_FUNCTION(wasm_store_new);
ZEND_FUNCTION(wasm_store_delete);
ZEND_FUNCTION(wasm_valtype_new);
ZEND_FUNCTION(wasm_valtype_delete);
ZEND_FUNCTION(wasm_valtype_kind);
ZEND_FUNCTION(wasm_valtype_is_num);
ZEND_FUNCTION(wasm_valtype_is_ref);
ZEND_FUNCTION(wasm_valtype_copy);
ZEND_FUNCTION(wasm_valkind_is_num);
ZEND_FUNCTION(wasm_valkind_is_ref);
ZEND_FUNCTION(wasm_globaltype_new);
ZEND_FUNCTION(wasm_globaltype_delete);
ZEND_FUNCTION(wasm_globaltype_content);
ZEND_FUNCTION(wasm_globaltype_mutability);
ZEND_FUNCTION(wasm_globaltype_copy);
ZEND_FUNCTION(wasm_globaltype_as_externtype);
ZEND_FUNCTION(wasm_limits_new);
ZEND_FUNCTION(wasm_limits_min);
ZEND_FUNCTION(wasm_limits_max);
ZEND_FUNCTION(wasm_tabletype_new);
ZEND_FUNCTION(wasm_tabletype_delete);
ZEND_FUNCTION(wasm_tabletype_element);
ZEND_FUNCTION(wasm_tabletype_limits);
ZEND_FUNCTION(wasm_tabletype_copy);
ZEND_FUNCTION(wasm_tabletype_as_externtype);
ZEND_FUNCTION(wasm_memorytype_new);
ZEND_FUNCTION(wasm_memorytype_delete);
ZEND_FUNCTION(wasm_memorytype_limits);
ZEND_FUNCTION(wasm_memorytype_copy);
ZEND_FUNCTION(wasm_memorytype_as_externtype);
ZEND_FUNCTION(wasm_externtype_kind);
ZEND_FUNCTION(wasm_externtype_as_functype);
ZEND_FUNCTION(wasm_externtype_as_globaltype);
ZEND_FUNCTION(wasm_externtype_as_tabletype);
ZEND_FUNCTION(wasm_externtype_as_memorytype);
ZEND_FUNCTION(wasm_importtype_new);
ZEND_FUNCTION(wasm_importtype_delete);
ZEND_FUNCTION(wasm_importtype_module);
ZEND_FUNCTION(wasm_importtype_name);
ZEND_FUNCTION(wasm_importtype_type);
ZEND_FUNCTION(wasm_importtype_copy);
ZEND_FUNCTION(wasm_exporttype_new);
ZEND_FUNCTION(wasm_exporttype_delete);
ZEND_FUNCTION(wasm_exporttype_name);
ZEND_FUNCTION(wasm_exporttype_type);
ZEND_FUNCTION(wasm_exporttype_copy);
ZEND_FUNCTION(wasm_val_delete);
ZEND_FUNCTION(wasm_val_copy);
ZEND_FUNCTION(wasm_module_new);
ZEND_FUNCTION(wasm_module_delete);
ZEND_FUNCTION(wasm_module_validate);
ZEND_FUNCTION(wasm_module_imports);
ZEND_FUNCTION(wasm_module_exports);
ZEND_FUNCTION(wasm_module_serialize);
ZEND_METHOD(Wasm_Vec_ValType, __construct);
ZEND_METHOD(Wasm_Vec_ValType, count);
ZEND_METHOD(Wasm_Vec_ValType, offsetExists);
ZEND_METHOD(Wasm_Vec_ValType, offsetGet);
ZEND_METHOD(Wasm_Vec_ValType, offsetSet);
ZEND_METHOD(Wasm_Vec_ValType, offsetUnset);
ZEND_METHOD(Wasm_Vec_GlobalType, __construct);
ZEND_METHOD(Wasm_Vec_GlobalType, count);
ZEND_METHOD(Wasm_Vec_GlobalType, offsetExists);
ZEND_METHOD(Wasm_Vec_GlobalType, offsetGet);
ZEND_METHOD(Wasm_Vec_GlobalType, offsetSet);
ZEND_METHOD(Wasm_Vec_GlobalType, offsetUnset);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(wasm_config_new, arginfo_wasm_config_new)
	ZEND_FE(wasm_engine_new, arginfo_wasm_engine_new)
	ZEND_FE(wasm_engine_new_with_config, arginfo_wasm_engine_new_with_config)
	ZEND_FE(wasm_engine_delete, arginfo_wasm_engine_delete)
	ZEND_FE(wasm_store_new, arginfo_wasm_store_new)
	ZEND_FE(wasm_store_delete, arginfo_wasm_store_delete)
	ZEND_FE(wasm_valtype_new, arginfo_wasm_valtype_new)
	ZEND_FE(wasm_valtype_delete, arginfo_wasm_valtype_delete)
	ZEND_FE(wasm_valtype_kind, arginfo_wasm_valtype_kind)
	ZEND_FE(wasm_valtype_is_num, arginfo_wasm_valtype_is_num)
	ZEND_FE(wasm_valtype_is_ref, arginfo_wasm_valtype_is_ref)
	ZEND_FE(wasm_valtype_copy, arginfo_wasm_valtype_copy)
	ZEND_FE(wasm_valkind_is_num, arginfo_wasm_valkind_is_num)
	ZEND_FE(wasm_valkind_is_ref, arginfo_wasm_valkind_is_ref)
	ZEND_FE(wasm_globaltype_new, arginfo_wasm_globaltype_new)
	ZEND_FE(wasm_globaltype_delete, arginfo_wasm_globaltype_delete)
	ZEND_FE(wasm_globaltype_content, arginfo_wasm_globaltype_content)
	ZEND_FE(wasm_globaltype_mutability, arginfo_wasm_globaltype_mutability)
	ZEND_FE(wasm_globaltype_copy, arginfo_wasm_globaltype_copy)
	ZEND_FE(wasm_globaltype_as_externtype, arginfo_wasm_globaltype_as_externtype)
	ZEND_FE(wasm_limits_new, arginfo_wasm_limits_new)
	ZEND_FE(wasm_limits_min, arginfo_wasm_limits_min)
	ZEND_FE(wasm_limits_max, arginfo_wasm_limits_max)
	ZEND_FE(wasm_tabletype_new, arginfo_wasm_tabletype_new)
	ZEND_FE(wasm_tabletype_delete, arginfo_wasm_tabletype_delete)
	ZEND_FE(wasm_tabletype_element, arginfo_wasm_tabletype_element)
	ZEND_FE(wasm_tabletype_limits, arginfo_wasm_tabletype_limits)
	ZEND_FE(wasm_tabletype_copy, arginfo_wasm_tabletype_copy)
	ZEND_FE(wasm_tabletype_as_externtype, arginfo_wasm_tabletype_as_externtype)
	ZEND_FE(wasm_memorytype_new, arginfo_wasm_memorytype_new)
	ZEND_FE(wasm_memorytype_delete, arginfo_wasm_memorytype_delete)
	ZEND_FE(wasm_memorytype_limits, arginfo_wasm_memorytype_limits)
	ZEND_FE(wasm_memorytype_copy, arginfo_wasm_memorytype_copy)
	ZEND_FE(wasm_memorytype_as_externtype, arginfo_wasm_memorytype_as_externtype)
	ZEND_FE(wasm_externtype_kind, arginfo_wasm_externtype_kind)
	ZEND_FE(wasm_externtype_as_functype, arginfo_wasm_externtype_as_functype)
	ZEND_FE(wasm_externtype_as_globaltype, arginfo_wasm_externtype_as_globaltype)
	ZEND_FE(wasm_externtype_as_tabletype, arginfo_wasm_externtype_as_tabletype)
	ZEND_FE(wasm_externtype_as_memorytype, arginfo_wasm_externtype_as_memorytype)
	ZEND_FE(wasm_importtype_new, arginfo_wasm_importtype_new)
	ZEND_FE(wasm_importtype_delete, arginfo_wasm_importtype_delete)
	ZEND_FE(wasm_importtype_module, arginfo_wasm_importtype_module)
	ZEND_FE(wasm_importtype_name, arginfo_wasm_importtype_name)
	ZEND_FE(wasm_importtype_type, arginfo_wasm_importtype_type)
	ZEND_FE(wasm_importtype_copy, arginfo_wasm_importtype_copy)
	ZEND_FE(wasm_exporttype_new, arginfo_wasm_exporttype_new)
	ZEND_FE(wasm_exporttype_delete, arginfo_wasm_exporttype_delete)
	ZEND_FE(wasm_exporttype_name, arginfo_wasm_exporttype_name)
	ZEND_FE(wasm_exporttype_type, arginfo_wasm_exporttype_type)
	ZEND_FE(wasm_exporttype_copy, arginfo_wasm_exporttype_copy)
	ZEND_FE(wasm_val_delete, arginfo_wasm_val_delete)
	ZEND_FE(wasm_val_copy, arginfo_wasm_val_copy)
	ZEND_FE(wasm_module_new, arginfo_wasm_module_new)
	ZEND_FE(wasm_module_delete, arginfo_wasm_module_delete)
	ZEND_FE(wasm_module_validate, arginfo_wasm_module_validate)
	ZEND_FE(wasm_module_imports, arginfo_wasm_module_imports)
	ZEND_FE(wasm_module_exports, arginfo_wasm_module_exports)
	ZEND_FE(wasm_module_serialize, arginfo_wasm_module_serialize)
	ZEND_FE_END
};


static const zend_function_entry class_Wasm_Vec_ValType_methods[] = {
	ZEND_ME(Wasm_Vec_ValType, __construct, arginfo_class_Wasm_Vec_ValType___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_ValType, count, arginfo_class_Wasm_Vec_ValType_count, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_ValType, offsetExists, arginfo_class_Wasm_Vec_ValType_offsetExists, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_ValType, offsetGet, arginfo_class_Wasm_Vec_ValType_offsetGet, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_ValType, offsetSet, arginfo_class_Wasm_Vec_ValType_offsetSet, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_ValType, offsetUnset, arginfo_class_Wasm_Vec_ValType_offsetUnset, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Wasm_Vec_GlobalType_methods[] = {
	ZEND_ME(Wasm_Vec_GlobalType, __construct, arginfo_class_Wasm_Vec_GlobalType___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_GlobalType, count, arginfo_class_Wasm_Vec_GlobalType_count, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_GlobalType, offsetExists, arginfo_class_Wasm_Vec_GlobalType_offsetExists, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_GlobalType, offsetGet, arginfo_class_Wasm_Vec_GlobalType_offsetGet, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_GlobalType, offsetSet, arginfo_class_Wasm_Vec_GlobalType_offsetSet, ZEND_ACC_PUBLIC)
	ZEND_ME(Wasm_Vec_GlobalType, offsetUnset, arginfo_class_Wasm_Vec_GlobalType_offsetUnset, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
