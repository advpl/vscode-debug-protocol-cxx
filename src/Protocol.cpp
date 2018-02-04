#include "Protocol.hpp"
namespace vscode_debug {
void to_json(json& j, const ProtocolMessage& p) {
        j = json{{"seq", p.seq}, {"type", p.type}};
    }
    void from_json(const json& j, ProtocolMessage& p) {
        p.seq = j.at("seq").get<int>();
        p.type = j.at("type").get<string>();

    }

    void to_json(json& j, const Request& p) {
        to_json(j,(ProtocolMessage&) p );
    }
    void from_json(const json& j, Request& p) {
        from_json(j, (ProtocolMessage&) p );
        p.command = j.at("command").get<string>();
    }

    void from_json(const json& j, InitializeRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<InitializeRequestArguments>();

     }


     void to_json(json& j, const InitializeRequestArguments& p) {
        j = json{{"clientID", p.clientID},
                 {"adapterID", p.adapterID},
                 {"locale", p.locale},
                 {"linesStartAt1", p.linesStartAt1},
                 {"columnsStartAt1", p.columnsStartAt1},                 
                 {"pathFormat", p.pathFormat},
                 {"supportsVariableType", p.supportsVariableType},
                 {"supportsVariablePaging", p.supportsVariablePaging},
                 {"supportsRunInTerminalRequest", p.supportsRunInTerminalRequest}};

    }
    void from_json(const json& j, InitializeRequestArguments& p) {        
		p.adapterID = j.at("adapterID").get<string>();
        if(j.find("clientID")!= j.end())
            p.clientID = j.at("clientID").get<string>();
        if(j.find("locale")!= j.end())
            p.locale = j.at("locale").get<string>();
		if(j.find("linesStartAt1")!= j.end())
            p.linesStartAt1 = j.at("linesStartAt1").get<bool>();
        if(j.find("columnsStartAt1")!= j.end())
		    p.columnsStartAt1 = j.at("columnsStartAt1").get<bool>();
		if(j.find("pathFormat")!= j.end())
            p.pathFormat = j.at("pathFormat").get<string>();
		if(j.find("supportsVariableType")!= j.end())
            p.supportsVariableType = j.at("supportsVariableType").get<bool>();
		if(j.find("supportsVariablePaging")!= j.end())
            p.supportsVariablePaging = j.at("supportsVariablePaging").get<bool>();
		if(j.find("supportsRunInTerminalRequest")!= j.end())
            p.supportsRunInTerminalRequest = j.at("supportsRunInTerminalRequest").get<bool>();
		

    }
    using nlohmann::json;
    void to_json(json& j, const Capabilities& p) {
        j = json{{"supportsConfigurationDoneRequest", p.supportsConfigurationDoneRequest},
                 {"supportsFunctionBreakpoints", p.supportsFunctionBreakpoints},
                 {"supportsConditionalBreakpoints", p.supportsConditionalBreakpoints},
                 {"supportsHitConditionalBreakpoints", p.supportsHitConditionalBreakpoints},
                 {"supportsEvaluateForHovers", p.supportsEvaluateForHovers},        
      	{"supportsStepBack",p.supportsStepBack},		
		{"supportsSetVariable",p.supportsSetVariable},		
		{"supportsRestartFrame",p.supportsRestartFrame},		
		{"supportsGotoTargetsRequest",p.supportsGotoTargetsRequest},
		{"supportsStepInTargetsRequest",p.supportsStepInTargetsRequest},		
		{"supportsCompletionsRequest",p.supportsCompletionsRequest},
		{"supportsModulesRequest",p.supportsModulesRequest},
                 //vector<ExceptionBreakpointsFilter> exceptionBreakpointFilters;
        //vector <ColumnDescriptor> additionalModuleColumns;
        //supportedChecksumAlgorithms
        {"supportsRestartRequest",p.supportsRestartRequest},
		{"supportsExceptionOptions",p.supportsExceptionOptions},
		{"supportsValueFormattingOptions",p.supportsValueFormattingOptions},
		{"supportsExceptionInfoRequest",p.supportsExceptionInfoRequest},
		{"supportTerminateDebuggee",p.supportTerminateDebuggee},
		{"supportsDelayedStackTraceLoading",p.supportsDelayedStackTraceLoading},
		{"supportsLoadedSourcesRequest",p.supportsLoadedSourcesRequest}};
    }

    void from_json(const json& j, Capabilities& p) {
        p.supportsConfigurationDoneRequest = j.at("supportsConfigurationDoneRequest").get<bool>();
        p.supportsFunctionBreakpoints = j.at("supportsFunctionBreakpoints").get<bool>();
        p.supportsConditionalBreakpoints = j.at("supportsConditionalBreakpoints").get<bool>();
    }

}