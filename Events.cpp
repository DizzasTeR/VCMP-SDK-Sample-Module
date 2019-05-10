#include "pch.h"

extern PluginFuncs* g_Funcs;
extern PluginCallbacks* g_Calls;
extern PluginInfo* g_Info;

extern HSQUIRRELVM sqvm;
extern HSQAPI sqapi;

void OnSquirrelScriptLoad() {
	size_t size;
	int32_t sqID = g_Funcs->FindPlugin("SQHost2");
	const void** sqExports = g_Funcs->GetPluginExports(sqID, &size);
	if(sqExports != NULL && size > 0) {
		SquirrelImports* sqFuncs = (SquirrelImports*)(*sqExports);
		if(sqFuncs) {
			sqvm = *sqFuncs->GetSquirrelVM();
			sqapi = *sqFuncs->GetSquirrelAPI();
		}
	}
}

uint8_t OnInternalCommand(uint32_t uCmdType, const char* pszText) {
	switch(uCmdType) {
	case 0x7D6E22D8:
		OnSquirrelScriptLoad();
		break;

	default:
		break;
	}
	return 1;
}