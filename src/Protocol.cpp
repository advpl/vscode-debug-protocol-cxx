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


     void to_json(json& j, InitializeRequestArguments& p) {
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
        j = json{{"verified", p.verified},
                 {"line", p.line}};
        if(p.id != -1)
            j["id"] = p.id;
        if(!p.message.empty())
            j["message"] = p.message;
        if(!p.source.path.empty())
            j["source"] = p.source;
        if(p.column != -1)
            j["column"] = p.column;
        if(p.endLine != -1)
            j["endLine"] = p.endLine;
        if(p.endColumn != -1)
            j["endColumn"] = p.endColumn;
        if(!p.instructionReference.empty())
            j["instructionReference"] = p.instructionReference;
        if(p.offset != -1)
            j["offset"] = p.offset;
    }
    void to_json(json& j, const SetBreakpointsResponseBody& p)
    {
        j["breakpoints"] = p.breakpoints;
    }
    void to_json(json& j, const SetBreakpointsResponse& p)
    {
          to_json(j,(Response&) p );
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
		{"supportsLoadedSourcesRequest",p.supportsLoadedSourcesRequest},
		{"supportsLogPoints",p.supportsLogPoints},
		{"supportsTerminateRequest",p.supportsTerminateRequest},
		{"supportsDataBreakpoints",p.supportsDataBreakpoints},
		{"supportsReadMemoryRequest",p.supportsReadMemoryRequest},
		{"supportsWriteMemoryRequest",p.supportsWriteMemoryRequest},
		{"supportsDisassembleRequest",p.supportsDisassembleRequest},
		{"supportsCancelRequest",p.supportsCancelRequest},
		{"supportsBreakpointLocationsRequest",p.supportsBreakpointLocationsRequest},
		{"supportsClipboardContext",p.supportsClipboardContext},
		{"supportsSteppingGranularity",p.supportsSteppingGranularity},
		{"supportsInstructionBreakpoints",p.supportsInstructionBreakpoints},
		{"supportsExceptionFilterOptions",p.supportsExceptionFilterOptions},
		{"supportsSingleThreadExecutionRequests",p.supportsSingleThreadExecutionRequests},
		{"supportsProgressReporting",p.supportsProgressReporting},
		{"supportsInvalidatedEvent",p.supportsInvalidatedEvent},
		{"supportsMemoryReferences",p.supportsMemoryReferences},
		{"supportsMemoryEvent",p.supportsMemoryEvent},
		{"supportsStartDebuggingRequest",p.supportsStartDebuggingRequest},
		{"supportsANSIStyling",p.supportsANSIStyling},
		{"supportsDataBreakpointBytes",p.supportsDataBreakpointBytes}};
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
        if(!p.hitBreakpointIds.empty())
            j["hitBreakpointIds"] = p.hitBreakpointIds;
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
		if(j.find("singleThread")!= j.end())
			p.singleThread = j.at("singleThread").get<bool>();
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
        if(!p.instructionPointerReference.empty())
            j["instructionPointerReference"] = p.instructionPointerReference;
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
    void to_json(json& j, const ValueFormat& p)
    {		
        j["hex"] =  p.hex;
	}
    void from_json(const json& j, ValueFormat& p)
    {   
		if(j.find("hex")!= j.end())
            p.hex = j.at("hex").get<bool>();
	}
    void from_json(const json& j, StackFrameFormat& p)
    {        
		
        from_json(j,(ValueFormat&) p);
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
		if(j.find("granularity")!= j.end())
			p.granularity = j.at("granularity").get<string>();
		if(j.find("singleThread")!= j.end())
			p.singleThread = j.at("singleThread").get<bool>();
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
		if(j.find("targetId")!= j.end())
			p.targetId = j.at("targetId").get<int>();
		if(j.find("granularity")!= j.end())
			p.granularity = j.at("granularity").get<string>();
		if(j.find("singleThread")!= j.end())
			p.singleThread = j.at("singleThread").get<bool>();
    }
	void from_json(const json& j, StepInRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<StepInArguments>();

     }
	void to_json(json& j, const StepInResponse& p)
    {
        to_json(j,(Response&) p );        
    }	
    void to_json(json& j, const VariablePresentationHint& p) 
    {
        j = json{{"kind", p.kind},
                 {"attributes", p.attributes}};
				 if(!p.visibility.empty())
            		j["visibility"] = p.visibility;				 
	}
    void to_json(json& j, const Variable& p) 
    {
        j = json{{"name", p.name},
                 {"value", p.value},
				 {"type", p.type},
				 {"variablesReference", p.variablesReference}};
				if(!p.presentationHint.kind.empty())
            		j["presentationHint"] = p.presentationHint;
				if(!p.evaluateName.empty())
					j["evaluateName"] = p.evaluateName;
				if(p.namedVariables > 0 )
					j["namedVariables"] = p.namedVariables;
				if(p.indexedVariables > 0 )
					j["indexedVariables"] = p.indexedVariables;
				if(!p.memoryReference.empty())
					j["memoryReference"] = p.memoryReference;
	}
    void to_json(json& j, const ScopesResponse& p)
    {
          to_json(j,(Response&) p );
          j["body"] =  p.body;
    }

	void to_json(json& j, const ScopesResponseBody& p)
    {
        j = json{{"scopes", p.scopes}};
	}
	
	void to_json(json& j, const ScopesArguments& p) 
    {
		j = json{{"frameId", p.frameId}};
	}

	void to_json(json& j, const Scope& p) 
    {
        j = json{{"name", p.name},
                 {"expensive", p.expensive},				 
				 {"variablesReference", p.variablesReference}};								
				if(p.namedVariables > 0 )
					j["namedVariables"] = p.namedVariables;
				if(p.indexedVariables > 0 )
					j["indexedVariables"] = p.indexedVariables;
				if(!p.source.name.empty())
            		j["source"] = p.source;
				if(p.line != -1)
					j["line"] = p.line;
				if(p.column != -1 )
					j["column"] = p.column;
				if(p.endLine != -1 )
					j["endLine"] = p.endLine;
				if(p.endColumn != -1 )
					j["endColumn"] = p.endColumn;
	}
    void from_json(const json& j, ScopesRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<ScopesArguments>();
     }
    void from_json(const json& j, ScopesArguments& p) {
        p.frameId = j.at("frameId").get<int>();        
    }

    void to_json(json& j, const VariablesArguments& p) 
    {
		j = json{{"variablesReference", p.variablesReference}};
			if(p.filter.empty() )
				j["filter"] = p.filter;
			if(p.start != -1 )
				j["start"] = p.start;
			if(p.count != -1 )
				j["count"] = p.count;			
			j["format"] = p.format;
	};   
    void from_json(const json& j, VariablesArguments& p) {
        p.variablesReference = j.at("variablesReference").get<int>();
		if(j.find("filter")!= j.end())
			p.filter = j.at("filter").get<string>();
		if(j.find("start")!= j.end())
			p.start = j.at("start").get<int>();
		if(j.find("count")!= j.end())
			p.count = j.at("count").get<int>();		
		if(j.find("format")!= j.end())
			p.format = j.at("format").get<ValueFormat>();
    }
		

	void from_json(const json& j, VariablesRequest& p) {
            from_json(j, (Request&) p );
			p.arguments = j.at("arguments").get<VariablesArguments>();
     }
     void to_json(json& j, const SetVariableResponseBody& p) {
        j = json{{"value", p.value}};				                  
		if(!p.type.empty())
            j["type"] = p.type;
		if(p.variablesReference != -1)
            j["variablesReference"] = p.variablesReference;
		if(p.namedVariables != -1)
            j["namedVariables"] = p.namedVariables;
		if(p.indexedVariables != -1)
            j["indexedVariables"] = p.indexedVariables;		
    }
    void to_json(json& j, const VariablesResponseBody& p)
    {
        j["variables"] = p.variables;
    }

	void to_json(json& j, const VariablesResponse& p)
    {
          to_json(j,(Response&) p );
          j["body"] =  p.body;
    }
    void from_json(const json& j, EvaluateArguments& p) {
        p.expression = j.at("expression").get<string>();		
		if(j.find("frameId")!= j.end())
			p.frameId = j.at("frameId").get<int>();
		if(j.find("context")!= j.end())
			p.context = j.at("context").get<string>();
		if(j.find("format")!= j.end())
			p.format = j.at("format").get<ValueFormat>();
    }
	void from_json(const json& j, EvaluateRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<EvaluateArguments>();
     }
     void to_json(json& j, const EvaluateResponseBody& p)
    {
		j = json{{"result", p.result}};
            if (!p.type.empty())
				j["type"] = p.type;
			if (!p.presentationHint.kind.empty())
				j["presentationHint"] = p.presentationHint;
			if (p.variablesReference > 0 )
				j["variablesReference"] = p.variablesReference;
			if (p.namedVariables > 0 )
				j["namedVariables"] = p.namedVariables;
			if (p.indexedVariables > 0 )
				j["indexedVariables"] = p.indexedVariables;
	}
	void to_json(json& j, const EvaluateResponse& p)
    {
          to_json(j,(Response&) p );
          j["body"] =  p.body;
    }    
    void from_json(const json& j, ExceptionFilterOptions& p){
        p.filterId = j.at("filterId").get<string>();
        if(j.find("condition")!= j.end())
            p.condition = j.at("condition").get<string>();
    }
    void from_json(const json& j, SetExceptionBreakpointsArguments& p){
        if(j.find("filters")!= j.end())
            p.filters = j.at("filters").get<vector<string>>();
        if(j.find("filterOptions")!= j.end())
            p.filterOptions = j.at("filterOptions").get<vector<ExceptionFilterOptions>>();
    }
    void to_json(json& j, const SetExceptionBreakpointsResponse& p)
    {
        to_json(j,(Response&) p );
    }

    void from_json(const json& j, SourceArguments& p){
        p.sourceReference = j.at("sourceReference").get<int>();		
		if(j.find("source")!= j.end())
			p.source = j.at("source").get<Source>();
		
    }
	void from_json(const json& j, SourceRequest& p){
       from_json(j, (Request&) p );
       p.arguments = j.at("arguments").get<SourceArguments>();		 
    }
	void to_json(json& j, const SourceResponse& p){
           to_json(j,(Response&) p );
          j["body"] =  p.body;
    }
	void to_json(json& j, const SourceResponseBody& p)
    {
        j = json{{"content", p.content}};
        if (!p.mimeType.empty())
            j["mimeType"] = p.mimeType;

    }
    void from_json(const json& j, InitializeRequest& p) {
            from_json(j, (Request&) p );
            p.arguments = j.at("arguments").get<InitializeRequestArguments>();

     }
     void from_json(const json& j, SetExceptionBreakpointsRequest& p){
        from_json(j, (Request&) p );
        p.arguments = j.at("arguments").get<SetExceptionBreakpointsArguments>();
    }

    void to_json(json& j, const OutputEventBody& p) {
        j["output"] = p.output;

        if (!p.category.empty())
            j["category"] = p.category;

        if (!p.group.empty())
            j["group"] = p.group;

        if (!p.data.empty())
            j["data"] = p.data;

        if (!p.source.name.empty())
            j["source"] = p.source;

        if (p.variablesReference != -1)
            j["variablesReference"] = p.variablesReference;

        if (p.line != -1)
            j["line"] = p.line;

        if (p.column != -1)
            j["column"] = p.column;

        if (p.locationReference != -1)
            j["locationReference"] = p.locationReference;
    }

    void to_json(json& j, const OutputEvent& p) {
        to_json(j,(Event&) p );
        j["body"] = p.body;
    }

    // -------------------------------------------------------------------------
    // New serialization functions for DAP v1.71
    // -------------------------------------------------------------------------

    // SetFunctionBreakpoints
    void from_json(const json& j, FunctionBreakpoint& p) {
        p.name = j.at("name").get<string>();
        if(j.find("condition")!= j.end()) p.condition = j.at("condition").get<string>();
        if(j.find("hitCondition")!= j.end()) p.hitCondition = j.at("hitCondition").get<string>();
    }
    void to_json(json& j, const FunctionBreakpoint& p) {
        j = json{{"name", p.name}};
        if(!p.condition.empty()) j["condition"] = p.condition;
        if(!p.hitCondition.empty()) j["hitCondition"] = p.hitCondition;
    }
    void from_json(const json& j, SetFunctionBreakpointsArguments& p) {
        p.breakpoints = j.at("breakpoints").get<vector<FunctionBreakpoint>>();
    }
    void from_json(const json& j, SetFunctionBreakpointsRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<SetFunctionBreakpointsArguments>();
    }
    void to_json(json& j, const SetFunctionBreakpointsResponseBody& p) {
        j["breakpoints"] = p.breakpoints;
    }
    void to_json(json& j, const SetFunctionBreakpointsResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // DataBreakpoints
    void from_json(const json& j, DataBreakpoint& p) {
        p.dataId = j.at("dataId").get<string>();
        if(j.find("accessType")!= j.end()) p.accessType = j.at("accessType").get<string>();
        if(j.find("condition")!= j.end()) p.condition = j.at("condition").get<string>();
        if(j.find("hitCondition")!= j.end()) p.hitCondition = j.at("hitCondition").get<string>();
    }
    void from_json(const json& j, DataBreakpointInfoArguments& p) {
        if(j.find("variablesReference")!= j.end()) p.variablesReference = j.at("variablesReference").get<int>();
        p.name = j.at("name").get<string>();
        if(j.find("frameId")!= j.end()) p.frameId = j.at("frameId").get<int>();
    }
    void from_json(const json& j, DataBreakpointInfoRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<DataBreakpointInfoArguments>();
    }
    void to_json(json& j, const DataBreakpointInfoResponseBody& p) {
        j = json{{"dataId", p.dataId}, {"description", p.description}};
        if(!p.accessTypes.empty()) j["accessTypes"] = p.accessTypes;
        if(p.canPersist) j["canPersist"] = p.canPersist;
    }
    void to_json(json& j, const DataBreakpointInfoResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }
    void from_json(const json& j, SetDataBreakpointsArguments& p) {
        p.breakpoints = j.at("breakpoints").get<vector<DataBreakpoint>>();
    }
    void from_json(const json& j, SetDataBreakpointsRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<SetDataBreakpointsArguments>();
    }
    void to_json(json& j, const SetDataBreakpointsResponseBody& p) {
        j["breakpoints"] = p.breakpoints;
    }
    void to_json(json& j, const SetDataBreakpointsResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // BreakpointLocations
    void from_json(const json& j, BreakpointLocationsArguments& p) {
        p.source = j.at("source").get<Source>();
        p.line = j.at("line").get<int>();
        if(j.find("column")!= j.end()) p.column = j.at("column").get<int>();
        if(j.find("endLine")!= j.end()) p.endLine = j.at("endLine").get<int>();
        if(j.find("endColumn")!= j.end()) p.endColumn = j.at("endColumn").get<int>();
    }
    void from_json(const json& j, BreakpointLocationsRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<BreakpointLocationsArguments>();
    }
    void to_json(json& j, const BreakpointLocation& p) {
        j = json{{"line", p.line}};
        if(p.column != -1) j["column"] = p.column;
        if(p.endLine != -1) j["endLine"] = p.endLine;
        if(p.endColumn != -1) j["endColumn"] = p.endColumn;
    }
    void to_json(json& j, const BreakpointLocationsResponseBody& p) {
        j["breakpoints"] = p.breakpoints;
    }
    void to_json(json& j, const BreakpointLocationsResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // InstructionBreakpoints
    void from_json(const json& j, InstructionBreakpoint& p) {
        p.instructionReference = j.at("instructionReference").get<string>();
        if(j.find("offset")!= j.end()) p.offset = j.at("offset").get<int>();
        if(j.find("condition")!= j.end()) p.condition = j.at("condition").get<string>();
        if(j.find("hitCondition")!= j.end()) p.hitCondition = j.at("hitCondition").get<string>();
        if(j.find("mode")!= j.end()) p.mode = j.at("mode").get<string>();
    }
    void from_json(const json& j, SetInstructionBreakpointsArguments& p) {
        p.breakpoints = j.at("breakpoints").get<vector<InstructionBreakpoint>>();
    }
    void from_json(const json& j, SetInstructionBreakpointsRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<SetInstructionBreakpointsArguments>();
    }
    void to_json(json& j, const SetInstructionBreakpointsResponseBody& p) {
        j["breakpoints"] = p.breakpoints;
    }
    void to_json(json& j, const SetInstructionBreakpointsResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // Execution control
    void from_json(const json& j, StepOutArguments& p) {
        p.threadId = j.at("threadId").get<int>();
        if(j.find("granularity")!= j.end()) p.granularity = j.at("granularity").get<string>();
        if(j.find("singleThread")!= j.end()) p.singleThread = j.at("singleThread").get<bool>();
    }
    void from_json(const json& j, StepOutRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<StepOutArguments>();
    }
    void to_json(json& j, const StepOutResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, StepBackArguments& p) {
        p.threadId = j.at("threadId").get<int>();
        if(j.find("granularity")!= j.end()) p.granularity = j.at("granularity").get<string>();
        if(j.find("singleThread")!= j.end()) p.singleThread = j.at("singleThread").get<bool>();
    }
    void from_json(const json& j, StepBackRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<StepBackArguments>();
    }
    void to_json(json& j, const StepBackResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, ReverseContinueArguments& p) {
        p.threadId = j.at("threadId").get<int>();
        if(j.find("singleThread")!= j.end()) p.singleThread = j.at("singleThread").get<bool>();
    }
    void from_json(const json& j, ReverseContinueRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<ReverseContinueArguments>();
    }
    void to_json(json& j, const ReverseContinueResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, RestartFrameArguments& p) {
        p.frameId = j.at("frameId").get<int>();
    }
    void from_json(const json& j, RestartFrameRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<RestartFrameArguments>();
    }
    void to_json(json& j, const RestartFrameResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, PauseArguments& p) {
        p.threadId = j.at("threadId").get<int>();
    }
    void from_json(const json& j, PauseRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<PauseArguments>();
    }
    void to_json(json& j, const PauseResponse& p) { to_json(j,(Response&) p); }

    // Goto
    void from_json(const json& j, GotoArguments& p) {
        p.threadId = j.at("threadId").get<int>();
        p.targetId = j.at("targetId").get<int>();
    }
    void from_json(const json& j, GotoRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<GotoArguments>();
    }
    void to_json(json& j, const GotoResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, GotoTargetsArguments& p) {
        p.source = j.at("source").get<Source>();
        p.line = j.at("line").get<int>();
        if(j.find("column")!= j.end()) p.column = j.at("column").get<int>();
    }
    void from_json(const json& j, GotoTargetsRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<GotoTargetsArguments>();
    }
    void to_json(json& j, const GotoTarget& p) {
        j = json{{"id", p.id}, {"label", p.label}, {"line", p.line}};
        if(p.column != -1) j["column"] = p.column;
        if(p.endLine != -1) j["endLine"] = p.endLine;
        if(p.endColumn != -1) j["endColumn"] = p.endColumn;
        if(!p.instructionPointerReference.empty()) j["instructionPointerReference"] = p.instructionPointerReference;
    }
    void to_json(json& j, const GotoTargetsResponseBody& p) { j["targets"] = p.targets; }
    void to_json(json& j, const GotoTargetsResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // SetVariable
    void from_json(const json& j, SetVariableArguments& p) {
        p.variablesReference = j.at("variablesReference").get<int>();
        p.name = j.at("name").get<string>();
        p.value = j.at("value").get<string>();
        if(j.find("format")!= j.end()) p.format = j.at("format").get<ValueFormat>();
    }
    void from_json(const json& j, SetVariableRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<SetVariableArguments>();
    }

    // Memory
    void from_json(const json& j, ReadMemoryArguments& p) {
        p.memoryReference = j.at("memoryReference").get<string>();
        if(j.find("offset")!= j.end()) p.offset = j.at("offset").get<int>();
        p.count = j.at("count").get<int>();
    }
    void from_json(const json& j, ReadMemoryRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<ReadMemoryArguments>();
    }
    void to_json(json& j, const ReadMemoryResponseBody& p) {
        j = json{{"address", p.address}};
        if(p.unreadableBytes != -1) j["unreadableBytes"] = p.unreadableBytes;
        if(!p.data.empty()) j["data"] = p.data;
    }
    void to_json(json& j, const ReadMemoryResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    void from_json(const json& j, WriteMemoryArguments& p) {
        p.memoryReference = j.at("memoryReference").get<string>();
        if(j.find("offset")!= j.end()) p.offset = j.at("offset").get<int>();
        if(j.find("allowPartial")!= j.end()) p.allowPartial = j.at("allowPartial").get<bool>();
        p.data = j.at("data").get<string>();
    }
    void from_json(const json& j, WriteMemoryRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<WriteMemoryArguments>();
    }
    void to_json(json& j, const WriteMemoryResponseBody& p) {
        j = json::object();
        if(p.offset != -1) j["offset"] = p.offset;
        if(p.bytesWritten != -1) j["bytesWritten"] = p.bytesWritten;
    }
    void to_json(json& j, const WriteMemoryResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // Disassemble
    void from_json(const json& j, DisassembleArguments& p) {
        p.memoryReference = j.at("memoryReference").get<string>();
        if(j.find("offset")!= j.end()) p.offset = j.at("offset").get<int>();
        if(j.find("instructionOffset")!= j.end()) p.instructionOffset = j.at("instructionOffset").get<int>();
        p.instructionCount = j.at("instructionCount").get<int>();
        if(j.find("resolveSymbols")!= j.end()) p.resolveSymbols = j.at("resolveSymbols").get<bool>();
    }
    void from_json(const json& j, DisassembleRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<DisassembleArguments>();
    }
    void to_json(json& j, const DisassembledInstruction& p) {
        j = json{{"address", p.address}, {"instruction", p.instruction}};
        if(!p.instructionBytes.empty()) j["instructionBytes"] = p.instructionBytes;
        if(!p.symbol.empty()) j["symbol"] = p.symbol;
        if(!p.location.path.empty()) j["location"] = p.location;
        if(p.line != -1) j["line"] = p.line;
        if(p.column != -1) j["column"] = p.column;
        if(p.endLine != -1) j["endLine"] = p.endLine;
        if(p.endColumn != -1) j["endColumn"] = p.endColumn;
    }
    void to_json(json& j, const DisassembleResponseBody& p) { j["instructions"] = p.instructions; }
    void to_json(json& j, const DisassembleResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // Modules
    void from_json(const json& j, ModulesArguments& p) {
        if(j.find("startModule")!= j.end()) p.startModule = j.at("startModule").get<int>();
        if(j.find("moduleCount")!= j.end()) p.moduleCount = j.at("moduleCount").get<int>();
    }
    void from_json(const json& j, ModulesRequest& p) {
        from_json(j, (Request&) p);
        if(j.find("arguments")!= j.end()) p.arguments = j.at("arguments").get<ModulesArguments>();
    }
    void to_json(json& j, const Module& p) {
        j = json{{"id", p.id}, {"name", p.name}};
        if(!p.path.empty()) j["path"] = p.path;
        if(p.isOptimized) j["isOptimized"] = p.isOptimized;
        if(p.isUserCode) j["isUserCode"] = p.isUserCode;
        if(!p.version.empty()) j["version"] = p.version;
        if(!p.symbolStatus.empty()) j["symbolStatus"] = p.symbolStatus;
        if(!p.symbolFilePath.empty()) j["symbolFilePath"] = p.symbolFilePath;
        if(!p.dateTimeStamp.empty()) j["dateTimeStamp"] = p.dateTimeStamp;
        if(!p.addressRange.empty()) j["addressRange"] = p.addressRange;
    }
    void to_json(json& j, const ModulesResponseBody& p) {
        j["modules"] = p.modules;
        if(p.totalModules != -1) j["totalModules"] = p.totalModules;
    }
    void to_json(json& j, const ModulesResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // LoadedSources
    void from_json(const json& j, LoadedSourcesRequest& p) {
        from_json(j, (Request&) p);
    }
    void to_json(json& j, const LoadedSourcesResponseBody& p) { j["sources"] = p.sources; }
    void to_json(json& j, const LoadedSourcesResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // Completions
    void from_json(const json& j, CompletionsArguments& p) {
        if(j.find("frameId")!= j.end()) p.frameId = j.at("frameId").get<int>();
        p.text = j.at("text").get<string>();
        p.column = j.at("column").get<int>();
        if(j.find("line")!= j.end()) p.line = j.at("line").get<int>();
    }
    void from_json(const json& j, CompletionsRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<CompletionsArguments>();
    }
    void to_json(json& j, const CompletionItem& p) {
        j = json{{"label", p.label}};
        if(!p.text.empty()) j["text"] = p.text;
        if(!p.sortText.empty()) j["sortText"] = p.sortText;
        if(!p.detail.empty()) j["detail"] = p.detail;
        if(!p.type.empty()) j["type"] = p.type;
        if(p.start != -1) j["start"] = p.start;
        if(p.length != -1) j["length"] = p.length;
        if(p.selectionStart != -1) j["selectionStart"] = p.selectionStart;
        if(p.selectionLength != -1) j["selectionLength"] = p.selectionLength;
    }
    void to_json(json& j, const CompletionsResponseBody& p) { j["targets"] = p.targets; }
    void to_json(json& j, const CompletionsResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // ExceptionInfo
    void from_json(const json& j, ExceptionInfoArguments& p) {
        p.threadId = j.at("threadId").get<int>();
    }
    void from_json(const json& j, ExceptionInfoRequest& p) {
        from_json(j, (Request&) p);
        p.arguments = j.at("arguments").get<ExceptionInfoArguments>();
    }
    void to_json(json& j, const ExceptionDetails& p) {
        j = json::object();
        if(!p.message.empty()) j["message"] = p.message;
        if(!p.typeName.empty()) j["typeName"] = p.typeName;
        if(!p.fullTypeName.empty()) j["fullTypeName"] = p.fullTypeName;
        if(!p.evaluateName.empty()) j["evaluateName"] = p.evaluateName;
        if(!p.stackTrace.empty()) j["stackTrace"] = p.stackTrace;
    }
    void to_json(json& j, const ExceptionInfoResponseBody& p) {
        j = json{{"exceptionId", p.exceptionId}, {"breakMode", p.breakMode}};
        if(!p.description.empty()) j["description"] = p.description;
        j["details"] = p.details;
    }
    void to_json(json& j, const ExceptionInfoResponse& p) {
        to_json(j,(Response&) p);
        j["body"] = p.body;
    }

    // Attach / Disconnect / Terminate / Restart / Cancel
    void from_json(const json& j, AttachRequestArguments& p) {
        if(j.find("restart")!= j.end()) p.restart = j.at("restart").get<string>();
    }
    void from_json(const json& j, AttachRequest& p) {
        from_json(j, (Request&) p);
        if(j.find("arguments")!= j.end()) p.arguments = j.at("arguments").get<AttachRequestArguments>();
    }
    void to_json(json& j, const AttachResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, DisconnectArguments& p) {
        if(j.find("restart")!= j.end()) p.restart = j.at("restart").get<bool>();
        if(j.find("terminateDebuggee")!= j.end()) p.terminateDebuggee = j.at("terminateDebuggee").get<bool>();
        if(j.find("suspendDebuggee")!= j.end()) p.suspendDebuggee = j.at("suspendDebuggee").get<bool>();
    }
    void from_json(const json& j, DisconnectRequest& p) {
        from_json(j, (Request&) p);
        if(j.find("arguments")!= j.end()) p.arguments = j.at("arguments").get<DisconnectArguments>();
    }
    void to_json(json& j, const DisconnectResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, TerminateArguments& p) {
        if(j.find("restart")!= j.end()) p.restart = j.at("restart").get<bool>();
    }
    void from_json(const json& j, TerminateRequest& p) {
        from_json(j, (Request&) p);
        if(j.find("arguments")!= j.end()) p.arguments = j.at("arguments").get<TerminateArguments>();
    }
    void to_json(json& j, const TerminateResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, RestartArguments& p) { (void)j; (void)p; }
    void from_json(const json& j, RestartRequest& p) {
        from_json(j, (Request&) p);
    }
    void to_json(json& j, const RestartResponse& p) { to_json(j,(Response&) p); }

    void from_json(const json& j, CancelArguments& p) {
        if(j.find("requestId")!= j.end()) p.requestId = j.at("requestId").get<int>();
        if(j.find("progressId")!= j.end()) p.progressId = j.at("progressId").get<string>();
    }
    void from_json(const json& j, CancelRequest& p) {
        from_json(j, (Request&) p);
        if(j.find("arguments")!= j.end()) p.arguments = j.at("arguments").get<CancelArguments>();
    }
    void to_json(json& j, const CancelResponse& p) { to_json(j,(Response&) p); }
    void to_json(json& j, const ConfigurationDoneResponse& p) { to_json(j,(Response&) p); }
    void to_json(json& j, const LaunchResponse& p) { to_json(j,(Response&) p); }

    // Reverse requests: RunInTerminal, StartDebugging
    void to_json(json& j, const RunInTerminalRequestArguments& p) {
        j = json{{"cwd", p.cwd}, {"args", p.args}};
        if(!p.kind.empty()) j["kind"] = p.kind;
        if(!p.title.empty()) j["title"] = p.title;
    }
    void to_json(json& j, const RunInTerminalRequest& p) {
        to_json(j,(ProtocolMessage&) p);
        j["command"] = p.command;
        j["arguments"] = p.arguments;
    }
    void from_json(const json& j, RunInTerminalResponseBody& p) {
        if(j.find("processId")!= j.end()) p.processId = j.at("processId").get<int>();
        if(j.find("shellProcessId")!= j.end()) p.shellProcessId = j.at("shellProcessId").get<int>();
    }
    void from_json(const json& j, RunInTerminalResponse& p) {
        from_json(j,(Request&) p);
        if(j.find("body")!= j.end()) p.body = j.at("body").get<RunInTerminalResponseBody>();
    }
    void to_json(json& j, const StartDebuggingRequestArguments& p) {
        j = json{{"request", p.request}};
    }
    void to_json(json& j, const StartDebuggingRequest& p) {
        to_json(j,(ProtocolMessage&) p);
        j["command"] = p.command;
        j["arguments"] = p.arguments;
    }
    void from_json(const json& j, StartDebuggingResponse& p) {
        from_json(j,(Request&) p);
    }

    // New events
    void to_json(json& j, const ProgressStartEventBody& p) {
        j = json{{"progressId", p.progressId}, {"title", p.title}};
        if(p.requestId != -1) j["requestId"] = p.requestId;
        if(p.cancellable) j["cancellable"] = p.cancellable;
        if(!p.message.empty()) j["message"] = p.message;
        if(p.percentage >= 0) j["percentage"] = p.percentage;
    }
    void to_json(json& j, const ProgressStartEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ProgressUpdateEventBody& p) {
        j = json{{"progressId", p.progressId}};
        if(!p.message.empty()) j["message"] = p.message;
        if(p.percentage >= 0) j["percentage"] = p.percentage;
    }
    void to_json(json& j, const ProgressUpdateEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ProgressEndEventBody& p) {
        j = json{{"progressId", p.progressId}};
        if(!p.message.empty()) j["message"] = p.message;
    }
    void to_json(json& j, const ProgressEndEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const InvalidatedEventBody& p) {
        j = json::object();
        if(!p.areas.empty()) j["areas"] = p.areas;
        if(p.threadId != -1) j["threadId"] = p.threadId;
        if(p.stackFrameId != -1) j["stackFrameId"] = p.stackFrameId;
    }
    void to_json(json& j, const InvalidatedEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const MemoryEventBody& p) {
        j = json{{"memoryReference", p.memoryReference}, {"offset", p.offset}, {"count", p.count}};
    }
    void to_json(json& j, const MemoryEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ContinuedEventBody& p) {
        j = json{{"threadId", p.threadId}};
        if(p.allThreadsContinued) j["allThreadsContinued"] = p.allThreadsContinued;
    }
    void to_json(json& j, const ContinuedEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ExitedEventBody& p) {
        j = json{{"exitCode", p.exitCode}};
    }
    void to_json(json& j, const ExitedEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ThreadEventBody& p) {
        j = json{{"threadId", p.threadId}, {"reason", p.reason}};
    }
    void to_json(json& j, const ThreadEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ModuleEventBody& p) {
        j = json{{"reason", p.reason}, {"module", p.module}};
    }
    void to_json(json& j, const ModuleEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const LoadedSourceEventBody& p) {
        j = json{{"reason", p.reason}, {"source", p.source}};
    }
    void to_json(json& j, const LoadedSourceEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const ProcessEventBody& p) {
        j = json{{"name", p.name}};
        if(p.systemProcessId != -1) j["systemProcessId"] = p.systemProcessId;
        if(p.isLocalProcess) j["isLocalProcess"] = p.isLocalProcess;
        if(!p.startMethod.empty()) j["startMethod"] = p.startMethod;
        if(p.pointerSize != -1) j["pointerSize"] = p.pointerSize;
    }
    void to_json(json& j, const ProcessEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
    void to_json(json& j, const CapabilitiesEventBody& p) {
        j = json{{"capabilities", p.capabilities}};
    }
    void to_json(json& j, const CapabilitiesEvent& p) {
        to_json(j,(Event&) p);
        j["body"] = p.body;
    }
}