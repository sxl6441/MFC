function LoadToolkitDll(application_id) {
    if (application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
}

function RetrieveSpecifiedAppID(application_id, app_name)
{
    if (application_id == "" || application_id == null || application_id == undefined ||
        app_name == "" || app_name == null || app_name == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    
    var argument = pfcCreate("pfcArgument").Create("appid_tag", pfcCreate("MpfcArgument").CreateStringArgValue(app_name));
    var arguments = pfcCreate("pfcArguments");
    
    arguments.Append(argument);
    
    var func_return = dll.ExecuteFunction("RetrieveAppID", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "app_id") {
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;    
}

//恢复工艺路线装配
function RecoveryModel_ljl(application_id){
	if (application_id == "" || application_id == null || application_id == undefined)
        return null;
		
	if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();
	
	var argument = pfcCreate("pfcArgument").Create("display_tags", pfcCreate("MpfcArgument").CreateStringArgValue(""));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

	var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    var func_return = dll.ExecuteFunction("RecoveryModel_ljl", arguments);
	
	if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "displayed") {
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RetrieveAsmfileAutomatic(assembly_path, application_id) {
    if (assembly_path == "" || assembly_path == null || assembly_path == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("asmfilepath_tag", pfcCreate("MpfcArgument").CreateStringArgValue(assembly_path));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("LoadAsmfileAutomatic", arguments);

    return null;
}

//焊接仿真
function SelectiveWaveSoldering_T(lable_name, asm_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined ||
        asm_name == "" || asm_name == null || asm_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;

    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("part_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var argument_asm = pfcCreate("pfcArgument").Create("asm_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asm_name));
    arguments.Append(argument_asm);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined) {
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("SelectiveWaveSoldering_T", arguments);

    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }

    return null;
}
function SelectiveWaveSoldering_B(lable_name, asm_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined ||
        asm_name == "" || asm_name == null || asm_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;

    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("part_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var argument_asm = pfcCreate("pfcArgument").Create("asm_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asm_name));
    arguments.Append(argument_asm);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined) {
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("SelectiveWaveSoldering_B", arguments);

    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }

    return null;
}
function PressureWeldingSoldering_T(lable_name, asm_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined ||
        asm_name == "" || asm_name == null || asm_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;

    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("part_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var argument_asm = pfcCreate("pfcArgument").Create("asm_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asm_name));
    arguments.Append(argument_asm);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined) {
		alert(application_id);
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
	
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("PressureWeldingSoldering_T", arguments);

    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }

    return null;
}
function PressureWeldingSoldering_B(lable_name, asm_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined ||
        asm_name == "" || asm_name == null || asm_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;

    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("part_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var argument_asm = pfcCreate("pfcArgument").Create("asm_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asm_name));
    arguments.Append(argument_asm);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined) {
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("PressureWeldingSoldering_B", arguments);

    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }

    return null;
}
function SeparateBoardSoldering(lable_name, asm_name, application_id) {
	alert(lable_name);
	alert(asm_name);
	alert(application_id);
    //if (lable_name == "" || lable_name == null || lable_name == undefined ||
    //    asm_name == "" || asm_name == null || asm_name == undefined ||
    //    application_id == "" || application_id == null || application_id == undefined)
    //    return null;
	  if (application_id == "" || application_id == null || application_id == undefined)
        return null;
	alert(2);
    if (!isProEEmbeddedBrowser())
        return null;
	alert(3);
    var session = pfcGetProESession();
    var arguments = pfcCreate("pfcArguments");
	
	if (lable_name != "" && lable_name != null && lable_name != undefined){
		var argument = pfcCreate("pfcArgument").Create("part_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));
		arguments.Append(argument);
	}
	if (asm_name != "" && asm_name != null && asm_name != undefined){
		var argument_asm = pfcCreate("pfcArgument").Create("asm_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asm_name));
		arguments.Append(argument_asm);
	}
	alert(4);
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined) {
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
	//alert(5);
    alert(dll.Id);
    var func_return = dll.ExecuteFunction("SeparateBoardSoldering", arguments);
	alert(6);
    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }
	alert(7);
    return null;
}

//传递前面的工序(checked_val可去掉)
function FrontAsmcomponents(lable_name, checked_val, application_id) {
    if (lable_name == null || lable_name == undefined || //lable_name == "" || 
        application_id == "" || application_id == null || application_id == undefined ||
        checked_val == null || checked_val == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("display_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_chk = pfcCreate("pfcArgument").Create("checked_tag", pfcCreate("MpfcArgument").CreateIntArgValue(checked_val));
     arguments.Append(argument_chk);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("FrontAsmcomponents", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "displayed") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}


function RetrieveALLComponents(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();
    var cur_model = session.CurrentModel;

    if (cur_model == void null || cur_model.Type != pfcCreate("pfcModelType").MDL_ASSEMBLY)
        return null;

    var argument = pfcCreate("pfcArgument").Create("component_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveALLComponents", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "components") {
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RetrieveProcPlanDatas(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("procplantree_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    //alert('App ID: ' + application_id);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveProcPlanDatas", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "procplantree") {
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function ImportModel(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();
    //var cur_model = session.CurrentModel;

    //if (cur_model == void null || cur_model.Type != pfcCreate("pfcModelType").MDL_ASSEMBLY)
    //    return null;

    var argument = pfcCreate("pfcArgument").Create("importmodel_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("ImportModel", arguments);
    //alert(func_return.FunctionReturn + " " +func_return.OutputArguments.Count);
    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "modelname" || output_arg.Label == "proctreedata") {
                //alert(output_arg.Value.StringValue);
                return output_arg;
            }
        }
    }

    return null;
}

function DesignationAsmcomp2Simprep(lable_name, asm_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined ||
        asm_name == "" || asm_name == null || asm_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("asmcomp2simprep_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_asm = pfcCreate("pfcArgument").Create("asm_name_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asm_name));    
    arguments.Append(argument_asm);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DesignationAsmcomp2Simprep", arguments);

    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }

    return null;
}

function DesignationAsmcompByPPlanTree(pplantree_datas, application_id) {
    if (pplantree_datas == "" || pplantree_datas == null || pplantree_datas == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("pplantree_tag", pfcCreate("MpfcArgument").CreateStringArgValue(pplantree_datas));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DesignationAsmcompByPPlanTree", arguments);

    if (func_return.FunctionReturn == 0) {
        return func_return.OutputArguments;
    }

    return null;
}

function HighlightAsmcomponent(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("highlight_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("HighlightAsmcomponent", arguments);

    return null;
}

function HighlightAsmcomponentPair(comp_path_a, comp_path_b, application_id) {
    if (comp_path_a == "" || comp_path_a == null || comp_path_a == undefined ||
        comp_path_b == "" || comp_path_b == null || comp_path_b == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument_a = pfcCreate("pfcArgument").Create("comppath_a_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comp_path_a));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument_a);
    
    var argument_b = pfcCreate("pfcArgument").Create("comppath_b_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comp_path_b));
    arguments.Append(argument_b);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("HighlightAsmcomponentPair", arguments);

    return null;
}

function ZoomWindowByAsmcomponent(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("zoomwindow_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("ZoomWindowByAsmcomponent", arguments);

    return null;
}

function UnhighlightAsmcomponent(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("unhighlight_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("UnhighlightAsmcomponent", arguments);

    return null;
}

function UnhighlightAllAsmcomponent(application_id) {
    if (application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var lable_name = "";
    var argument = pfcCreate("pfcArgument").Create("unhighlight_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("UnhighlightAllAsmcomponent", arguments);

    return null;
}

function DisplayAsmcomppaths(comppaths, checked_val, application_id) {
    if (comppaths == "" || comppaths == null || comppaths == undefined || // 
        application_id == "" || application_id == null || application_id == undefined ||
        checked_val == null || checked_val == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("display_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comppaths));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_chk = pfcCreate("pfcArgument").Create("checked_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(checked_val));
     arguments.Append(argument_chk);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DisplayAsmcomppaths", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "displayed") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function DisplayAsmcomponents(lable_name, checked_val, application_id) {
    if (lable_name == null || lable_name == undefined || //lable_name == "" || 
        application_id == "" || application_id == null || application_id == undefined ||
        checked_val == null || checked_val == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("display_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_chk = pfcCreate("pfcArgument").Create("checked_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(checked_val));
     arguments.Append(argument_chk);
	
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DisplayAsmcomponents", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "displayed") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function DisplayFixers(layer_name, checked_val, application_id) {
    if (layer_name == "" || layer_name == null || layer_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined ||
        checked_val == null || checked_val == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("layer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(layer_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_chk = pfcCreate("pfcArgument").Create("checked_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(checked_val));
     arguments.Append(argument_chk);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DisplayFixers", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "displayed") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function DisplayOneFixer(asmcomp_path, checked_val, application_id) {
    if (asmcomp_path == "" || asmcomp_path == null || asmcomp_path == undefined ||
        application_id == "" || application_id == null || application_id == undefined ||
        checked_val == null || checked_val == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("display_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asmcomp_path));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_chk = pfcCreate("pfcArgument").Create("checked_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(checked_val));
     arguments.Append(argument_chk);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DisplayOneFixer", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "displayed") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RetrieveAsmcomponents(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("sequence_comp_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveSequenceCompDatas", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "sequence_comp") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function ModifySimprepDatas(old_layer_name, new_layer_name, comppath_lable, is_displayed, application_id) {
    if (old_layer_name == "" || old_layer_name == null || old_layer_name == undefined ||
        new_layer_name == "" || new_layer_name == null || new_layer_name == undefined ||
        comppath_lable == "" || comppath_lable == null || comppath_lable == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var arg_old_layer = pfcCreate("pfcArgument").Create("oldlayer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(old_layer_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(arg_old_layer);
    
    var arg_new_layer = pfcCreate("pfcArgument").Create("newlayer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(new_layer_name));
    arguments.Append(arg_new_layer);
    
    var arg_comppath = pfcCreate("pfcArgument").Create("comppath_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comppath_lable));
    arguments.Append(arg_comppath);
    
    var arg_displayed = pfcCreate("pfcArgument").Create("display_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(is_displayed));
    arguments.Append(arg_displayed);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("ModifySimprepDatas", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "modify_simprep") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.IntValue;
                //return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function AssembleFixerComps(assembly_name, layer_name, application_id) {
    if (assembly_name == "" || assembly_name == null || assembly_name == undefined ||
        layer_name == "" || layer_name == null || layer_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var arg_assemb = pfcCreate("pfcArgument").Create("assemblyname_tag", pfcCreate("MpfcArgument").CreateStringArgValue(assembly_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(arg_assemb);
    
    var arg_layername = pfcCreate("pfcArgument").Create("layername_tag", pfcCreate("MpfcArgument").CreateStringArgValue(layer_name));
    arguments.Append(arg_layername);

    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("AssembleFixerComps", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "fixer_comp") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RedefineFixerComp(comp_path, application_id) {
    if (comp_path == "" || comp_path == null || comp_path == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("comppath_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comp_path));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RedefineFixerComp", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "redefine_comp") {
                //alert(output_arg.Value.IntValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function AssembleFixerCompsCopyas(assembly_name, layer_name, comp_paths, application_id) {
    if (assembly_name == "" || assembly_name == null || assembly_name == undefined ||
        layer_name == "" || layer_name == null || layer_name == undefined ||
        comp_paths == "" || comp_paths == null || comp_paths == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var arg_assemb = pfcCreate("pfcArgument").Create("assemblyname_tag", pfcCreate("MpfcArgument").CreateStringArgValue(assembly_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(arg_assemb);
    
    var arg_layername = pfcCreate("pfcArgument").Create("layername_tag", pfcCreate("MpfcArgument").CreateStringArgValue(layer_name));
    arguments.Append(arg_layername);

    var arg_comppaths = pfcCreate("pfcArgument").Create("comppaths_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comp_paths));
    arguments.Append(arg_comppaths);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("AssembleFixerCompsCopyas", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "copyas_comp") {
                //alert(output_arg.Value.IntValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function RetrieveFixercomponents(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("sequence_fixer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveSequenceFixerDatas", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "sequence_fixer") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RemoveAsmcomponent(asmcomp_path, reload_or_not, layer_name, application_id) {
    if (asmcomp_path == "" || asmcomp_path == null || asmcomp_path == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("remove_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asmcomp_path));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
    
    var argument_reload = pfcCreate("pfcArgument").Create("reload_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(reload_or_not));
    arguments.Append(argument_reload);

    if (reload_or_not){
        if (layer_name == "" || layer_name == null || layer_name == undefined) {
            $.messager.alert("提示","层名称不能为空");
            return null;
        }
        var argument_layer = pfcCreate("pfcArgument").Create("layername_tag", pfcCreate("MpfcArgument").CreateStringArgValue(layer_name));
        arguments.Append(argument_layer);        
    }
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RemoveAsmcomponent", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "remove_comp") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function AddAsmcompParameter(param_name, param_value, asmcomp_path, application_id) {
    if (param_name == "" || param_name == null || param_name == undefined ||
        param_value == "" || param_value == null || param_value == undefined ||
        asmcomp_path == "" || asmcomp_path == null || asmcomp_path == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument_name = pfcCreate("pfcArgument").Create("paramname_tag", pfcCreate("MpfcArgument").CreateStringArgValue(param_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument_name);
    
    var argument_value = pfcCreate("pfcArgument").Create("paramvalue_tag", pfcCreate("MpfcArgument").CreateIntArgValue(parseInt(param_value)));
    arguments.Append(argument_value);
    
    var argument_path = pfcCreate("pfcArgument").Create("asmcomppath_tag", pfcCreate("MpfcArgument").CreateStringArgValue(asmcomp_path));
    arguments.Append(argument_path);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("AddAsmcompParameter", arguments);

    if (func_return.FunctionReturn == 0 ) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "addparameter") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function SaveProplanTree(tree_data, application_id) {
    if (tree_data == "" || tree_data == null || tree_data == undefined || application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("procplantree_tag", pfcCreate("MpfcArgument").CreateStringArgValue(tree_data));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("SaveProcplanTree", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "procplan_tree") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function CalcDistByFixersAndComponents(fixer_layer, comp_layer, application_id) {
    if (fixer_layer == "" || fixer_layer == null || fixer_layer == undefined ||
        comp_layer == "" || comp_layer == null || comp_layer == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument_fixer = pfcCreate("pfcArgument").Create("fixerlayer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(fixer_layer));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument_fixer);

    var argument_comp = pfcCreate("pfcArgument").Create("complayer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comp_layer));
    arguments.Append(argument_comp);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("CalcDistByFixerAndComps", arguments);

    if (func_return.FunctionReturn == 0) {
        //alert(func_return.FunctionReturn);
        return func_return;
    }

    return null;
}

function ExportComps2StepFile(comp_layer, application_id) {
    if (comp_layer == "" || comp_layer == null || comp_layer == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var arguments = pfcCreate("pfcArguments");
  
    var argument_comp = pfcCreate("pfcArgument").Create("exportlayer_tag", pfcCreate("MpfcArgument").CreateStringArgValue(comp_layer));
    arguments.Append(argument_comp);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("ExportComps2StepFile", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "export_result") {
                //alert(output_arg.Value.IntValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function RetrieveProcplanList(global_or_not, application_id) {
    if (application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("procplanlist_tag", pfcCreate("MpfcArgument").CreateStringArgValue(application_id));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var argument_global = pfcCreate("pfcArgument").Create("globallist_tag", pfcCreate("MpfcArgument").CreateBoolArgValue(global_or_not));
    arguments.Append(argument_global);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveProcplanListFromDB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "getprocplanlist") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function GetProcplanOriginalData(application_id) {
    if (application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("original_tag", pfcCreate("MpfcArgument").CreateStringArgValue(application_id));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("GetProcplanOriginalData", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "getoriginal") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function RetrieveProcplanDataFromDB(lable_name, application_id) {
    if (lable_name == "" || lable_name == null || lable_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("procplan_tag", pfcCreate("MpfcArgument").CreateStringArgValue(lable_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
        
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveProcplanDataFromDB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "getprocplan") {
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function StoreProcplanData2DB(procplan_name, procplan_data, application_id) {
    if (procplan_name == "" || procplan_name == null || procplan_name == undefined ||
        procplan_data == "" || procplan_data == null || procplan_data == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("savename_tag", pfcCreate("MpfcArgument").CreateStringArgValue(procplan_name));
    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var argument_data = pfcCreate("pfcArgument").Create("plandatas_tag", pfcCreate("MpfcArgument").CreateStringArgValue(procplan_data));
    arguments.Append(argument_data);
    
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("StoreProcplanData2DB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "storeplandata") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function DeleteProcplanData2DB(procplan_name, application_id) {
    if (procplan_name == "" || procplan_name == null || procplan_name == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;

    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("deletename_tag", pfcCreate("MpfcArgument").CreateStringArgValue(procplan_name));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);
        
    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("DeleteProcplanData2DB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "deleteplandata") {
                //return output_arg.Value.StringValue;
                return output_arg.Value.IntValue;
            }
        }
    }

    return null;
}

function RetrieveProplanTreeNode(application_id) {
    if (application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("pplannode_tag", pfcCreate("MpfcArgument").CreateStringArgValue(application_id));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveProcplanNodeFromDB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "getpplannode") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RetrieveProcplanTreeNodeChildren(pplanNodeID, application_id) {
    if (pplanNodeID == "" || pplanNodeID == null || pplanNodeID == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("pplannode_tag", pfcCreate("MpfcArgument").CreateStringArgValue(pplanNodeID));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveProcplanNodeChildrenFromDB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "getpplannodechildren") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}

function RetrieveProcplanTGridNodeChildren(pplanNodeID, application_id) {
    if (pplanNodeID == "" || pplanNodeID == null || pplanNodeID == undefined ||
        application_id == "" || application_id == null || application_id == undefined)
        return null;
    
    if (!isProEEmbeddedBrowser())
        return null;
    
    var session = pfcGetProESession();

    var argument = pfcCreate("pfcArgument").Create("pplantgridnode_tag", pfcCreate("MpfcArgument").CreateStringArgValue(pplanNodeID));

    var arguments = pfcCreate("pfcArguments");
    arguments.Append(argument);

    var dll = session.GetProToolkitDll(application_id);
    if (dll == null || dll == undefined){
        $.messager.alert("错误", "不能连接至ProE", "error");
        return null;
    }
    //alert(dll.Id);
    var func_return = dll.ExecuteFunction("RetrieveProcplanTGridNodeChildrenFromDB", arguments);

    if (func_return.FunctionReturn == 0) {
        for (var i = 0; i < func_return.OutputArguments.Count; i++) {
            var output_arg = func_return.OutputArguments.Item(i);
            if (output_arg.Label == "getpplantgridnodechildren") {
                //alert(output_arg.Value.StringValue);
                return output_arg.Value.StringValue;
            }
        }
    }

    return null;
}
