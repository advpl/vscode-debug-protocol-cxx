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
    void from_json(const json& j, StackTraceRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<StackTraceArguments>();

     }
    void from_json(const json& j, LaunchRequest& p)
    {
         from_json(j, (Request&) p );
         
         p.arguments = j.at("arguments").get<LaunchRequestArguments>();
    }
    void from_json(const json& j, LaunchRequestArguments& p)
    {
        if(j.find("noDebug")!= j.end())
            p.noDebug = j.at("noDebug").get<bool>();
            
    }
     void to_json(json& j, const Response& p)
     {
         to_json(j,(ProtocolMessage&) p );
         j["request_seq"] = p.request_seq;
         j["success"] = p.success;
         j["command"] = p.command;
         j["message"] = p.message;
         
            /*j.add()
             int request_seq;			
			bool success;
			
			string command;
			
			string message;*/
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
    void to_json(json& j, const Checksum& p)
    {
        j = json{{"algorithm", p.algorithm},
            {"checksum", p.checksum}};
    }		
    void from_json(const json& j, Checksum& p)
    {
        p.algorithm = j.at("algorithm").get<string>();
        p.checksum = j.at("checksum").get<string>();
    }		
    void from_json(const json& j, Source& p)
    {
        if(j.find("name")!= j.end())
            p.name = j.at("name").get<string>();
        if(j.find("path")!= j.end())
            p.path = j.at("path").get<string>();            
        if(j.find("sourceReference")!= j.end())
            p.sourceReference = j.at("sourceReference").get<int>();
        if(j.find("presentationHint")!= j.end())
            p.presentationHint = j.at("presentationHint").get<string>();
        if(j.find("origin")!= j.end())
            p.origin = j.at("origin").get<string>();
        if(j.find("sources")!= j.end())        
            p.sources = j["sources"].get<std::vector<Source>>();
        if(j.find("checksums")!= j.end())        
            p.checksums = j["checksums"].get<std::vector<Checksum>>();
/** An optional list of sources that are related to this source. These may be the source that generated this source. */
		//sources?: Source[];
		/** Optional data that a debug adapter might want to loop through the client. The client should leave the data intact and persist it across sessions. The client should not interpret the data. */
		//adapterData?: any;
		/** The checksums associated with this file. */
		//checksums?: Checksum[];


    }
    void from_json(const json& j, ConfigurationDoneRequest& p)
    {
        from_json(j, (Request&) p );
        if(j.find("arguments")!= j.end())
            p.arguments = j.at("arguments").get<ConfigurationDoneArguments>();
    }
	
    void from_json(const json& j, ConfigurationDoneArguments& p)
    {

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
    void to_json(json& j, const Breakpoint& p)
    {
        /*j = json{{"verified", p.verified},
                 {"message", p.message},
                 {"source", p.source},
                 {"line", p.line},
                 {"column", p.column},
                 {"endLine", p.endLine},
                 {"endColumn", p.endColumn}}*/
        j = json{{"verified", p.verified},                 
                 {"line", p.line}};
      
    }
    void to_json(json& j, const SetBreakpointsResponseBody& p)
    {
        j["breakpoints"] = p.breakpoints;
    }
    void to_json(json& j, const SetBreakpointsResponse& p)
    {
          j["body"] =  p.body;
    }
    
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
    void to_json(json& j, const InitializeResponse& p)
    {
        to_json(j,(Response&) p );
        j["body"] =  p.body;
    }

    void from_json(const json& j, Capabilities& p) {
        p.supportsConfigurationDoneRequest = j.at("supportsConfigurationDoneRequest").get<bool>();
        p.supportsFunctionBreakpoints = j.at("supportsFunctionBreakpoints").get<bool>();
        p.supportsConditionalBreakpoints = j.at("supportsConditionalBreakpoints").get<bool>();
    }
    void to_json(json& j, const Event& p){
        to_json(j,(ProtocolMessage&) p );
        j["event"] = p.event;        
    }
	void to_json(json& j, const TerminatedEvent& p)
    {
        to_json(j,(Event&) p );        
    }
    void to_json(json& j, const InitializedEvent& p)
    {
        to_json(j,(Event&) p );        
    }
    void to_json(json& j, const StoppedEvent& p)
    {
        to_json(j,(Event&) p );        
        j["body"] = p.body;
    }
    void to_json(json& j, const StoppedEventBody& p)
    {
        j = json{{"reason", p.reason},{"allThreadsStopped", p.allThreadsStopped}};
        if(!p.description.empty())
            j["description"] = p.description;
        if(p.threadId > 0 )
            j["threadId"] = p.threadId;
        if(!p.text.empty())
            j["text"] = p.text;
    }


    void from_json(const json& j, SourceBreakpoint& p)
    {
        p.line = j.at("line").get<int>();
        if(j.find("column")!= j.end())
            p.column = j.at("column").get<int>();   
        if(j.find("condition")!= j.end())
            p.condition = j.at("condition").get<string>();   
        if(j.find("hitCondition")!= j.end())
            p.hitCondition = j.at("hitCondition").get<string>();
        if(j.find("logMessage")!= j.end())
            p.logMessage = j.at("logMessage").get<string>();   
    }
    void from_json(const json& j, SetBreakpointsArguments& p)
    {
        p.source = j.at("source").get<Source>();
        p.breakpoints = j["breakpoints"].get<std::vector<SourceBreakpoint>>();
        p.lines = j["lines"].get<std::vector<int>>();
        if(j.find("sourceModified")!= j.end())
            p.sourceModified = j.at("sourceModified").get<bool>();
    }
    void from_json(const json& j, SetBreakpointsRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<SetBreakpointsArguments>();
     }
    void from_json(const json& j, ContinueArguments& p)
    {        
		p.threadId = j.at("threadId").get<int>();            
    }
	void from_json(const json& j, ContinueRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<ContinueArguments>();

     }
    void to_json(json& j, const ContinueResponse& p)
    {
        to_json(j,(Response&) p );
        j["body"] =  p.body;
    }	
	
    void to_json(json& j, const ContinueResponseBody& p)
    {
        j = json{{"allThreadsContinued", p.allThreadsContinued}};
	}
    void to_json(json& j, const ThreadsResponse& p)
    {
		to_json(j,(Response&) p );
        j["body"] =  p.body;
	}
    void from_json(const json& j, ThreadsResponse& p) {
            from_json(j, (Request&) p );
     }


    void to_json(json& j, const Thread& p)
    {
		j = json{{"id", p.id},
		{"name", p.name}};        
	}
    void to_json(json& j, const ThreadsResponseBody& p)
    {
		j = json{{"threads", p.threads}};        
	}

    void to_json(json& j, const Source& p) {
        j = json{{"name", p.name},
				 {"path", p.path},
                 {"sourceReference", p.sourceReference}};                 
		if(!p.presentationHint.empty())
            j["presentationHint"] = p.presentationHint;
		if(!p.origin.empty())
            j["origin"] = p.origin;
		j["sources"] = p.sources;
		if(!p.adapterData.empty())
            j["adapterData"] = p.adapterData;
		j["checksums"] = p.checksums;
		

    }

    void to_json(json& j, const StackFrame& p) {
        j = json{{"id", p.id},
                 {"name", p.name},
                 {"line", p.line},
                 {"column", p.column}};
		if(p.endLine != -1)
            j["endLine"] = p.endLine;		
		if(p.endColumn != -1)
            j["endColumn"] = p.endColumn;
		if(!p.presentationHint.empty())
            j["presentationHint"] = p.presentationHint;
        if(!p.source.name.empty())
            j["source"] = p.source;
    }
    void to_json(json& j, const StackTraceResponseBody& p)
    {
		j = json{{"stackFrames", p.stackFrames}};
            if (p.totalFrames > 0 )
				j["totalFrames"] = p.totalFrames;
	}
	void to_json(json& j, const StackTraceResponse& p)
    {
		to_json(j,(Response&) p );
        j["body"] =  p.body;
	}
    void from_json(const json& j, ValueFormat& p)
    {   
		if(j.find("hex")!= j.end())
            p.hex = j.at("hex").get<bool>();
	}
    void from_json(const json& j, StackFrameFormat& p)
    {        
		
        from_json(j,(ValueFormat) p);
        if(j.find("parameters")!= j.end())
            p.parameters = j.at("parameters").get<bool>();
		if(j.find("parameterTypes")!= j.end())
            p.parameterTypes = j.at("parameterTypes").get<bool>();
		if(j.find("parameterNames")!= j.end())
            p.parameterNames = j.at("parameterNames").get<bool>();
		if(j.find("parameterValues")!= j.end())
            p.parameterValues = j.at("parameterValues").get<bool>();
		if(j.find("line")!= j.end())
            p.line = j.at("line").get<bool>();
		if(j.find("module")!= j.end())
            p.module = j.at("module").get<bool>();
		if(j.find("includeAll")!= j.end())
            p.includeAll = j.at("includeAll").get<bool>();	
	}
	void from_json(const json& j, StackTraceArguments& p)
    {
        p.threadId = j.at("threadId").get<int>();
		if(j.find("startFrame")!= j.end())
            p.startFrame = j.at("startFrame").get<int>();
		if(j.find("levels")!= j.end())
            p.levels = j.at("levels").get<int>();
		if(j.find("format")!= j.end())
            p.format = j.at("format").get<StackFrameFormat>();
            
    }
    void from_json(const json& j, NextArguments& p)
    {        
		p.threadId = j.at("threadId").get<int>();            
    }
	void from_json(const json& j, NextRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<NextArguments>();

     }
	void to_json(json& j, const NextResponse& p)
    {
        to_json(j,(Response&) p );        
    }	
    void from_json(const json& j, StepInArguments& p)
    {        
		p.threadId = j.at("threadId").get<int>();            
    }
	void from_json(const json& j, StepInRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<StepInArguments>();

     }
	void to_json(json& j, const StepInResponse& p)
    {
        to_json(j,(Response&) p );        
    }	


}